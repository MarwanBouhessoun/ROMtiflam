/*
** PROJECT, 2026
** ROMtiflam
** File description:
** shift reg
*/

#include "cpu/arm9.hpp"
#include "cpu/instruction.hpp"

void ARM9::execute_thumb_shift_reg(uint16_t instruction) {

    uint32_t opcode = (instruction >> THUMB_OPCODE_SHIFT) & THUMB_OPCODE_MASK;
    uint32_t offset5 = (instruction >> THUMB_OFFSET5_SHIFT) & THUMB_OFFSET5_MASK;
    uint32_t reg_source = (instruction >> THUMB_RS_SHIFT) & THUMB_REG_MASK;
    uint32_t rd = instruction & THUMB_REG_MASK;
    uint32_t val = reg[reg_source];
    uint32_t result = 0;
    bool carry = (cpsr & FLAG_C) != 0;
    bool update_carry = true;

    switch (opcode) {
        case THUMB_SHIFT_LSL:
            if (offset5 == 0) {
                result = val;
                update_carry = false;
            } else {
                result = val << offset5;
                carry = (val >> (ARM_WORD_SIZE_BITS - offset5)) & 1;
            }
            break;

        case THUMB_SHIFT_LSR:
            if (offset5 == 0) {
                result = 0;
                carry = (val >> (ARM_WORD_SIZE_BITS - 1)) & 1;
            } else {
                result = val >> offset5;
                carry = (val >> (offset5 - 1)) & 1;
            }
            break;

        case THUMB_SHIFT_ASR:
            if (offset5 == 0) {
                bool sign = (val & FLAG_N) != 0;
                result = sign ? 0xFFFFFFFF : 0;
                carry = (val >> (ARM_WORD_SIZE_BITS - 1)) & 1;
            } else {
                result = static_cast<uint32_t>(static_cast<int32_t>(val) >> offset5);
                carry = (val >> (offset5 - 1)) & 1;
            }
            break;

        default:
            return;
    }
    reg[rd] = result;
    if (result & FLAG_N) cpsr |= FLAG_N;
    else cpsr &= ~FLAG_N;

    if (result == 0) cpsr |= FLAG_Z;
    else cpsr &= ~FLAG_Z;

    if (update_carry) {
        if (carry) cpsr |= FLAG_C;
        else cpsr &= ~FLAG_C;
    }
}
