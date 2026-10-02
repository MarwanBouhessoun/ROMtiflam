/*
** PROJECT, 2026
** ROMtiflam
** File description:
** alu reg
*/

#include "cpu/arm9.hpp"

uint32_t and_(uint32_t val_d, uint32_t val_s) {

    return val_d & val_s;
}

uint32_t eor_(uint32_t val_d, uint32_t val_s) {

    return val_d ^ val_s;
}

uint32_t lsl_(uint32_t shift_val, bool& update_c, uint32_t val_d, bool& new_carry) {

    if (shift_val > 0) {
        update_c = true;
        if (shift_val < 32) {
            new_carry = (val_d >> (32 - shift_val)) & 1;
            return val_d << shift_val;
        } else {
            new_carry = (shift_val == 32) ? (val_d & 1) : false;
            return 0;
        }
    } else
        return val_d;
}

uint32_t lsr_(uint32_t shift_val, bool& update_c, uint32_t val_d, bool& new_carry) {

    if (shift_val > 0) {
        update_c = true;
        if (shift_val < 32) {
            new_carry = (val_d >> (shift_val - 1)) & 1;
            return val_d >> shift_val;
        } else {
            new_carry = (shift_val == 32) ? ((val_d >> 31) & 1) : false;
            return 0;
        }
    } else
        return val_d;
}

uint32_t asr_(uint32_t shift_val, bool& update_c, uint32_t val_d, bool& new_carry) {

    if (shift_val > 0) {
        update_c = true;
        if (shift_val < 32) {
            new_carry = (val_d >> (shift_val - 1)) & 1;
            return static_cast<uint32_t>(static_cast<int32_t>(val_d) >> shift_val);
        } else {
            new_carry = (val_d >> 31) & 1;
            return (val_d & FLAG_N) ? 0xFFFFFFFF : 0;
        }
    } else
        return val_d;
}

uint32_t adc_(bool &is_logical, uint32_t val_d, uint32_t val_s, bool old_carry) {

    is_logical = false;
    return val_d + val_s + old_carry;
}

uint32_t sbc_(bool &is_logical, uint32_t val_d, uint32_t val_s, bool old_carry) {

    is_logical = false;
    return val_d - val_s - (!old_carry);
}

uint32_t ror_(uint32_t shift_val, bool &update_c, uint32_t val_d, bool &new_carry) {

    if (shift_val > 0) {
        update_c = true;
        shift_val %= 32;
        if (shift_val == 0) shift_val = 32;
        new_carry = (val_d >> (shift_val - 1)) & 1;
        return (val_d >> shift_val) | (val_d << (32 - shift_val));
    } else
        return val_d;
}

uint32_t tst_(uint32_t val_d, uint32_t val_s) {

    return val_d & val_s;
}

uint32_t neg_(uint32_t val_s, bool &is_logical) {

    is_logical = false;
    return -val_s;
}

uint32_t cmp_(uint32_t val_d, uint32_t val_s, bool &is_logical) {

    is_logical = false;
    return val_d - val_s;
}

uint32_t cmn_(uint32_t val_d, uint32_t val_s, bool &is_logical) {

    is_logical = false;
    return val_d + val_s;
}

uint32_t orr_(uint32_t val_d, uint32_t val_s) {

    return val_d | val_s;
}

uint32_t mul_(uint32_t val_d, uint32_t val_s) {

    return val_d * val_s;
}

uint32_t bic_(uint32_t val_d, uint32_t val_s) {

    return val_d & (~val_s);
}

uint32_t mvn_(uint32_t val_s) {

    return ~val_s;
}


void ARM9::execute_thumb_alu_reg(uint16_t instruction) {

    uint32_t opcode = (instruction >> THUMB_ALU_OPCODE_SHIFT) & THUMB_ALU_OPCODE_MASK;
    uint32_t rs = (instruction >> THUMB_RS_SHIFT) & THUMB_REG_MASK;
    uint32_t rd = instruction & THUMB_REG_MASK;

    uint32_t val_d = reg[rd];
    uint32_t val_s = reg[rs];
    uint32_t result = 0;

    bool old_carry = (cpsr & FLAG_C) != 0;
    bool update_c = false;
    bool new_carry = old_carry;
    uint32_t shift_val = val_s & THUMB_SHIFT_VAL_MASK;
    bool is_logical = true;

    switch (opcode) {
        case 0x0: // AND
            result = and_(val_d, val_s);
            break;
        case 0x1: // EOR
            result = eor_(val_d, val_s);
            break;
        case 0x2: // LSL
            result = lsl_(shift_val, update_c, val_d, new_carry);
            break;
        case 0x3: // LSR
            result = lsr_(shift_val, update_c, val_d, new_carry);
            break;
        case 0x4: // ASR
            result = asr_(shift_val, update_c, val_d, new_carry);
            break;
        case 0x5: // ADC
            result = adc_(is_logical, val_d, val_s, old_carry);
            update_arithmetic_flags(val_d, val_s, val_d + val_s + old_carry, false);
            break;
        case 0x6: // SBC
            result = sbc_(is_logical, val_d, val_s, old_carry);
            update_arithmetic_flags(val_d, val_s, val_d - val_s - (!old_carry), true);
            break;
        case 0x7: // ROR
            result = ror_(shift_val, update_c, val_d, new_carry);
            break;
        case 0x8: // TST
            result = tst_(val_d, val_s);
            break;
        case 0x9: // NEG
            result = neg_(val_s, is_logical);
            update_arithmetic_flags(0, val_s, -val_s, true);
            break;
        case 0xA: // CMP
            result = cmp_(val_d, val_s, is_logical);
            update_arithmetic_flags(val_d, val_s, val_d - val_s, true);
            break;
        case 0xB: // CMN
            result = cmn_(val_d, val_s, is_logical);
            update_arithmetic_flags(val_d, val_s, val_d + val_s, false);
            break;
        case 0xC: // ORR
            result = orr_(val_d, val_s);
            break;
        case 0xD: // MUL
            result = mul_(val_d, val_s);
            break;
        case 0xE: // BIC
            result = bic_(val_d, val_s);
            break;
        case 0xF: // MVN
            result = mvn_(val_s);
            break;
    }

    if (opcode != 0x8 && opcode != 0xA && opcode != 0xB)
        reg[rd] = result;
    if (is_logical) {
        uint32_t c_flag = update_c ? (new_carry ? FLAG_C : 0) : (cpsr & FLAG_C);

        cpsr = (cpsr & ~(FLAG_N | FLAG_Z | FLAG_C))
            | (result & FLAG_N)
            | ((result == 0) ? FLAG_Z : 0)
            | c_flag;
    }
}