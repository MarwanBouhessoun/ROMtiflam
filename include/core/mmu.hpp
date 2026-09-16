/*
** PROJECT, 2026
** ROMtiflam
** File description:
** MMU
*/

#ifndef MMU_HPP
    #define MMU_HPP

    #include <cstdint>
    #include "macro.hpp"

class MMU {
private:
    // ram
    uint8_t main_ram[MAIN_RAM_SIZE]; // 4 Mo

    // Work ram
    uint8_t shared_wram[SHARED_WRAM_SIZE]; // 32 Ko
    uint8_t arm7_wram[ARM7_WRAM_SIZE]; // 64 Ko

    // Tightly coupled memory (memory fast asf)
    uint8_t itcm[ITCM_SIZE]; // instruction
    uint8_t dtcm[DTCM_SIZE]; // data

public:

    // constructor
    MMU() = default;
    ~MMU() = default;

    // read function
    uint8_t read8(uint32_t addr, bool is_arm9);
    uint16_t read16(uint32_t addr, bool is_arm9);
    uint32_t read32(uint32_t addr, bool is_arm9);

    // write function
    void write8(uint32_t addr, uint8_t val, bool is_arm9);
    void write16(uint32_t addr, uint16_t val, bool is_arm9);
    void write32(uint32_t addr, uint32_t val, bool is_arm9);
};

#endif
