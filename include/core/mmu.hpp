/*
** PROJECT, 2026
** ROMtiflam
** File description:
** MMU
*/

#ifndef MMU_HPP
    #define MMU_HPP

    #include <cstdint>

class MMU {
private:
    // ram
    uint8_t ram[4 * 1024 * 1024]; // 4 Mo

    // Work ram
    uint8_t shared_wram[32* 1024]; // 32 Ko
    uint8_t arm7_wram[64 * 1024]; // 64 Ko

    // Tightly coupled memory (memory fast asf)
    uint8_t itcm[32 * 1024]; // instruction
    uint8_t dtcm[16 * 1024]; // data

public:
    MMU();
    ~MMU();
};

#endif
