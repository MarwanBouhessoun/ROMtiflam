/*
** PROJECT, 2026
** ROMtiflam
** File description:
** add & sub
*/

#include "cpu/arm9.hpp"

void ARM9::execute_thumb_add_sub(uint16_t instruction) {

    bool mode = (instruction & THUMB_ADD_SUB_MODE_BIT) != 0;
    bool is_sub = (instruction & THUMB_ADD_SUB_OP_BIT) != 0;
    uint32_t rn = (instruction >> THUMB_RN_SHIFT) & THUMB_REG_MASK;
    uint32_t rs = (instruction >> THUMB_RS_SHIFT) & THUMB_REG_MASK;
    uint32_t rd = instruction & THUMB_REG_MASK;
    uint32_t val = reg[rs];
    uint32_t op2 = mode ? rn : reg[rn];
    uint32_t result = is_sub ? (val - op2) : (val + op2);

    update_arithmetic_flags(val, op2, result, is_sub);
    reg[rd] = result;
}
