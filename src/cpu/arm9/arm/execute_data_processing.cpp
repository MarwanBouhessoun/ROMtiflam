/*
** EPITECH PROJECT, 2026
** ROMtiflam
** File description:
** execute data processing
*/

#include <stdexcept>
#include "cpu/arm9.hpp"

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
