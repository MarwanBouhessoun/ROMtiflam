/*
** PROJECT, 2026
** ROMtiflam
** File description:
** arm9 context function
*/

#include "cpu/arm9.hpp"

int ARM9::get_bank_index(uint32_t mode) {

    switch(mode) {
        case MODE_USER:
        case MODE_SYS: return 0;
        case MODE_FIQ: return 1;
        case MODE_IRQ: return 2;
        case MODE_SVC: return 3;
        case MODE_ABORT: return 4;
        case MODE_UNDEF: return 5;
        default: return 0;
    }
}

bool ARM9::check_condition(uint32_t cond) {

    bool n = (cpsr & (1 << 31)) != 0;
    bool z = (cpsr & (1 << 30)) != 0;
    bool c = (cpsr & (1 << 29)) != 0;
    bool v = (cpsr & (1 << 28)) != 0;

    switch (cond) {
        case COND_EQ: return z;
        case COND_NE: return !z;
        case COND_CS: return c;
        case COND_CC: return !c;
        case COND_MI: return n;
        case COND_PL: return !n;
        case COND_VS: return v;
        case COND_VC: return !v;
        case COND_HI: return c && !z;
        case COND_LS: return !c || z;
        case COND_GE: return (n == v);
        case COND_LT: return (n != v);
        case COND_GT: return !z && (n == v);
        case COND_LE: return z || (n != v);
        case COND_AL: return true;
        case COND_NV: return false;
        default: return false;
    }
}

void ARM9::switch_mode(uint32_t new_mode) {

    uint32_t old_mode = cpsr & 0x1F;

    if (old_mode == new_mode)
        return;

    int old_idx = get_bank_index(old_mode);

    banks[old_idx].r13 = reg[13];
    banks[old_idx].r14 = reg[14];

    if (old_mode == MODE_FIQ) {
        for (int i = 0; i < 5; i++) {
            fiq_r8_r12[i] = reg[8 + i];
            reg[8 + i] = user_r8_r12[i];
        }
    } else if (new_mode == MODE_FIQ) {
        for (int i = 0; i < 5; i++) {
            user_r8_r12[i] = reg[8 + i];
            reg[8 + i] = fiq_r8_r12[i];
        }
    }

    int new_idx = get_bank_index(new_mode);

    reg[13] = banks[new_idx].r13;
    reg[14] = banks[new_idx].r14;
    cpsr = (cpsr & ~0x1F) | new_mode;
}