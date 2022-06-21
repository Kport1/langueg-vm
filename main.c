#include <stdio.h>
#include <stdlib.h>
//#include "load/lalafile.h"
#include "error/error.h"
//#include "stack/stack.h"
#include "vm/langueg-vm.h"

int main(int argc, char **argv) {
    if(argc != 2){
        eprintf("Supply a main .lala file");
        return EXIT_FAILURE;
    }
    char *main_file_name = argv[1];

    LaLaFile *main_file = readLaLaFile(main_file_name);
    if(!main_file){
        eprintf("File %s doesn't exist", main_file_name);
        return EXIT_FAILURE;
    }

    LaLaProg *main_prog = parseLaLaProg(main_file);
    if(!main_prog){
        eprintf("File %s isn't a valid .lala file", main_file_name);
        freeLaLaFile(main_file);
        return EXIT_FAILURE;
    }

    if(verifyLaLaProg(main_prog) != VERIFY_OK){
        eprintf("File %s isn't a valid .lala file", main_file_name);
        freeLaLaProg(main_prog);
        free(main_file);
        return EXIT_FAILURE;
    }

    Vm *vm = malloc(sizeof(Vm));
    initVm(vm);
    loadProg(main_prog, vm);
    execVm(vm);
    printStack32(stdout, vm->int_op_stack);

    freeVm(vm);

    return EXIT_SUCCESS;
}
