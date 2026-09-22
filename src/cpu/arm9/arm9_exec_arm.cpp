/*
** PROJECT, 2026
** ROMtiflam
** File description:
** arm9 exec arm function
*/

#include <stdexcept>
#include "cpu/arm9.hpp"
#include "cpu/instruction.hpp"

void ARM9::execute_arm(uint32_t instruction) {

    uint32_t cond = (instruction >> 28) & 0xF;
    uint32_t category = 0;

    if (cond != COND_AL && !check_condition(cond))
        return;
    category = (instruction >> 25) & 0x7;
    switch (category) {
        case CAT_DATA_PROCESSING_1:
        case CAT_DATA_PROCESSING_2:
            execute_data_processing(instruction);
            break;
        case CAT_BRANCH:
            execute_branch(instruction);
            break;
        default: throw std::runtime_error("execute_arm (ARM9): Gros, cette instruction est inexistante...");
    }
}

void ARM9::execute_branch(uint32_t instruction) {

    bool link = (instruction & (1 << 24)) != 0;
    int32_t offset = 0;

    if (link)
        reg[14] = reg[15] - 4;
    offset = instruction & 0xFFFFFF;
    if (offset & 0x800000)
        offset |= ~0xFFFFFF;
    reg[15] = (reg[15] + 8) + (offset << 2);
}

uint32_t ARM9::decode_operand2(uint32_t instruction, bool& carry_out) {

    bool immediate = (instruction & ARM_IMM_BIT) != 0;
    uint32_t imm8 = 0;
    uint32_t rotate = 0;
    uint32_t rm = 0;

    if (immediate) {
        imm8 = instruction & 0xFF;
        rotate = ((instruction >> 8) & 0xF) * 2;
        if (rotate == 0)
            return imm8;
        return (imm8 >> rotate) | (imm8 << (32 - rotate));
    } else {
        rm = instruction & 0xF;
        return reg[rm];
    }
}

void ARM9::execute_data_processing(uint32_t instruction) {

    uint32_t opcode = (instruction >> 21) & 0xF;
    bool set_flags = (instruction & ARM_SET_S_BIT) != 0;
    uint32_t reg_src = (instruction >> 16) & 0xF;
    uint32_t reg_dest = (instruction >> 12) & 0xF;
    bool carry_out = (cpsr & FLAG_C) != 0;
    uint32_t op2 = decode_operand2(instruction, carry_out);
    uint32_t result = 0;
    bool update_rd = true;

    switch (opcode) {
        case OP_ADD:
            result = reg[reg_src] + op2;
            if (set_flags) update_arithmetic_flags(reg[reg_src], op2, result, false);
            break;
        case OP_SUB:
            result = reg[reg_src] - op2;
            if (set_flags) update_arithmetic_flags(reg[reg_src], op2, result, false);
            break;
        case OP_MOV:
            result = op2;
            if (set_flags) update_logic_flags(result, carry_out);
            break;
        case OP_CMP:
            result = reg[reg_src] - op2;
            update_rd = false;
            if (set_flags) update_arithmetic_flags(reg[reg_src], op2, result, true);
            break;
        default: throw std::runtime_error("Execute_data_processing (ARM9) : Chef, tu t'es tromper d'opcode, je le connais pas celui la.");
    }
    if (update_rd)
        reg[reg_dest] = result;
}

void ARM9::update_logic_flags(uint32_t result, bool carry_out) {

    cpsr &= ~(FLAG_N | FLAG_Z | FLAG_C);

    uint32_t new_flags = 0;

    new_flags |= (result & FLAG_N);
    if (result == 0) new_flags |= FLAG_Z;
    if (carry_out) new_flags |= FLAG_C;

    cpsr |= new_flags;
}

void ARM9::update_arithmetic_flags(uint32_t rn, uint32_t op2, uint32_t result, bool is_subtraction) {

    cpsr &= ~(FLAG_N | FLAG_Z | FLAG_C | FLAG_V);

    uint32_t new_flags = 0;

    new_flags |= (result & FLAG_N);
    if (result == 0)
        new_flags |= FLAG_Z;

    bool rn_sign = (rn & FLAG_N) != 0;
    bool op2_sign = (op2 & FLAG_N) != 0;
    bool res_sign = (result & FLAG_N) != 0;

    if (is_subtraction) {
        if (rn >= op2)
            new_flags |= FLAG_C;
        if (rn_sign != op2_sign && res_sign != rn_sign)
            new_flags |= FLAG_V;
    } else {
        if (result < rn)
            new_flags |= FLAG_C;
        if (rn_sign == op2_sign && res_sign != rn_sign)
            new_flags |= FLAG_V;
    }
    cpsr |= new_flags;
}