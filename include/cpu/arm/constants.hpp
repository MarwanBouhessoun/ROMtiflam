/*
** PROJECT, 2026
** ROMtiflam
** File description:
** ARM constants, flags and modes
*/

#ifndef ARM_CONSTANTS_HPP
    #define ARM_CONSTANTS_HPP

    #include <cstdint>

    #define NO_MODE -1

constexpr uint32_t FLAG_N = (1 << 31); // Negative
constexpr uint32_t FLAG_Z = (1 << 30); // Zero
constexpr uint32_t FLAG_C = (1 << 29); // Carry
constexpr uint32_t FLAG_V = (1 << 28); // Overflow

constexpr uint32_t ARM_IMM_BIT = (1 << 25);
constexpr uint32_t ARM_SET_S_BIT = (1 << 20);
constexpr uint32_t ARM_LINK_BIT = (1 << 24);

constexpr uint32_t THUMB_REG_MASK = 0x7;

constexpr uint32_t ARM_IMM8_MASK = 0xFF;
constexpr uint32_t ARM_ROTATE_MASK = 0xF;
constexpr uint32_t ARM_REGISTER_MASK = 0xF;
constexpr uint8_t ARM_ROTATE_SHIFT = 8;
constexpr uint8_t ARM_WORD_SIZE_BITS = 32;
constexpr uint8_t ARM_NO_ROTATION = 0;

constexpr uint8_t ARM_COND_SHIFT = 28;
constexpr uint8_t ARM_COND_MASK = 0xF;
constexpr uint8_t ARM_CATEGORY_SHIFT = 25;
constexpr uint8_t ARM_CATEGORY_MASK = 0x7;

constexpr uint32_t ARM_BRANCH_OFFSET_MASK = 0xFFFFFF;
constexpr uint32_t ARM_BRANCH_SIGN_BIT = 0x800000;
constexpr uint8_t ARM_BRANCH_OFFSET_SHIFT = 2;
constexpr uint8_t ARM_PC_PREFETCH_SIZE = 8;
constexpr uint8_t ARM_LR_ADJUST = 4;

constexpr uint8_t ARM_OPCODE_SHIFT = 21;
constexpr uint8_t ARM_OPCODE_MASK = 0xF;
constexpr uint8_t ARM_RN_SHIFT = 16;
constexpr uint8_t ARM_RD_SHIFT = 12;

constexpr uint16_t THUMB_ADD_SUB_MODE_BIT = 0x0400;
constexpr uint16_t THUMB_ADD_SUB_OP_BIT = 0x0200;
constexpr uint8_t THUMB_RN_SHIFT = 6;
constexpr uint8_t THUMB_RS_SHIFT = 3;

constexpr uint8_t THUMB_OPCODE_SHIFT = 11;
constexpr uint8_t THUMB_OPCODE_MASK = 0x3;
constexpr uint8_t THUMB_OFFSET5_MASK = 0x1F;
constexpr uint8_t THUMB_OFFSET5_SHIFT = 6;
constexpr uint8_t THUMB_RD_SHIFT = 8;
constexpr uint8_t THUMB_RD_MASK = 0x7;
constexpr uint8_t THUMB_IMM8_MASK = 0xFF;
constexpr uint32_t THUMB_PC_ALIGN_MASK = ~0x2;
constexpr uint8_t THUMB_PC_ALIGN_SHIFT = 2;
constexpr uint32_t THUMB_ALIGN_WORD = ~0x3u;
constexpr uint32_t THUMB_ALIGN_HALFWORD = ~0x1u;
constexpr uint8_t THUMB_FORMAT_SHIFT = 12;
constexpr uint8_t THUMB_FORMAT_MASK = 0xF;
constexpr uint8_t THUMB_SIGN_BIT_BYTE = 0x80;
constexpr uint32_t THUMB_SIGN_EXTEND_BYTE = 0xFFFFFF00;
constexpr uint16_t THUMB_SIGN_BIT_HALFWORD = 0x8000;
constexpr uint32_t THUMB_SIGN_EXTEND_HALFWORD = 0xFFFF0000;
constexpr uint16_t THUMB_PUSH_POP_BIT = 0x0400;
constexpr uint16_t THUMB_POP_BIT = 0x0800;
constexpr uint16_t THUMB_PC_LR_BIT = 0x0100;
constexpr uint8_t THUMB_RLIST_MASK = 0xFF;
constexpr uint8_t THUMB_REGISTER_SIZE = 4;
constexpr uint16_t THUMB_SP_ADJUST_MASK = 0x0F00;
constexpr uint8_t THUMB_IMM7_MASK = 0x7F;
constexpr uint8_t THUMB_IMM7_SHIFT = 2;
constexpr uint8_t THUMB_SIGN_BIT = 0x80;
constexpr uint8_t THUMB_COND_SHIFT = 8;
constexpr uint8_t THUMB_COND_MASK = 0xF;
constexpr uint8_t THUMB_SIGN_EXTEND_SHIFT = 24;
constexpr uint16_t THUMB_OFFSET_MASK = 0x7FF;
constexpr uint8_t THUMB_BL_OFFSET_SHIFT = 12;
constexpr uint8_t THUMB_THUMB_BIT = 1;
constexpr uint16_t THUMB_OPCODE_MASK_HIGH = 0xF000;
constexpr uint8_t THUMB_ALU_OPCODE_SHIFT = 6;
constexpr uint8_t THUMB_ALU_OPCODE_MASK = 0xF;
constexpr uint8_t THUMB_SHIFT_VAL_MASK = 0xFF;
constexpr uint8_t THUMB_REGISTER_BYTE_SIZE = 4;

enum arm_mode {
    MODE_USER = 0x10,
    MODE_FIQ = 0x11, // fast interrupt
    MODE_IRQ = 0x12, // standard interrupt
    MODE_SVC = 0x13, // supervisor (software interrupts)
    MODE_ABORT = 0x17, // memory abort
    MODE_UNDEF = 0x1B, // undefined instruction
    MODE_SYS = 0x1F  // system mode
};

// ARM condition codes
enum arm_condition {
    COND_EQ = 0x0, // equal
    COND_NE = 0x1, // not equal
    COND_CS = 0x2, // carry set / higher or same
    COND_CC = 0x3, // carry clear / lower
    COND_MI = 0x4, // minus / negative
    COND_PL = 0x5, // plus / positive or zero
    COND_VS = 0x6, // overflow
    COND_VC = 0x7, // no overflow
    COND_HI = 0x8, // unsigned higher
    COND_LS = 0x9, // unsigned lower or same
    COND_GE = 0xA, // signed greater than or equal
    COND_LT = 0xB, // signed less than
    COND_GT = 0xC, // signed greater than
    COND_LE = 0xD, // signed less than or equal
    COND_AL = 0xE, // always
    COND_NV = 0xF  // never
};

#endif
