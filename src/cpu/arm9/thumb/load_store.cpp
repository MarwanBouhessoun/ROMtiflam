/*
** PROJECT, 2026
** ROMtiflam
** File description:
** load store
*/

#include "cpu/arm9.hpp"

void ARM9::execute_thumb_load_store_imm(uint16_t instruction) {
    uint32_t rd = instruction & 0x7;
    uint32_t rb = (instruction >> 3) & 0x7;
    uint32_t imm5 = (instruction >> 6) & 0x1F;
    uint32_t format = (instruction >> 12) & 0xF;

    if (format == 0b0110 || format == 0b0111) {
        bool is_byte = (instruction & (1 << 12)) != 0;
        bool is_load = (instruction & (1 << 11)) != 0;
        uint32_t address = reg[rb] + (is_byte ? imm5 : (imm5 << 2));

        if (is_load) reg[rd] = is_byte ? mmu.read8(address, true) : mmu.read32(address & ~0x3, true);
        else {
            if (is_byte) mmu.write8(address, reg[rd] & 0xFF, true);
            else mmu.write32(address & ~0x3, reg[rd], true);
        }
    } else if (format == 0b1000) {
        bool is_load = (instruction & (1 << 11)) != 0;
        uint32_t address = reg[rb] + (imm5 << 1);

        if (is_load) reg[rd] = mmu.read16(address & ~0x1, true);
        else mmu.write16(address & ~0x1, reg[rd] & 0xFFFF, true);
    } else if (format == 0b1001) {
        bool is_load = (instruction & (1 << 11)) != 0;
        uint32_t imm8 = instruction & 0xFF;
        rd = (instruction >> 8) & 0x7;
        uint32_t address = reg[13] + (imm8 << 2);

        if (is_load) reg[rd] = mmu.read32(address & ~0x3, true);
        else mmu.write32(address & ~0x3, reg[rd], true);
    }
}

void ARM9::execute_thumb_load_store(uint16_t instruction) {
    uint32_t rd = instruction & 0x7;
    uint32_t rb = (instruction >> 3) & 0x7;
    uint32_t ro = (instruction >> 6) & 0x7;
    uint32_t address = reg[rb] + reg[ro];
    bool is_extended = (instruction & (1 << 9)) != 0;

    if (!is_extended) {
        bool is_load = (instruction & (1 << 11)) != 0;
        bool is_byte = (instruction & (1 << 10)) != 0;
        if (is_load) {
            reg[rd] = is_byte ? mmu.read8(address, true) : mmu.read32(address & ~0x3, true);
        } else {
            if (is_byte) mmu.write8(address, reg[rd] & 0xFF, true);
            else mmu.write32(address & ~0x3, reg[rd], true);
        }
    } else {
        bool is_halfword = (instruction & (1 << 11)) != 0;
        bool is_sign_ext = (instruction & (1 << 10)) != 0;
        if (!is_sign_ext && !is_halfword) {
            mmu.write16(address & ~0x1, reg[rd] & 0xFFFF, true);
        } else if (!is_sign_ext && is_halfword) {
            reg[rd] = mmu.read16(address & ~0x1, true);
        } else if (is_sign_ext && !is_halfword) {
            uint8_t val = mmu.read8(address, true);
            reg[rd] = (val & 0x80) ? (val | 0xFFFFFF00) : val;
        } else {
            uint16_t val = mmu.read16(address & ~0x1, true);
            reg[rd] = (val & 0x8000) ? (val | 0xFFFF0000) : val;
        }
    }
}
