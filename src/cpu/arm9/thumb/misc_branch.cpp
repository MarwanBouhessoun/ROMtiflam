/*
** PROJECT, 2026
** ROMtiflam
** File description:
** misc branch
*/

#include <bit>
#include "cpu/arm9.hpp"

void ARM9::misc_branch_b(uint16_t instruction) {

    if (instruction & 0x0400) {
        bool is_pop = (instruction & 0x0800) != 0;
        bool pc_lr_bit = (instruction & 0x0100) != 0;
        uint32_t rlist = instruction & 0xFF;
        uint32_t num_regs = std::popcount(rlist) + pc_lr_bit;

        if (!is_pop) {
            uint32_t addr = reg[13] - (num_regs * 4);
            reg[13] = addr;
            for (int i = 0; i < 8; i++) {
                if (rlist & (1 << i)) {
                    mmu.write32(addr, reg[i], true);
                    addr += 4;
                }
            }
            if (pc_lr_bit) mmu.write32(addr, reg[14], true);
        } else {
            uint32_t addr = reg[13];
            for (int i = 0; i < 8; i++) {
                if (rlist & (1 << i)) {
                    reg[i] = mmu.read32(addr, true);
                    addr += 4;
                }
            }
            if (pc_lr_bit) {
                reg[15] = mmu.read32(addr, true) & ~1;
                addr += 4;
            }
            reg[13] = addr;
        }
    } else if ((instruction & 0x0F00) == 0x0000) {
        uint32_t imm7 = (instruction & 0x7F) << 2;
        reg[13] += (instruction & 0x80) ? -imm7 : imm7;
    }
}

void ARM9::misc_branch_c(uint16_t instruction) {

    bool is_load = (instruction & 0x0800) != 0;
    uint32_t rb = (instruction >> 8) & 0x7;
    uint32_t rlist = instruction & 0xFF;
    uint32_t addr = reg[rb];

    if (is_load) {
        for (int i = 0; i < 8; i++) {
            if (rlist & (1 << i)) {
                reg[i] = mmu.read32(addr, true);
                addr += 4;
            }
        }
    } else {
        for (int i = 0; i < 8; i++) {
            if (rlist & (1 << i)) {
                mmu.write32(addr, reg[i], true);
                addr += 4;
            }
        }
    }
    if (!(is_load && (rlist & (1 << rb))))
        reg[rb] = addr;
}

void ARM9::misc_branch_d(uint16_t instruction) {

    uint32_t cond = (instruction >> 8) & 0xF;

    if (cond != 0xF && check_condition(cond)) {
        int32_t offset = (static_cast<int32_t>(instruction << 24) >> 24);
        reg[15] += (offset << 1);
    }
}

void ARM9::misc_branch_e(uint16_t instruction) {

    int32_t offset = (static_cast<int32_t>((instruction & 0x7FF) << 21) >> 21);

    reg[15] += (offset << 1);
}

void ARM9::misc_branch_f(uint16_t instruction) {

    if ((instruction & 0x0800) == 0) {
        int32_t offset = (static_cast<int32_t>((instruction & 0x7FF) << 21) >> 21);

        reg[14] = reg[15] + (offset << 12);
    } else {
        uint32_t offset = (instruction & 0x7FF) << 1;
        uint32_t next_pc = reg[15] - 2;

        reg[15] = (reg[14] + offset) & ~1;
        reg[14] = next_pc | 1;
    }
}

void ARM9::execute_thumb_misc_branch(uint16_t instruction) {

    uint32_t opcode = instruction & 0xF000;

    switch (opcode) {
        case 0xB000: {
            misc_branch_b(instruction);
            break;
        }
        case 0xC000: {
            misc_branch_c(instruction);
            break;
        }
        case 0xD000: {
            misc_branch_d(instruction);
            break;
        }
        case 0xE000: {
            misc_branch_e(instruction);
            break;
        }
        case 0xF000: {
            misc_branch_f(instruction);
            break;
        }
    }
}
