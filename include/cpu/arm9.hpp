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
class ARM9;

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

enum arm_mode {
    MODE_USER = 0x10,
    MODE_FIQ = 0x11, // fast interrupt
    MODE_IRQ = 0x12, // standard interrupt
    MODE_SVC = 0x13, // supervisor (software interrupts)
    MODE_ABORT = 0x17, // memory abort
    MODE_UNDEF = 0x1B, // undefined instruction
    MODE_SYS = 0x1F  // system mode
};

constexpr uint32_t FLAG_N = (1 << 31); // Negative
constexpr uint32_t FLAG_Z = (1 << 30); // Zero
constexpr uint32_t FLAG_C = (1 << 29); // Carry
constexpr uint32_t FLAG_V = (1 << 28); // Overflow

constexpr uint32_t ARM_IMM_BIT = (1 << 25);
constexpr uint32_t ARM_SET_S_BIT = (1 << 20);
constexpr uint32_t ARM_LINK_BIT = (1 << 24);

constexpr uint32_t THUMB_REG_MASK = 0x7;
struct exception_bank_t {

    uint32_t r13;
    uint32_t r14;
    uint32_t spsr;

};

struct thumb_opcode_def_thumb {
    uint16_t mask;
    uint16_t pattern;
    void (ARM9::*handler)(uint16_t);
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

    using ThumbHandler = void (ARM9::*)(uint16_t);
    ThumbHandler thumb_lut[256];

    int get_bank_index(uint32_t mode);
    bool check_condition(uint32_t cond);
    void execute_branch(uint32_t instruction);
    void execute_data_processing(uint32_t instruction);
    uint32_t decode_operand2(uint32_t instruction, bool& carry_out);
    void update_logic_flags(uint32_t result, bool carry);
    void update_arithmetic_flags(uint32_t rn, uint32_t op2, uint32_t result, bool is_subtraction);
    void execute_thumb_shift_reg(uint16_t instruction);
    void execute_thumb_add_sub(uint16_t instruction);
    void execute_thumb_imm_ops(uint16_t instruction);
    void execute_thumb_alu_reg(uint16_t instruction);
    void execute_thumb_ldr_literal(uint16_t instruction);
    void execute_thumb_load_store(uint16_t instruction);
    void execute_thumb_load_store_imm(uint16_t instruction);
    void execute_thumb_misc_branch(uint16_t instruction);
    void build_thumb_lut();
    void execute_unknown(uint16_t instruction);
    void misc_branch_b(uint16_t instruction);
    void misc_branch_c(uint16_t instruction);
    void misc_branch_d(uint16_t instruction);
    void misc_branch_e(uint16_t instruction);
    void misc_branch_f(uint16_t instruction);



static constexpr thumb_opcode_def_thumb thumb_definitions[] = {
    { 0xF800, 0x1800, &ARM9::execute_thumb_add_sub },
    { 0xE000, 0x0000, &ARM9::execute_thumb_shift_reg },
    { 0xE000, 0x2000, &ARM9::execute_thumb_imm_ops },
    { 0xFC00, 0x4000, &ARM9::execute_thumb_alu_reg },
    { 0xF800, 0x4800, &ARM9::execute_thumb_ldr_literal },
    { 0xF000, 0x5000, &ARM9::execute_thumb_load_store },
    { 0xE000, 0x6000, &ARM9::execute_thumb_load_store_imm },
    { 0xF000, 0x8000, &ARM9::execute_thumb_load_store_imm },
    { 0xF000, 0x9000, &ARM9::execute_thumb_load_store_imm },
    { 0xF000, 0xB000, &ARM9::execute_thumb_misc_branch }
    };

public:
    ARM9(MMU& memory);
    ~ARM9() = default;

    void execute_arm(uint32_t instruction);
    void execute_thumb(uint16_t instruction);
    void switch_mode(uint32_t new_mode);
    void reset();
    uint32_t get_cpsr();
    void set_cpsr(uint32_t val);
    uint32_t get_reg(int reg_idx);
    void set_reg(int reg_idx, uint32_t reg_val);
    void step();

};

#endif
