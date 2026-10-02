/*
** PROJECT, 2026
** ROMtiflam
** File description:
** load store
*/

#include "cpu/arm9.hpp"

static constexpr uint32_t ALIGN_WORD = THUMB_ALIGN_WORD;
static constexpr uint32_t ALIGN_HALFWORD = THUMB_ALIGN_HALFWORD;

static uint32_t extract_bits(uint16_t instruction, uint8_t offset, uint8_t mask) {
    return (instruction >> offset) & mask;
}

static bool test_bit(uint16_t instruction, uint8_t bit) {
    return (instruction & (1 << bit)) != 0;
}

static uint32_t sign_extend_byte(uint8_t value) {
    return (value & THUMB_SIGN_BIT_BYTE) ? (value | THUMB_SIGN_EXTEND_BYTE) : value;
}

static uint32_t sign_extend_halfword(uint16_t value) {
    return (value & THUMB_SIGN_BIT_HALFWORD) ? (value | THUMB_SIGN_EXTEND_HALFWORD) : value;
}

void ARM9::execute_load_store_byte_word(uint32_t address, uint32_t rd, bool is_load, bool is_byte) {
    if (is_load) {
        reg[rd] = is_byte ? mmu.read8(address, true) : mmu.read32(address & ALIGN_WORD, true);
    } else {
        if (is_byte) mmu.write8(address, reg[rd] & 0xFF, true);
        else mmu.write32(address & ALIGN_WORD, reg[rd], true);
    }
}

void ARM9::execute_thumb_load_store_imm(uint16_t instruction) {
    uint32_t rd = extract_bits(instruction, 0, THUMB_RD_MASK);
    uint32_t rb = extract_bits(instruction, 3, THUMB_RD_MASK);
    uint32_t imm5 = extract_bits(instruction, THUMB_OFFSET5_SHIFT, THUMB_OFFSET5_MASK);
    uint32_t format = extract_bits(instruction, THUMB_FORMAT_SHIFT, THUMB_FORMAT_MASK);

    if (format == 0b0110 || format == 0b0111) {
        bool is_byte = test_bit(instruction, THUMB_FORMAT_SHIFT);
        bool is_load = test_bit(instruction, 11);
        uint32_t address = reg[rb] + (is_byte ? imm5 : (imm5 << 2));
        execute_load_store_byte_word(address, rd, is_load, is_byte);
    } else if (format == 0b1000) {
        bool is_load = test_bit(instruction, 11);
        uint32_t address = reg[rb] + (imm5 << 1);

        if (is_load) reg[rd] = mmu.read16(address & ALIGN_HALFWORD, true);
        else mmu.write16(address & ALIGN_HALFWORD, reg[rd] & 0xFFFF, true);
    } else if (format == 0b1001) {
        bool is_load = test_bit(instruction, 11);
        uint32_t imm8 = instruction & THUMB_IMM8_MASK;
        rd = extract_bits(instruction, THUMB_RD_SHIFT, THUMB_RD_MASK);
        uint32_t address = reg[13] + (imm8 << 2);

        if (is_load) reg[rd] = mmu.read32(address & ALIGN_WORD, true);
        else mmu.write32(address & ALIGN_WORD, reg[rd], true);
    }
}

void ARM9::execute_thumb_load_store(uint16_t instruction) {
    uint32_t rd = extract_bits(instruction, 0, THUMB_RD_MASK);
    uint32_t rb = extract_bits(instruction, 3, THUMB_RD_MASK);
    uint32_t ro = extract_bits(instruction, 6, THUMB_RD_MASK);
    uint32_t address = reg[rb] + reg[ro];
    bool is_extended = test_bit(instruction, 9);

    if (!is_extended) {
        bool is_load = test_bit(instruction, 11);
        bool is_byte = test_bit(instruction, 10);
        execute_load_store_byte_word(address, rd, is_load, is_byte);

    } else {
        bool is_halfword = test_bit(instruction, 11);
        bool is_sign_ext = test_bit(instruction, 10);

        if (!is_sign_ext && !is_halfword) {
            mmu.write16(address & ALIGN_HALFWORD, reg[rd] & 0xFFFF, true);
        } else if (!is_sign_ext && is_halfword) {
            reg[rd] = mmu.read16(address & ALIGN_HALFWORD, true);
        } else if (is_sign_ext && !is_halfword) {
            uint8_t val = mmu.read8(address, true);
            reg[rd] = sign_extend_byte(val);
        } else {
            uint16_t val = mmu.read16(address & ALIGN_HALFWORD, true);
            reg[rd] = sign_extend_halfword(val);
        }
    }
}