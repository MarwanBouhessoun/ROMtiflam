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
