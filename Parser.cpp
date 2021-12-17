#include "Parser.h"

int Parser::Disassemble(unsigned char *bytes, unsigned int max, int offset, QString &output)
{
    base = bytes;
    opcode = *bytes++;

    const INSTRUCTION *instructions = standard_instructions;
    if (opcode == 0x0F) { // Extended opcodes
        if (max < 2 || *bytes == 0x0F || *bytes == 0xA6 || *bytes == 0xA7 || *bytes == 0xF7 || *bytes == 0xFF) {

            // Illegal instruction
            output = QString(".byte 0x%1").arg(opcode, 2, 16, QChar('0'));
            return 1;
        }

        instructions = extended_instructions;
        opcode = *bytes++;
    }

    // Skip ModRM byte parsing
    if (!instructions[opcode].hasModRM) {
        goto decode;
    }

    _RM_output.clear();
    _R_output.clear();

    modRM_mod = ((*bytes) >> 6) & 0b11; // Bits 7-6.
    modRM_reg = ((*bytes) >> 3) & 0b111; // Bits 5-3.
    modRM_rm = (*bytes++) & 0b111; // Bits 2-0.

    switch (instructions[opcode].size) {
        case WORD:
            _R_output = register_mnemonics16[modRM_reg];
            break;
        case BYTE:
            _R_output = register_mnemonics8[modRM_reg];
            break;
        default:
            _R_output = register_mnemonics32[modRM_reg];
    }

    if (modRM_mod == 0b11) { // Register addressing mode.
        switch (instructions[opcode].size) {
        case BYTE:
            _RM_output = register_mnemonics8[modRM_rm];
            break;
        case WORD:
            _RM_output = register_mnemonics16[modRM_rm];
            break;
        default:
            _RM_output = register_mnemonics32[modRM_rm];
        }

    } else if (modRM_mod == 0b00 && modRM_rm == 0b101) { // Displacement only addressing mode.
        _RM_output = QString("[0x%1]").arg(*(int *)bytes, 0, 16);
        bytes += 4;
    } else { // One-byte or four-byte signed displacement follows addressing mode byte(s).
        if (modRM_rm == 0b100) { // Contains SIB byte
            char SIB_scale = ((*bytes) >> 6) & 0b11; // Bits 7-6.
            char SIB_index = ((*bytes) >> 3) & 0b111; // Bits 5-3.
            char SIB_base = (*bytes++) & 0b111; // Bits 2-0.

            if (SIB_base == 0b101 && modRM_mod == 0b00) {
                _RM_output = QString("[0x%1").arg(*(int *)bytes, 0, 16);
                bytes += 4;
            } else {
                _RM_output = sib_base_mnemonics[SIB_base];
            }

            if (SIB_index != 0b100) {
                _RM_output.append("+");
                _RM_output.append(register_mnemonics32[SIB_index]);
                _RM_output.append(sib_scale_mnemonics[SIB_scale]);
            }
        } else {
            _RM_output = QString("[").append(register_mnemonics32[modRM_rm]);
        }

        if (modRM_mod == 0b01) { // One-byte signed displacement follows addressing mode byte(s).
            if (*bytes > 0x7F) {
                _RM_output.append(QString("-0x%1]").arg(-*(char *)bytes++, 0, 16));
            } else {
                _RM_output.append(QString("+0x%1]").arg(+*(char *)bytes++, 0, 16));
            }
        } else if (modRM_mod == 0b10) { // Four-byte signed displacement follows addressing mode byte(s).
            if (*(unsigned int *)bytes > 0x7FFFFFFF) {
                _RM_output.append(QString("-0x%1]").arg(-*(int *)bytes, 0, 16));
            } else {
                _RM_output.append(QString("+0x%1]").arg(*(unsigned int *)bytes, 0, 16));
            }

            bytes += 4;
        } else {
            _RM_output.append("]");
        }
    }

decode:
    return Decode(instructions, bytes, max, offset, output);

}

int Parser::Decode(const INSTRUCTION *instructions, unsigned char *bytes, unsigned int max, int offset, QString &output)
{
    output = instructions[opcode].mnemonic;

    for (int i = 0; i < instructions[opcode].argument_count; i++) {
        if (i > 0) {
            output.append(",");
        }

        switch (instructions[opcode].arguments[i]) {
            case RM:
                if (modRM_mod != 0b11) {
                    switch (instructions[opcode].size) {
                        case BYTE:
                            output.append("BYTE PTR ");
                            break;
                        case WORD:
                            output.append("WORD PTR ");
                            break;
                        case DWORD:
                            output.append("DWORD PTR ");
                            break;
                        case QWORD:
                            output.append("QWORD PTR ");
                            break;
                        case FWORD:
                            output.append("FWORD PTR ");
                            break;
                        case XMMWORD:
                            output.append("XMMWORD PTR ");
                            break;
                    }
                }

                output.append(_RM_output);
                break;
            case R:
                output.append(_R_output);
                break;
            case IMM8:
                output.append(QString("0x%1").arg(*bytes++, 0, 16));
                break;
            case IMM16:
                output.append(QString("0x%1").arg(*(short *)bytes, 0, 16));
                bytes += 2;
                break;
            case IMM32:
                output.append(QString("0x%1").arg(*(int *)bytes, 0, 16));
                bytes += 4;
                break;
            case REL8:
                output.append(QString("0x%1").arg(offset + ((bytes - base) + 1) + *(char *)bytes++, 0, 16));
                break;
            case REL32:
                output.append(QString("0x%1").arg(offset + ((bytes - base) + 4) + *(int *)bytes, 0, 16));
                bytes += 4;
                break;
            case PTR1632:
                output.append(QString("0x%1:0x%2").arg(*(short *)(bytes + 4), 0, 16).arg(*(int *)bytes, 0, 16));
                bytes += 6;
                break;
            case AL:
                output.append("al");
                break;
            case EAX:
                output.append("eax");
                break;
            case ES:
                output.append("es");
                break;
            case CS:
                output.append("cs");
                break;
            case SS:
                output.append("ss");
                break;
            case DS:
                output.append("ds");
                break;
            case ONE:
                output.append("1");
                break;
            case CL:
                output.append("cl");
                break;
            case XMM0:
                output.append("xmm0");
                break;
            case BND0:
                output.append("bnd0");
                break;
            case BAD:
                bytes++;
                break;
            case MM0:
                output.append("mm0");
                break;
        }
    }

    if (((unsigned int)(bytes - base)) <= max)
        return bytes - base;
    else
        return 1;
}

