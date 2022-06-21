#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lalafile.h"
#include "../util/byte-iterator.h"
#include "../vm/instructions.h"

LaLaFile *readLaLaFile(char *path){
    FILE *f = fopen(path, "r");
    if(!f) return NULL;

    fseek(f, 0, SEEK_END);
    uint64_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t *bytes = malloc(len);
    fread(bytes, 1, len, f);
    fclose(f);

    LaLaFile *laLaFile = malloc(sizeof(LaLaFile));
    laLaFile->bytes = bytes;
    laLaFile->len = len;
    return laLaFile;
}

LaLaProg *parseLaLaProg(LaLaFile *lalaFile){
    ByteIterator iterator;
    init_byte_iterator(lalaFile->len, lalaFile->bytes, &iterator);
    if(!has_uint(&iterator) || next_uint(&iterator) != MAGIC) return NULL;

    //Constants
    if(!has_ushort(&iterator)) return NULL;
    uint16_t intc_len = next_ushort(&iterator);
    if(remaining_bytes(&iterator) < intc_len * sizeof(int32_t)) return NULL;
    int32_t *intc = next_int_array(intc_len, &iterator);

    if(!has_ushort(&iterator)) return NULL;
    uint16_t longc_len = next_ushort(&iterator);
    if(remaining_bytes(&iterator) < longc_len * sizeof(int64_t)) return NULL;
    int64_t *longc = next_long_array(longc_len, &iterator);

    if(!has_ushort(&iterator)) return NULL;
    uint16_t floatc_len = next_ushort(&iterator);
    if(remaining_bytes(&iterator) < floatc_len * sizeof(float)) return NULL;
    float *floatc = next_float_array(floatc_len, &iterator);

    if(!has_ushort(&iterator)) return NULL;
    uint16_t doublec_len = next_ushort(&iterator);
    if(remaining_bytes(&iterator) < doublec_len * sizeof(double)) return NULL;
    double *doublec = next_double_array(doublec_len, &iterator);

    //Line information
    if(!has_ulong(&iterator)) return NULL;
    uint64_t line_change_len = next_ulong(&iterator);
    if(remaining_bytes(&iterator) < line_change_len * (sizeof(uint64_t) + sizeof(uint32_t))) return NULL;
    uint64_t *line_change_prog = next_ulong_array(line_change_len, &iterator);
    uint32_t *line_chane_line = next_uint_array(line_change_len, &iterator);


    LaLaProg *prog = malloc(sizeof(LaLaProg));
    prog->bytes = lalaFile->bytes;

    prog->header_len = iterator.offset;

    prog->intc_len = intc_len;
    prog->intc = intc;

    prog->longc_len = longc_len;
    prog->longc = longc;

    prog->floatc_len = floatc_len;
    prog->floatc = floatc;

    prog->doublec_len = doublec_len;
    prog->doublec = doublec;

    prog->line_change_len = line_change_len;
    prog->line_change_prog = line_change_prog;
    prog->line_change_line = line_chane_line;

    prog->prog_len = remaining_bytes(&iterator);
    prog->prog = next_byte_array(prog->prog_len, &iterator);

    return prog;
}

LaLaProgVerifyRes verifyLaLaProg(LaLaProg *prog){
    ByteIterator iterator;
    init_byte_iterator(prog->prog_len, prog->prog, &iterator);

    uint64_t int_stack_count = 0;

    while(has_byte(&iterator)){
        switch(next_byte(&iterator)){
            case PUSH_INTC:
                if(!has_ushort(&iterator)) return VERIFY_ERR;
                next_ushort(&iterator);
                int_stack_count++;
                break;

            case ADD_INT:
                if(int_stack_count < 2) return VERIFY_ERR;
                int_stack_count--;
                break;

            default:
                break;
        }
    }

    return VERIFY_OK;
}

uint32_t getProgLine(uint64_t instr_index, LaLaProg *prog){
    if(prog->line_change_len == 0) return 0;
    if(prog->line_change_len == 1) return prog->line_change_line[0];

    uint64_t left = 0, right = prog->line_change_len;
    uint64_t middle;
    while(left <= right){
        middle = (left + right) / 2;
        if(prog->line_change_prog[middle] > instr_index){
            if(middle == 0) return 0;
            right = middle - 1;
            continue;
        }
        if(middle == prog->line_change_len - 1 || prog->line_change_prog[middle + 1] > instr_index){
            return prog->line_change_line[middle];
        }
        left = middle + 1;
    }
    return UINT32_MAX;
}

void freeLaLaFile(LaLaFile *file){
    free(file->bytes);
    free(file);
}

void freeLaLaProg(LaLaProg *prog){
    free(prog->bytes);
    free(prog);
}