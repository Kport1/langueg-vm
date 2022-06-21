#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define STACK_INITIAL_CAP 16
#define STACK_GROW_PERC 1.75

#define STACK_BIN_OP(op, astack)                                                \
do {                                                                            \
    (astack)->stack[(astack)->size - 2] op= (astack)->stack[(astack)->size - 1];\
    (astack)->size--;                                                           \
} while(0)

#define STACK_UNARY_OP(op, astack)                                                  \
do {                                                                                \
    (astack)->stack[(astack)->size - 1] = op((astack)->stack[(astack)->size - 1]);  \
} while(0)

typedef struct {
    uint8_t *stack;
    uint32_t capacity;
    uint32_t size;
} Stack8u;

typedef struct {
    int16_t *stack;
    uint32_t capacity;
    uint32_t size;
} Stack16;

typedef struct {
    int32_t *stack;
    uint32_t capacity;
    uint32_t size;
} Stack32;

typedef struct {
    int64_t *stack;
    uint32_t capacity;
    uint32_t size;
} Stack64;

inline void initStack8u(uint32_t initial_cap, Stack8u *stack){
    stack->stack = malloc(initial_cap * sizeof(uint8_t));
    stack->capacity = initial_cap;
    stack->size = 0;
}

inline void pushStack8u(uint8_t val, Stack8u *stack){
    stack->stack[stack->size] = val;
    stack->size++;
    if(stack->size >= stack->capacity){
        stack->stack = realloc(stack->stack, (size_t)(stack->capacity * STACK_GROW_PERC));
        stack->capacity = stack->capacity * STACK_GROW_PERC;
    }
}

inline uint8_t popStack8u(Stack8u *stack){
    stack->size--;
    return stack->stack[stack->size];
}

inline void freeStack8u(Stack8u *stack){
    free(stack->stack);
    free(stack);
}

inline void printStack8u(FILE *out, Stack8u *stack){
    fprintf(out, "[");
    for(uint32_t i = 0; i < stack->size; i++){
        fprintf(out, "%u", stack->stack[i]);
        if(i == stack->size - 1) break;
        fprintf(out, ", ");
    }
    fprintf(out, "]  cap: %u\n", stack->capacity);
}

inline void initStack16(uint32_t initial_cap, Stack16 *stack){
    stack->stack = malloc(initial_cap * sizeof(int16_t));
    stack->capacity = initial_cap;
    stack->size = 0;
}

inline void pushStack16(int16_t val, Stack16 *stack){
    stack->stack[stack->size] = val;
    stack->size++;
    if(stack->size >= stack->capacity){
        stack->stack = realloc(stack->stack, (size_t)(stack->capacity * STACK_GROW_PERC) * sizeof(int16_t));
        stack->capacity = stack->capacity * STACK_GROW_PERC;
    }
}

inline int16_t popStack16(Stack16 *stack){
    stack->size--;
    return stack->stack[stack->size];
}

inline void freeStack16(Stack16 *stack){
    free(stack->stack);
    free(stack);
}

inline void printStack16(FILE *out, Stack16 *stack){
    fprintf(out, "[");
    for(uint32_t i = 0; i < stack->size; i++){
        fprintf(out, "%i", stack->stack[i]);
        if(i == stack->size - 1) break;
        fprintf(out, ", ");
    }
    fprintf(out, "]  cap: %u\n", stack->capacity);
}

inline void initStack32(uint32_t initial_cap, Stack32 *stack){
    stack->stack = malloc(initial_cap * sizeof(int32_t));
    stack->capacity = initial_cap;
    stack->size = 0;
}

inline void pushStack32(int32_t val, Stack32 *stack){
    stack->stack[stack->size] = val;
    stack->size++;
    if(stack->size >= stack->capacity){
        stack->stack = realloc(stack->stack, (size_t)(stack->capacity * STACK_GROW_PERC) * sizeof(int32_t));
        stack->capacity = stack->capacity * STACK_GROW_PERC;
    }
}

inline int32_t popStack32(Stack32 *stack){
    stack->size--;
    return stack->stack[stack->size];
}

inline void freeStack32(Stack32 *stack){
    free(stack->stack);
    free(stack);
}

inline void printStack32(FILE *out, Stack32 *stack){
    fprintf(out, "[");
    for(uint32_t i = 0; i < stack->size; i++){
        fprintf(out, "%i", stack->stack[i]);
        if(i == stack->size - 1) break;
        fprintf(out, ", ");
    }
    fprintf(out, "]  cap: %u\n", stack->capacity);
}

inline void initStack64(uint32_t initial_cap, Stack64 *stack){
    stack->stack = malloc(initial_cap * sizeof(int64_t));
    stack->capacity = initial_cap;
    stack->size = 0;
}

inline void pushStack64(int64_t val, Stack64 *stack){
    stack->stack[stack->size] = val;
    stack->size++;
    if(stack->size >= stack->capacity){
        stack->stack = realloc(stack->stack, (size_t)(stack->capacity * STACK_GROW_PERC) * sizeof(int64_t));
        stack->capacity = stack->capacity * STACK_GROW_PERC;
    }
}

inline int64_t popStack64(Stack64 *stack){
    stack->size--;
    return stack->stack[stack->size];
}

inline void freeStack64(Stack64 *stack){
    free(stack->stack);
    free(stack);
}

inline void printStack64(FILE *out, Stack64 *stack){
    fprintf(out, "[");
    for(uint32_t i = 0; i < stack->size; i++){
        fprintf(out, "%lli", stack->stack[i]);
        if(i == stack->size - 1) break;
        fprintf(out, ", ");
    }
    fprintf(out, "]  cap: %u\n", stack->capacity);
}