#include <stdlib.h>
#include "langueg-vm.h"
#include "instructions.h"
#include "../util/byte-iterator.h"

void initVm(Vm *vm){
    vm->ip = 0;
    vm->int_op_stack = malloc(sizeof(Stack32));
    initStack32(1u << 16u, vm->int_op_stack);
}

void freeVm(Vm *vm){
    freeLaLaProg(vm->prog);
    freeStack32(vm->int_op_stack);
    free(vm);
}

InterpResult execProg(LaLaProg *prog, Vm *vm){
    ByteIterator iterator;
    init_byte_iterator(prog->prog_len, prog->prog, &iterator);
    while(has_byte(&iterator)){
        switch (next_byte(&iterator)) {
            case PUSH_INTC:
                pushStack32(prog->intc[next_ushort(&iterator)], vm->int_op_stack);
                break;

            case NEG_INT:
                STACK_UNARY_OP(-, vm->int_op_stack);
                break;

            case ADD_INT:
                STACK_BIN_OP(+, vm->int_op_stack);
                break;

            case SUB_INT:
                STACK_BIN_OP(-, vm->int_op_stack);
                break;

            case MUL_INT:
                STACK_BIN_OP(*, vm->int_op_stack);
                break;

            case DIV_INT:
                STACK_BIN_OP(/, vm->int_op_stack);
                break;

            case MOD_INT:
                STACK_BIN_OP(%, vm->int_op_stack);
                break;

            case AND_INT:
                STACK_BIN_OP(&, vm->int_op_stack);
                break;

            case OR_INT:
                STACK_BIN_OP(|, vm->int_op_stack);
                break;

            case XOR_INT:
                STACK_BIN_OP(^, vm->int_op_stack);
                break;

            case SHIFTR_INT:
                STACK_BIN_OP(>>, vm->int_op_stack);
                break;

            case SHIFTL_INT:
                STACK_BIN_OP(<<, vm->int_op_stack);
                break;

            default:
                break;
        }
    }

    //printStack32(stdout, vm->int_op_stack);
    return INTERP_OK;
}

void loadProg(LaLaProg *prog, Vm *vm){
    vm->prog = prog;
}

InterpResult execVm(Vm *vm){
    return execProg(vm->prog, vm);
}