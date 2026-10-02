/*
** EPITECH PROJECT, 2026
** ROMtiflam
** File description:
** execute branch
*/

#include "cpu/arm9.hpp"

void ARM9::execute_branch(uint32_t instruction) {

    bool link = (instruction & ARM_LINK_BIT) != 0;
    int32_t offset = 0;

    if (link)
        reg[14] = reg[15] - ARM_LR_ADJUST;
    offset = instruction & ARM_BRANCH_OFFSET_MASK;
    if (offset & ARM_BRANCH_SIGN_BIT)
        offset |= ~ARM_BRANCH_OFFSET_MASK;
    reg[15] = (reg[15] + ARM_PC_PREFETCH_SIZE) + (offset << ARM_BRANCH_OFFSET_SHIFT);
}
