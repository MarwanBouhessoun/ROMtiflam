/*
** PROJECT, 2026
** ROMtiflam
** File description:
** write
*/

#include <cstdint>
#include "core/mmu.hpp"

void MMU::write8(uint32_t addr, uint8_t val, bool is_arm9) {

    uint8_t type = addr >> 24;
    uint32_t offset = 0;

    switch (type) {
        case 0x00: {
            if (is_arm9) {
                offset = addr & ITCM_MASK;
                itcm[offset] = val;
            }
            break;
        }
        case 0x02: {
            if (is_arm9 && addr >= DTCM_START && addr < DTCM_END) {
                offset = addr & DTCM_MASK;
                dtcm[offset] = val;
            } else {
                offset = addr & MAIN_RAM_MASK;
                main_ram[offset] = val;
            }
            break;
        }
        case 0x03: {
            if (addr >= ARM7_WRAM_START) {
                offset = addr & ARM7_WRAM_MASK;
                arm7_wram[offset] = val;
            } else {
                offset = addr & SHARED_WRAM_MASK;
                shared_wram[offset] = val;
            }
            break;
        }
        default: break;
    }
}

void MMU::write16(uint32_t addr, uint16_t val, bool is_arm9) {

    uint8_t type = addr >> 24;
    uint32_t offset = 0;

    if (addr & 1)
        return;
    switch (type) {
        case 0x00: {
            if (is_arm9) {
                offset = addr & ITCM_MASK;
                *reinterpret_cast<uint16_t *>(&itcm[offset]) = val;
            }
            break;
        }
        case 0x02: {
            if (is_arm9 && addr >= DTCM_START && addr < DTCM_END) {
                offset = addr & DTCM_MASK;
                *reinterpret_cast<uint16_t *>(&dtcm[offset]) = val;
            } else {
                offset = addr & MAIN_RAM_MASK;
                *reinterpret_cast<uint16_t *>(&main_ram[offset]) = val;
            }
            break;
        }
        case 0x03: {
            if (addr >= ARM7_WRAM_START) {
                offset = addr & ARM7_WRAM_MASK;
                *reinterpret_cast<uint16_t *>(&arm7_wram[offset]) = val;
            } else {
                offset = addr & SHARED_WRAM_MASK;
                *reinterpret_cast<uint16_t *>(&shared_wram[offset]) = val;
            }
            break;
        }
        default: break;
    }
}

void MMU::write32(uint32_t addr, uint32_t val, bool is_arm9) {

    uint8_t type = addr >> 24;
    uint32_t offset = 0;

    if (addr & 3)
        return;
    switch (type) {
        case 0x00: {
            if (is_arm9) {
                offset = addr & ITCM_MASK;
                *reinterpret_cast<uint32_t*>(&itcm[offset]) = val;
            }
            break;
        }
        case 0x02: {
            if (is_arm9 && addr >= DTCM_START && addr < DTCM_END) {
                offset = addr & DTCM_MASK;
                *reinterpret_cast<uint32_t *>(&dtcm[offset]) = val;
            } else {
                offset = addr & MAIN_RAM_MASK;
                *reinterpret_cast<uint32_t *>(&main_ram[offset]) = val;
            }
            break;
        }
        case 0x03: {
            if (addr >= ARM7_WRAM_START) {
                offset = addr & ARM7_WRAM_MASK;
                *reinterpret_cast<uint32_t *>(&arm7_wram[offset]) = val;
            } else {
                offset = addr & SHARED_WRAM_MASK;
                *reinterpret_cast<uint32_t *>(&shared_wram[offset]) = val;
            }
            break;
        }
        default: break;
    }
}