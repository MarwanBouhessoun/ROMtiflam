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
        imm8 = instruction & 0xFF;
        rotate = ((instruction >> 8) & 0xF) * 2;
        if (rotate == 0)
            return imm8;
        return (imm8 >> rotate) | (imm8 << (32 - rotate));
    } else {
        rm = instruction & 0xF;
        return reg[rm];
    }
}
