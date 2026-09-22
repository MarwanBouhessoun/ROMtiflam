/*
** PROJECT, 2026
** ROMtiflam
** File description:
** arm9
*/

#include "cpu/arm9.hpp"
#include "core/mmu.hpp"
#include "cpu/instruction.hpp"

ARM9::ARM9(MMU& memory) : mmu(memory) {
    build_thumb_lut();
    reset();
}

void ARM9::step() {

    uint32_t pc = reg[15];
    bool is_thumb = (cpsr & 0x20) != 0;
    uint32_t instruction = 0;

    if (is_thumb) {
        instruction = mmu.read16(pc, true);
        reg[15] += 2;
        execute_thumb(instruction);
    } else {
        instruction = mmu.read32(pc, true);
        reg[15] += 4;
        execute_arm(instruction);
    }

}

void ARM9::reset() {

    for (int i = 0; i < 15; i++)
        reg[i] = 0;
    cpsr = MODE_SVC | 0x80 | 0x40;
    user_r13 = 0;
    user_r14 = 0;
    for (int i = 0; i < 5; i++) {
        banks[i].r13 = 0;
        banks[i].r14 = 0;
        banks[i].spsr = 0;
        fiq_r8_r12[i] = 0;
        user_r8_r12[i] = 0;
    }
    reg[15] = INITIAL_PC;
}

uint32_t ARM9::get_cpsr() {
    return cpsr;
}

uint32_t ARM9::get_reg(int reg_idx) {
    return reg[reg_idx];
}

void ARM9::set_reg(int reg_idx, uint32_t reg_val) {
    reg[reg_idx] = reg_val;
}

void ARM9::set_cpsr(uint32_t val) {
    cpsr = val;
}