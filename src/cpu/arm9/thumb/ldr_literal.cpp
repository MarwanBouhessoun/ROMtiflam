/*
** PROJECT, 2026
** ROMtiflam
** File description:
** ldr literal
*/

#include "cpu/arm9.hpp"
#include "cpu/instruction.hpp"

void ARM9::execute_thumb_ldr_literal(uint16_t instruction) {
    uint32_t rd = (instruction >> 8) & 0x7;
    uint32_t imm8 = instruction & 0xFF;
    uint32_t pc_aligned = reg[15] & ~0x2;
    uint32_t address = pc_aligned + (imm8 << 2);

    reg[rd] = mmu.read32(address, true);
}
