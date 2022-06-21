#include <stdint.h>
#include "../load/lalafile.h"
#include "../stack/stack.h"

typedef enum {
    INTERP_OK,
    INTERP_ERR,
} InterpResult;

typedef struct {
    uint64_t ip;
    LaLaProg *prog;

    Stack32 *int_op_stack;
} Vm;

void initVm(Vm*);
void freeVm(Vm*);
void loadProg(LaLaProg*, Vm*);
InterpResult execVm(Vm*);
