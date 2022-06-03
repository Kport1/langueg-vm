#include <stdint.h>
#ifndef LANGUEG_VM_LALAFILE_H
#define LANGUEG_VM_LALAFILE_H

#endif //LANGUEG_VM_LALAFILE_H

typedef struct {
    uint64_t  len;
    uint8_t *bytes;
} LaLaFile;

typedef struct {
    //HEADER
        uint64_t  header_len;

        uint16_t intc_len;
        int32_t *intc;

        uint16_t longc_len;
        int64_t *longc;

        uint16_t floatc_len;
        float *floatc;

        uint16_t doublec_len;
        double *doublec;

    //PROG
    uint64_t prog_len;
    uint8_t *prog;

} LaLaProg;