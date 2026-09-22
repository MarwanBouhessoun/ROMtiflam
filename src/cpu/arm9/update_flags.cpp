/*
** PROJECT, 2026
** ROMtiflam
** File description:
** arm9 exec arm function
*/

#include "cpu/arm9.hpp"

void ARM9::update_logic_flags(uint32_t result, bool carry_out) {

    cpsr &= ~(FLAG_N | FLAG_Z | FLAG_C);

    uint32_t new_flags = 0;

    new_flags |= (result & FLAG_N);
    if (result == 0) new_flags |= FLAG_Z;
    if (carry_out) new_flags |= FLAG_C;

    cpsr |= new_flags;
}

void ARM9::update_arithmetic_flags(uint32_t rn, uint32_t op2, uint32_t result, bool is_subtraction) {

    cpsr &= ~(FLAG_N | FLAG_Z | FLAG_C | FLAG_V);

    uint32_t new_flags = 0;

    new_flags |= (result & FLAG_N);
    if (result == 0)
        new_flags |= FLAG_Z;

    bool rn_sign = (rn & FLAG_N) != 0;
    bool op2_sign = (op2 & FLAG_N) != 0;
    bool res_sign = (result & FLAG_N) != 0;

    if (is_subtraction) {
        if (rn >= op2)
            new_flags |= FLAG_C;
        if (rn_sign != op2_sign && res_sign != rn_sign)
            new_flags |= FLAG_V;
    } else {
        if (result < rn)
            new_flags |= FLAG_C;
        if (rn_sign == op2_sign && res_sign != rn_sign)
            new_flags |= FLAG_V;
    }
    cpsr |= new_flags;
}