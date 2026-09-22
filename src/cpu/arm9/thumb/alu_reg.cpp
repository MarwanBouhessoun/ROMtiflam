/*
** PROJECT, 2026
** ROMtiflam
** File description:
** alu reg
*/

#include "cpu/arm9.hpp"

void ARM9::execute_thumb_alu_reg(uint16_t instruction) {

    uint32_t opcode = (instruction >> 6) & 0xF;
    uint32_t rs = (instruction >> 3) & THUMB_REG_MASK;
    uint32_t rd = instruction & THUMB_REG_MASK;
    uint32_t val_d = reg[rd];
    uint32_t val_s = reg[rs];
    uint32_t result = 0;
    bool old_carry = (cpsr & FLAG_C) != 0;
    bool update_c = false;
    bool new_carry = old_carry;
    uint32_t shift_val = val_s & 0xFF;

    switch (opcode) {
        case 0x0: // AND
            result = val_d & val_s;
            break;
        case 0x1: // EOR
            result = val_d ^ val_s;
            break;
        case 0x2: // LSL
            if (shift_val == 0) result = val_d;
            else if (shift_val < 32) { result = val_d << shift_val; new_carry = (val_d >> (32 - shift_val)) & 1; update_c = true; }
            else if (shift_val == 32) { result = 0; new_carry = val_d & 1; update_c = true; }
            else { result = 0; new_carry = false; update_c = true; }
            break;
        case 0x3: // LSR
            if (shift_val == 0) result = val_d;
            else if (shift_val < 32) { result = val_d >> shift_val; new_carry = (val_d >> (shift_val - 1)) & 1; update_c = true; }
            else if (shift_val == 32) { result = 0; new_carry = (val_d >> 31) & 1; update_c = true; }
            else { result = 0; new_carry = false; update_c = true; }
            break;
        case 0x4: // ASR
            if (shift_val == 0) result = val_d;
            else if (shift_val < 32) { result = static_cast<uint32_t>(static_cast<int32_t>(val_d) >> shift_val); new_carry = (val_d >> (shift_val - 1)) & 1; update_c = true; }
            else { result = (val_d & FLAG_N) ? 0xFFFFFFFF : 0; new_carry = (val_d >> 31) & 1; update_c = true; }
            break;
        case 0x5: // ADC
            result = val_d + val_s + old_carry;
            update_arithmetic_flags(val_d, val_s, result, false);
            break;
        case 0x6: // SBC
            result = val_d - val_s - (!old_carry);
            update_arithmetic_flags(val_d, val_s, result, true);
            break;
        case 0x7: // ROR
            if (shift_val == 0) result = val_d;
            else {
                shift_val %= 32;
                if (shift_val == 0) shift_val = 32;
                result = (val_d >> shift_val) | (val_d << (32 - shift_val));
                new_carry = (val_d >> (shift_val - 1)) & 1;
                update_c = true;
            }
            break;
        case 0x8: // TST
            result = val_d & val_s;
            break;
        case 0x9: // NEG
            result = 0 - val_s;
            update_arithmetic_flags(0, val_s, result, true);
            break;
        case 0xA: // CMP
            result = val_d - val_s;
            update_arithmetic_flags(val_d, val_s, result, true);
            break;
        case 0xB: // CMN
            result = val_d + val_s;
            update_arithmetic_flags(val_d, val_s, result, false);
            break;
        case 0xC: // ORR
            result = val_d | val_s;
            break;
        case 0xD: // MUL
            result = val_d * val_s;
            break;
        case 0xE: // BIC
            result = val_d & (~val_s);
            break;
        case 0xF: // MVN
            result = ~val_s;
            break;
    }
    if (opcode != 0x8 && opcode != 0xA && opcode != 0xB) {
        reg[rd] = result;
    }
    bool is_arithmetic = (opcode == 0x5 || opcode == 0x6 || opcode == 0x9 || opcode == 0xA || opcode == 0xB);
    if (!is_arithmetic) {
        if (result & FLAG_N) cpsr |= FLAG_N; else cpsr &= ~FLAG_N;
        if (result == 0) cpsr |= FLAG_Z; else cpsr &= ~FLAG_Z;
        if (update_c) {
            if (new_carry) cpsr |= FLAG_C; else cpsr &= ~FLAG_C;
        }
    }
}
