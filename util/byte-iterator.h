#include <stdint.h>

typedef struct {
    uint64_t offset;
    uint64_t len;
    uint8_t *bytes;
} ByteIterator;

inline void init_byte_iterator(uint64_t len, uint8_t *bytes, ByteIterator *iterator){
    iterator->offset = 0;
    iterator->len = len;
    iterator->bytes = bytes;
}

inline int isEOF(ByteIterator *iterator){
    return iterator->offset >= iterator->len;
}

inline uint64_t remaining_bytes(ByteIterator *iterator){
    return iterator->len - iterator->offset;
}

inline int has_byte(ByteIterator *iterator){
    return remaining_bytes(iterator) >= sizeof(uint8_t);
}

inline int has_ushort(ByteIterator *iterator){
    return remaining_bytes(iterator) >= sizeof(uint16_t);
}

inline int has_uint(ByteIterator *iterator){
    return remaining_bytes(iterator) >= sizeof(uint32_t);
}

inline int has_ulong(ByteIterator *iterator){
    return remaining_bytes(iterator) >= sizeof(uint64_t);
}

inline int has_short(ByteIterator *iterator){
    return remaining_bytes(iterator) >= sizeof(int16_t);
}

inline int has_int(ByteIterator *iterator){
    return remaining_bytes(iterator) >= sizeof(int32_t);
}

inline int has_long(ByteIterator *iterator){
    return remaining_bytes(iterator) >= sizeof(uint64_t);
}

inline int has_float(ByteIterator *iterator){
    return remaining_bytes(iterator) >= sizeof(float);
}

inline int has_double(ByteIterator *iterator){
    return remaining_bytes(iterator) >= sizeof(double);
}

inline uint8_t *next_byte_array(uint64_t len, ByteIterator *iterator){
    iterator->offset += len * sizeof(uint8_t);
    return (iterator->bytes + iterator->offset - len * sizeof(uint8_t));
}

inline uint32_t *next_uint_array(uint64_t len, ByteIterator *iterator){
    iterator->offset += len * sizeof(uint32_t);
    return (uint32_t*)(iterator->bytes + iterator->offset - len * sizeof(uint32_t));
}

inline uint64_t *next_ulong_array(uint64_t len, ByteIterator *iterator){
    iterator->offset += len * sizeof(uint64_t);
    return (uint64_t*)(iterator->bytes + iterator->offset - len * sizeof(uint64_t));
}

inline int32_t *next_int_array(uint64_t len, ByteIterator *iterator){
    iterator->offset += len * sizeof(int32_t);
    return (int32_t*)(iterator->bytes + iterator->offset - len * sizeof(int32_t));
}

inline int64_t *next_long_array(uint64_t len, ByteIterator *iterator){
    iterator->offset += len * sizeof(int64_t);
    return (int64_t*)(iterator->bytes + iterator->offset - len * sizeof(int64_t));
}

inline float *next_float_array(uint64_t len, ByteIterator *iterator){
    iterator->offset += len * sizeof(float);
    return (float*)(iterator->bytes + iterator->offset - len * sizeof(float));
}

inline double *next_double_array(uint64_t len, ByteIterator *iterator){
    iterator->offset += len * sizeof(double);
    return (double*)(iterator->bytes + iterator->offset - len * sizeof(double));
}

inline uint8_t next_byte(ByteIterator *iterator){
    iterator->offset += sizeof(uint8_t);
    return *(iterator->bytes + iterator->offset - sizeof(uint8_t));
}

inline uint16_t next_ushort(ByteIterator *iterator){
    iterator->offset += sizeof(uint16_t);
    return *(uint16_t*)(iterator->bytes + iterator->offset - sizeof(uint16_t));
}

inline uint32_t next_uint(ByteIterator *iterator){
    iterator->offset += sizeof(uint32_t);
    return *(uint32_t*)(iterator->bytes + iterator->offset - sizeof(uint32_t));
}

inline uint64_t next_ulong(ByteIterator *iterator){
    iterator->offset += sizeof(uint64_t);
    return *(uint64_t*)(iterator->bytes + iterator->offset - sizeof(uint64_t));
}

inline int16_t next_short(ByteIterator *iterator){
    iterator->offset += sizeof(int16_t);
    return *(int16_t*)(iterator->bytes + iterator->offset - sizeof(int16_t));
}

inline int32_t next_int(ByteIterator *iterator){
    iterator->offset += sizeof(int32_t);
    return *(int32_t*)(iterator->bytes + iterator->offset - sizeof(int32_t));
}

inline int64_t next_long(ByteIterator *iterator){
    iterator->offset += sizeof(int64_t);
    return *(int64_t*)(iterator->bytes + iterator->offset - sizeof(int64_t));
}

inline float next_float(ByteIterator *iterator){
    iterator->offset += sizeof(float);
    return *(float*)(iterator->bytes + iterator->offset - sizeof(float));
}

inline double next_double(ByteIterator *iterator){
    iterator->offset += sizeof(double);
    return *(double*)(iterator->bytes + iterator->offset - sizeof(double));
}