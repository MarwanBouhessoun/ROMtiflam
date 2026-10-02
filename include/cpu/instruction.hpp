/*
** PROJECT, 2026
** ROMtiflam
** File description:
** instruction macro
*/

#ifndef INSTRUCTION_HPP
    #define INSTRUCTION_HPP

enum thumb_instruction_category{
    THUMB_CAT_SHIFT_REG = 0b000,
    THUMB_CAT_ADD_SUB = 0b001,
    THUMB_CAT_IMM_OPS = 0b010,
    THUMB_CAT_ALU_REG = 0b011,
    THUMB_CAT_LDR_LITERAL = 0b100,
    THUMB_CAT_LOAD_STORE = 0b101,
    THUMB_CAT_LOAD_STORE_IMM = 0b110,
    THUMB_CAT_MISC_BRANCH = 0b111
};

enum arm_instruction_category{
    CAT_DATA_PROCESSING_1 = 0b000,
    CAT_DATA_PROCESSING_2 = 0b001,
    CAT_LOAD_STORE_IMM = 0b010,
    CAT_LOAD_STORE_REG = 0b011,
    CAT_BLOCK_TRANSFER = 0b100,
    CAT_BRANCH = 0b101,
    CAT_COPROC_LOAD = 0b110,
    CAT_COPROC_OR_SWI = 0b111
};

enum thumb_shift_opcode {
    THUMB_SHIFT_LSL = 0b00,
    THUMB_SHIFT_LSR = 0b01,
    THUMB_SHIFT_ASR = 0b10
};

#endif
