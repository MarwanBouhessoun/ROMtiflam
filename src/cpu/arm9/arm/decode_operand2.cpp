/*
** EPITECH PROJECT, 2026
** ROMtiflam
** File description:
** decode op2
*/

#include "cpu/arm9.hpp"

uint32_t ARM9::decode_operand2(uint32_t instruction, bool& carry_out) {

    bool immediate = (instruction & ARM_IMM_BIT) != 0;
    uint32_t imm8 = 0;
    uint32_t rotate = 0;
    uint32_t rm = 0;

    if (immediate) {
        imm8 = instruction & ARM_IMM8_MASK;
        rotate = ((instruction >> ARM_ROTATE_SHIFT) & ARM_ROTATE_MASK) * 2;
        if (rotate == ARM_NO_ROTATION)
            return imm8;
        return (imm8 >> rotate) | (imm8 << (ARM_WORD_SIZE_BITS - rotate));
    } else {
        rm = instruction & ARM_REGISTER_MASK;
        return reg[rm];
    }
}
