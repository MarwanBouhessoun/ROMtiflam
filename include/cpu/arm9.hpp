/*
** PROJECT, 2026
** ROMtiflam
** File description:
** ARM9 processor class
*/

#ifndef ARM9_HPP
    #define ARM9_HPP

    #include <cstdint>
    #include "core/mmu.hpp"
    #include "cpu/arm/constants.hpp"
    #include "cpu/arm/opcodes.hpp"

class ARM9;

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
    void execute_load_store_byte_word(uint32_t address, uint32_t rd, bool is_load, bool is_byte);

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
        { 0xF000, 0xB000, &ARM9::execute_thumb_misc_branch },
        { 0xF000, 0xC000, &ARM9::execute_thumb_misc_branch },
        { 0xF000, 0xD000, &ARM9::execute_thumb_misc_branch },
        { 0xF000, 0xE000, &ARM9::execute_thumb_misc_branch },
        { 0xF000, 0xF000, &ARM9::execute_thumb_misc_branch }
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
