/*
** PROJECT, 2026
** ROMtiflam
** File description:
** add & sub
*/

#include "cpu/arm9.hpp"

void ARM9::execute_thumb_add_sub(uint16_t instruction) {

    bool mode = (instruction & (1 << 10)) != 0;
    bool is_sub = (instruction & (1 << 9)) != 0;
    uint32_t rn = (instruction >> 6) & THUMB_REG_MASK;
    uint32_t rs = (instruction >> 3) & THUMB_REG_MASK;
    uint32_t rd = (instruction & THUMB_REG_MASK);
    uint32_t val = reg[rs];
    uint32_t op2 = 0;
    uint32_t result = 0;

    if (!mode) op2 = reg[rn];
    else op2 = rn;
    if (is_sub) {
        result = val - op2;
        update_arithmetic_flags(val, op2, result, true);
    } else {
        result = val + op2;
        update_arithmetic_flags(val, op2, result, false);
    }
    reg[rd] = result;
}
