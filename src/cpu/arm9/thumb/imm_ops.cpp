/*
** PROJECT, 2026
** ROMtiflam
** File description:
** imm & ops
*/

#include "cpu/arm9.hpp"

void ARM9::execute_thumb_imm_ops(uint16_t instruction) {

    uint32_t opcode = (instruction >> THUMB_OPCODE_SHIFT) & THUMB_OPCODE_MASK;
    uint32_t rd = (instruction >> THUMB_RD_SHIFT) & THUMB_RD_MASK;
    uint32_t imm = instruction & THUMB_IMM8_MASK;
    uint32_t val = reg[rd];

    switch (opcode) {
        case MOV:
            reg[rd] = imm;
            cpsr = (cpsr & ~(FLAG_N | FLAG_Z)) | ((imm == 0) ? FLAG_Z : 0);
            break;
        case CMP:
            update_arithmetic_flags(val, imm, val - imm, true);
            break;
        case ADD:
            reg[rd] = val + imm;
            update_arithmetic_flags(val, imm, val + imm, false);
            break;
        case SUB:
            reg[rd] = val - imm;
            update_arithmetic_flags(val, imm, val - imm, true);
            break;
    }
}