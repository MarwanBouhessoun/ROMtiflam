/*
** PROJECT, 2026
** ROMtiflam
** File description:
** misc branch
*/

#include <bit>
#include "cpu/arm9.hpp"

void ARM9::misc_branch_b(uint16_t instruction) {

    if (instruction & THUMB_PUSH_POP_BIT) {
        bool is_pop = (instruction & THUMB_POP_BIT) != 0;
        bool pc_lr_bit = (instruction & THUMB_PC_LR_BIT) != 0;
        uint32_t rlist = instruction & THUMB_RLIST_MASK;
        uint32_t num_regs = std::popcount(rlist) + pc_lr_bit;

        if (!is_pop) {
            uint32_t addr = reg[13] - (num_regs * THUMB_REGISTER_SIZE);
            reg[13] = addr;
            for (int i = 0; i < 8; i++) {
                if (rlist & (1 << i)) {
                    mmu.write32(addr, reg[i], true);
                    addr += THUMB_REGISTER_SIZE;
                }
            }
            if (pc_lr_bit) mmu.write32(addr, reg[14], true);
        } else {
            uint32_t addr = reg[13];
            for (int i = 0; i < 8; i++) {
                if (rlist & (1 << i)) {
                    reg[i] = mmu.read32(addr, true);
                    addr += THUMB_REGISTER_SIZE;
                }
            }
            if (pc_lr_bit) {
                reg[15] = mmu.read32(addr, true) & ~THUMB_THUMB_BIT;
                addr += THUMB_REGISTER_SIZE;
            }
            reg[13] = addr;
        }
    } else if ((instruction & THUMB_SP_ADJUST_MASK) == 0x0000) {
        uint32_t imm7 = (instruction & THUMB_IMM7_MASK) << THUMB_IMM7_SHIFT;
        reg[13] += (instruction & THUMB_SIGN_BIT) ? -imm7 : imm7;
    }
}

void ARM9::misc_branch_c(uint16_t instruction) {

    bool is_load = (instruction & 0x0800) != 0;
    uint32_t rb = (instruction >> THUMB_RD_SHIFT) & THUMB_RD_MASK;
    uint32_t rlist = instruction & THUMB_RLIST_MASK;
    uint32_t addr = reg[rb];

    if (is_load) {
        for (int i = 0; i < 8; i++) {
            if (rlist & (1 << i)) {
                reg[i] = mmu.read32(addr, true);
                addr += THUMB_REGISTER_BYTE_SIZE;
            }
        }
    } else {
        for (int i = 0; i < 8; i++) {
            if (rlist & (1 << i)) {
                mmu.write32(addr, reg[i], true);
                addr += THUMB_REGISTER_BYTE_SIZE;
            }
        }
    }
    if (!(is_load && (rlist & (1 << rb))))
        reg[rb] = addr;
}

void ARM9::misc_branch_d(uint16_t instruction) {

    uint32_t cond = (instruction >> THUMB_COND_SHIFT) & THUMB_COND_MASK;

    if (cond != 0xF && check_condition(cond)) {
        int32_t offset = (static_cast<int32_t>(instruction << THUMB_SIGN_EXTEND_SHIFT) >> THUMB_SIGN_EXTEND_SHIFT);
        reg[15] += (offset << 1);
    }
}

void ARM9::misc_branch_e(uint16_t instruction) {

    int32_t offset = (static_cast<int32_t>((instruction & THUMB_OFFSET_MASK) << THUMB_SIGN_EXTEND_SHIFT) >> THUMB_SIGN_EXTEND_SHIFT);

    reg[15] += (offset << 1);
}

void ARM9::misc_branch_f(uint16_t instruction) {

    if ((instruction & 0x0800) == 0) {
        int32_t offset = (static_cast<int32_t>((instruction & THUMB_OFFSET_MASK) << THUMB_SIGN_EXTEND_SHIFT) >> THUMB_SIGN_EXTEND_SHIFT);

        reg[14] = reg[15] + (offset << THUMB_BL_OFFSET_SHIFT);
    } else {
        uint32_t offset = (instruction & THUMB_OFFSET_MASK) << 1;
        uint32_t next_pc = reg[15] - 2;

        reg[15] = (reg[14] + offset) & ~THUMB_THUMB_BIT;
        reg[14] = next_pc | THUMB_THUMB_BIT;
    }
}

void ARM9::execute_thumb_misc_branch(uint16_t instruction) {

    uint32_t opcode = instruction & THUMB_OPCODE_MASK_HIGH;

    switch (opcode) {
        case 0xB000: misc_branch_b(instruction);
            break;
        case 0xC000: misc_branch_c(instruction);
            break;
        case 0xD000: misc_branch_d(instruction);
            break;
        case 0xE000: misc_branch_e(instruction);
            break;
        case 0xF000: misc_branch_f(instruction);
            break;
    }
}
