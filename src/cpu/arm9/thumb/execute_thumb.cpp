/*
** PROJECT, 2026
** ROMtiflam
** File description:
** execute thumb
*/

#include <iostream>
#include "cpu/arm9.hpp"

void ARM9::build_thumb_lut() {
    constexpr size_t def_count = sizeof(thumb_definitions) / sizeof(thumb_opcode_def_thumb);

    for (int i = 0; i < 256; ++i) {
        uint16_t opcode = i << 8;

        thumb_lut[i] = &ARM9::execute_unknown;

        for (size_t j = 0; j < def_count; ++j) {
            if ((opcode & thumb_definitions[j].mask) == thumb_definitions[j].pattern) {
                thumb_lut[i] = thumb_definitions[j].handler;
                break;
            }
        }
    }
}

void ARM9::execute_thumb(uint16_t instruction) {
    uint8_t index = static_cast<uint8_t>(instruction >> 8);

    (this->*thumb_lut[index])(instruction);
}

void ARM9::execute_unknown(uint16_t instruction) {
    std::cerr << "Erreur : Instruction Thumb inconnue ou non implémentée : 0x"
            << std::hex << instruction << std::endl;
    std::exit(1);
}