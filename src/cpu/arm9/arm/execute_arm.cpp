/*
** PROJECT, 2026
** ROMtiflam
** File description:
** execute arm
*/

#include <stdexcept>
#include "cpu/arm9.hpp"
#include "cpu/instruction.hpp"

void ARM9::execute_arm(uint32_t instruction) {

    uint32_t cond = (instruction >> ARM_COND_SHIFT) & ARM_COND_MASK;
    uint32_t category = 0;

    if (cond != COND_AL && !check_condition(cond))
        return;
    category = (instruction >> ARM_CATEGORY_SHIFT) & ARM_CATEGORY_MASK;
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
