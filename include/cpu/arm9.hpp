/*
** PROJECT, 2026
** ROMtiflam
** File description:
** arm9
*/

#ifndef ARM9_HPP
    #define ARM9_HPP

    #include <cstdint>
    #include "core/mmu.hpp"

    #define NO_MODE -1

enum arm_mode {
    MODE_USER  = 0x10,
    MODE_FIQ   = 0x11, // fast interrupt
    MODE_IRQ   = 0x12, // standard interrupt
    MODE_SVC   = 0x13, // supervisor (software interrupts)
    MODE_ABORT = 0x17, // memory abort
    MODE_UNDEF = 0x1B, // undefined instruction
    MODE_SYS   = 0x1F  // system mode
};

struct exception_bank_t {

    uint32_t r13;
    uint32_t r14;
    uint32_t spsr;

};

class ARM9 {
private:
    uint32_t reg[16];
    uint32_t cpsr;
    exception_bank_t banks[5];
    uint32_t fiq_r8_r12[5];
    uint32_t user_r8_r12[5];
    uint32_t user_r13;
    uint32_t user_r14;
    MMU& mmu;

    int get_bank_index(uint32_t mode);

public:
    ARM9(MMU& memory);
    ~ARM9() = default;

    void switch_mode(uint32_t new_mode);
    void reset();
    uint32_t get_cpsr();
    uint32_t get_reg(int reg_idx);
    void set_reg(int reg_idx, uint32_t reg_val);
    void step();

};

#endif
