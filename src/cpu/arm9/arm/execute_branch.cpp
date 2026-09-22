/*
** EPITECH PROJECT, 2026
** ROMtiflam
** File description:
** execute branch
*/

#include "cpu/arm9.hpp"

void ARM9::execute_branch(uint32_t instruction) {

    bool link = (instruction & (1 << 24)) != 0;
    int32_t offset = 0;

    if (link)
        reg[14] = reg[15] - 4;
    offset = instruction & 0xFFFFFF;
    if (offset & 0x800000)
        offset |= ~0xFFFFFF;
    reg[15] = (reg[15] + 8) + (offset << 2);
}
