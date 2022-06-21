#include <stdint.h>

#define MAGIC ('a' << 24 | 'l' << 16 | 'a' << 8 | 'l')

typedef struct {
    uint64_t  len;
    uint8_t *bytes;
} LaLaFile;

typedef struct {
    uint8_t *bytes;

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

        uint64_t line_change_len;
        uint64_t *line_change_prog;
        uint32_t *line_change_line;

    //PROG
    uint64_t prog_len;
    uint8_t *prog;

} LaLaProg;

typedef enum {
    VERIFY_OK,
    VERIFY_ERR,
} LaLaProgVerifyRes;

LaLaFile *readLaLaFile(char*);
LaLaProg *parseLaLaProg(LaLaFile*);
LaLaProgVerifyRes verifyLaLaProg(LaLaProg*);
uint32_t getProgLine(uint64_t, LaLaProg*);

void freeLaLaFile(LaLaFile*);
void freeLaLaProg(LaLaProg*);