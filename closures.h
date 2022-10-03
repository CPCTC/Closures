#pragma once

//
// Header
//

void *clsr_capture(void *fn, void *data);
int clsr_release(void **pclsr);
register void *CLSR_DATA __asm__ ("r11");   // Yes, %r11 is call-clobbered

//
// Implementation
//

#ifdef CLSR_IMPLEMENTATION

#define _GNU_SOURCE
#include <sys/mman.h>
#include <stddef.h>

typedef struct __attribute__ ((packed)) {
    unsigned char b : 1;
    unsigned char x : 1;
    unsigned char r : 1;
    unsigned char w : 1;
    unsigned char up : 4;
} Rex;

typedef struct __attribute__ ((packed)) {
    unsigned char rm : 3;
    unsigned char reg : 3;
    unsigned char mod : 2;
} ModRM;

typedef struct __attribute__ ((packed)) {
    Rex rex;
    unsigned char opcode;
    void *imm64;
} Mov;

typedef struct __attribute__ ((packed)) {
    unsigned char opcode;
    ModRM modrm;
    int disp32;
} Jmp;

typedef struct __attribute__ ((packed)) {
    Mov mov;
    Jmp jmp;
    void *fn;
} Code;

void *clsr_capture(void *fn, void *data) {
    Code *code = mmap(NULL, sizeof (Code), PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, 0);
    if (code == MAP_FAILED)
        return NULL;

    *code = (Code) {
        .mov = {
            .rex = {
                .up = 4,
                .w = 1,
                .r = 0,
                .x = 0,
                .b = 1,
            },
            .opcode = 0xb8 + 3,
            .imm64 = data,
        },
        .jmp = {
            .opcode = 0xFF,
            .modrm = {
                .mod = 0,
                .reg = 4,
                .rm = 5,
            },
            .disp32 = 0,
        },
        .fn = fn,
    };

    return code;
}

int clsr_release(void **pclsr) {
    int ret = munmap(*pclsr, sizeof (Code));
    if (!ret)
        *pclsr = NULL;
    return ret;
}

#endif
