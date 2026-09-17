/*
** PROJECT, 2026
** ROMtiflam
** File description:
** MMU
*/

#ifndef MMU_HPP
    #define MMU_HPP

    #include <cstdint>

// main ram
constexpr uint32_t MAIN_RAM_START = 0x02000000;
constexpr uint32_t MAIN_RAM_SIZE = 4 * 1024 * 1024; // 4 Mo
constexpr uint32_t MAIN_RAM_END = MAIN_RAM_START + MAIN_RAM_SIZE;
constexpr uint32_t MAIN_RAM_MASK = MAIN_RAM_SIZE - 1;

// shared wram
constexpr uint32_t SHARED_WRAM_START = 0x03000000;
constexpr uint32_t SHARED_WRAM_SIZE = 32 * 1024; // 32 Ko
constexpr uint32_t SHARED_WRAM_END = SHARED_WRAM_START + SHARED_WRAM_SIZE;
constexpr uint32_t SHARED_WRAM_MASK = SHARED_WRAM_SIZE - 1;

// arm7 wram
constexpr uint32_t ARM7_WRAM_START = 0x03800000;
constexpr uint32_t ARM7_WRAM_SIZE = 64 * 1024; // 64 Ko
constexpr uint32_t ARM7_WRAM_END = ARM7_WRAM_START + ARM7_WRAM_SIZE;
constexpr uint32_t ARM7_WRAM_MASK = ARM7_WRAM_SIZE - 1;

// itcm
constexpr uint32_t ITCM_START = 0x00000000;
constexpr uint32_t ITCM_SIZE = 32 * 1024; // 32 Ko
constexpr uint32_t ITCM_END = ITCM_START + ITCM_SIZE;
constexpr uint32_t ITCM_MASK = ITCM_SIZE - 1;

// dtcm
constexpr uint32_t DTCM_START = 0x027C0000;
constexpr uint32_t DTCM_SIZE = 16 * 1024; // 16 Ko
constexpr uint32_t DTCM_END = DTCM_START + DTCM_SIZE;
constexpr uint32_t DTCM_MASK = DTCM_SIZE - 1;

// pc

constexpr uint32_t INITIAL_PC =  0xFFFF0000;

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
