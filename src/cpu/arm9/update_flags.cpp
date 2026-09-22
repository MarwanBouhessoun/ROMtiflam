/*
** PROJECT, 2026
** ROMtiflam
** File description:
** arm9 exec arm function
*/

#include "cpu/arm9.hpp"

void ARM9::update_logic_flags(uint32_t result, bool carry_out) {

cpsr = (cpsr & ~(FLAG_N | FLAG_Z | FLAG_C))
        | (result & FLAG_N)
        | ((result == 0) ? FLAG_Z : 0)
        | (carry_out ? FLAG_C : 0);
}

void ARM9::update_arithmetic_flags(uint32_t rn, uint32_t op2, uint32_t result, bool is_subtraction) {

    uint32_t c_flag = 0;
    bool overflow = false;

    if (is_subtraction) {
        c_flag = (rn >= op2) ? FLAG_C : 0;
        overflow = ((rn ^ op2) & (rn ^ result)) & FLAG_N;
    } else {
        c_flag = (result < rn) ? FLAG_C : 0;
        overflow = (~(rn ^ op2) & (rn ^ result)) & FLAG_N;
    }

    cpsr = (cpsr & ~(FLAG_N | FLAG_Z | FLAG_C | FLAG_V))
        | (result & FLAG_N)
        | ((result == 0) ? FLAG_Z : 0)
        | c_flag
        | (overflow ? FLAG_V : 0);
}