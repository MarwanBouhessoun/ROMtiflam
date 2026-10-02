/*
** PROJECT, 2026
** ROMtiflam
** File description:
** ldr literal
*/

#include "cpu/arm9.hpp"
#include "cpu/instruction.hpp"

void ARM9::execute_thumb_ldr_literal(uint16_t instruction) {

    uint32_t rd = (instruction >> THUMB_RD_SHIFT) & THUMB_RD_MASK;
    uint32_t imm8 = instruction & THUMB_IMM8_MASK;
    uint32_t pc_aligned = reg[15] & THUMB_PC_ALIGN_MASK;
    uint32_t address = pc_aligned + (imm8 << THUMB_PC_ALIGN_SHIFT);

    reg[rd] = mmu.read32(address, true);
}
