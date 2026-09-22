/*
** PROJECT, 2026
** ROMtiflam
** File description:
** imm & ops
*/

#include "cpu/arm9.hpp"

void ARM9::execute_thumb_imm_ops(uint16_t instruction) {

    uint32_t opcode = (instruction >> 11) & 0x3;
    uint32_t rd = (instruction >> 8) & THUMB_REG_MASK;
    uint32_t imm = (instruction & 0xFF);
    uint32_t val = reg[rd];

    switch (opcode) {
        case MOV:
            reg[rd] = imm;
            cpsr &= ~FLAG_N;
            if (imm == 0) cpsr |= FLAG_Z;
            else cpsr &= ~FLAG_Z;
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