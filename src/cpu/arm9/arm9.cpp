/*
** PROJECT, 2026
** ROMtiflam
** File description:
** arm9
*/

#include "cpu/arm9.hpp"
#include "core/mmu.hpp"

ARM9::ARM9(MMU& memory) : mmu(memory) {
    reset();
}

void ARM9::step() {

    uint32_t pc = reg[15];
    bool is_thumb = (cpsr & 0x20) != 0;
    uint32_t instruction = 0;

    if (is_thumb) {
        instruction = mmu.read16(pc, true);
        reg[15] += 2;
    } else {
        instruction = mmu.read32(pc, true);
        reg[15] += 4;
    }

}

int ARM9::get_bank_index(uint32_t mode) {

    switch(mode) {
        case MODE_FIQ: return 0;
        case MODE_IRQ: return 1;
        case MODE_SVC: return 2;
        case MODE_ABORT: return 3;
        case MODE_UNDEF: return 4;
        default: return NO_MODE;
    }
}

void ARM9::switch_mode(uint32_t new_mode) {

    uint32_t old_mode = cpsr & 0x1F;
    int old_idx = 0;
    int new_idx = 0;
    bool old_is_fiq = false;
    bool new_is_fiq = false;

    if (old_mode == new_mode)
        return;
    old_idx = get_bank_index(old_mode);
    new_idx = get_bank_index(new_mode);
    if (old_idx != NO_MODE) {
        banks[old_idx].r13 = reg[13];
        banks[old_idx].r14 = reg[14];
    } else {
        user_r13 = reg[13];
        user_r14 = reg[14];
    }
    old_is_fiq = (old_mode == MODE_FIQ);
    new_is_fiq = (new_mode == MODE_FIQ);
    if (old_is_fiq && !new_is_fiq) {
        for (int i = 0; i < 5; i++) {
            fiq_r8_r12[i] = reg[8 + i];
            reg[8 + i] = user_r8_r12[i];
        }
    } else if (!old_is_fiq && new_is_fiq) {
        for (int i = 0; i < 5; i++) {
            user_r8_r12[i] = reg[8 + i];
            reg[8 + i] = fiq_r8_r12[i];
        }
    }
    if (new_idx != NO_MODE) {
        reg[13] = banks[new_idx].r13;
        reg[14] = banks[new_idx].r14;
    } else {
        reg[13] = user_r13;
        reg[14] = user_r14;
    }
    cpsr = (cpsr & ~0x1F) | new_mode;
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