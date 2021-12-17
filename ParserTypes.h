#ifndef PARSERTYPES_H
#define PARSERTYPES_H

enum
{
    AL, EAX, ES, CS, SS, DS, ONE, CL, XMM0, BND0, BAD, MM0,
    IMM8, IMM16, IMM32, REL8, REL32, PTR1632, R, RM,
    BYTE, WORD, DWORD, QWORD, FWORD, XMMWORD
};

typedef struct {
    char hasModRM, size;
    char mnemonic[0xFF];
    char argument_count;
    char arguments[4];
} INSTRUCTION;

#endif // PARSERTYPES_H
