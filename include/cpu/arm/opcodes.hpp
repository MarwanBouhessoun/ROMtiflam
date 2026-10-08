/*
** PROJECT, 2026
** ROMtiflam
** File description:
** ARM and Thumb instruction opcodes
*/

#ifndef ARM_OPCODES_HPP
    #define ARM_OPCODES_HPP

enum imm_ops {
    MOV = 0,
    CMP = 1,
    ADD = 2,
    SUB = 3
};

enum arm_data_processing_opcode {

    OP_AND = 0b0000,
    OP_EOR = 0b0001,
    OP_SUB = 0b0010,
    OP_RSB = 0b0011,
    OP_ADD = 0b0100,
    OP_ADC = 0b0101,
    OP_SBC = 0b0110,
    OP_RSC = 0b0111,
    OP_TST = 0b1000,
    OP_TEQ = 0b1001,
    OP_CMP = 0b1010,
    OP_CMN = 0b1011,
    OP_ORR = 0b1100,
    OP_MOV = 0b1101,
    OP_BIC = 0b1110,
    OP_MVN = 0b1111
};

enum thumb_opcode {

    THUMB_AND = 0x0,
    THUMB_EOR = 0x1,
    THUMB_LSL = 0x2,
    THUMB_LSR = 0x3,
    THUMB_ASR = 0x4,
    THUMB_ADC = 0x5,
    THUMB_SBC = 0x6,
    THUMB_ROR = 0x7,
    THUMB_TST = 0x8,
    THUMB_NEG = 0x9,
    THUMB_CMP = 0xA,
    THUMB_CMN = 0xB,
    THUMB_ORR = 0xC,
    THUMB_MUL = 0xD,
    THUMB_BIC = 0xE,
    THUMB_MVN = 0xF,
};

#endif
