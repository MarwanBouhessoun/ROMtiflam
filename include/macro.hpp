/*
** PROJECT, 2026
** ROMtiflam
** File description:
** macro
*/

#ifndef MACRO_HPP
    #define MACRO_HPP

#include <cstdint>

// main ram
constexpr uint32_t MAIN_RAM_START = 0x02000000;
constexpr uint32_t MAIN_RAM_SIZE = 4 * 1024 * 1024; // 4 Mo
constexpr uint32_t MAIN_RAM_END = MAIN_RAM_START + MAIN_RAM_SIZE;

// shared wram
constexpr uint32_t SHARED_WRAM_START = 0x03000000;
constexpr uint32_t SHARED_WRAM_SIZE = 32 * 1024; // 32 Ko
constexpr uint32_t SHARED_WRAM_END = SHARED_WRAM_START + SHARED_WRAM_SIZE;

// arm7 wram
constexpr uint32_t ARM7_WRAM_START = 0x03800000;
constexpr uint32_t ARM7_WRAM_SIZE = 64 * 1024; // 64 Ko
constexpr uint32_t ARM7_WRAM_END = ARM7_WRAM_START + ARM7_WRAM_SIZE;

// itcm
constexpr uint32_t ITCM_START = 0x00000000;
constexpr uint32_t ITCM_SIZE = 32 * 1024; // 32 Ko
constexpr uint32_t ITCM_END = ITCM_START + ITCM_SIZE;

// dtcm
constexpr uint32_t DTCM_START = 0x027C0000;
constexpr uint32_t DTCM_SIZE = 16 * 1024; // 16 Ko
constexpr uint32_t DTCM_END = DTCM_START + DTCM_SIZE;

#endif