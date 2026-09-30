/*
** PROJECT, 2026
** ROMtiflam
** File description:
** read
*/

#include "core/mmu.hpp"

uint8_t MMU::read8(uint32_t addr, bool is_arm9) {

    uint8_t type = addr >> 24;
    uint32_t offset = 0;

    switch (type) {
        case 0x00: {
            if (is_arm9) {
                offset = addr & ITCM_MASK;
                return itcm[offset];
            }
            break;
        }
        case 0x02: {
            if (is_arm9 && addr >= DTCM_START && addr < DTCM_END) {
                offset = addr & DTCM_MASK;
                return dtcm[offset];
            } else {
                offset = addr & MAIN_RAM_MASK;
                return main_ram[offset];
            }
            break;
        }
        case 0x03: {
            if (addr >= ARM7_WRAM_START) {
                offset = addr & ARM7_WRAM_MASK;
                return arm7_wram[offset];
            } else {
                offset = addr & SHARED_WRAM_MASK;
                return shared_wram[offset];
            }
            break;
        }
        default: break;
    }
    return 0;
}

uint16_t MMU::read16(uint32_t addr, bool is_arm9) {

    uint8_t type = addr >> 24;
    uint32_t offset = 0;

    if (addr & 1)
        return 0;
    switch (type) {
        case 0x00: {
            if (is_arm9) {
                offset = addr & ITCM_MASK;
                return itcm[offset] | (itcm[offset + 1] << 8);
            }
            break;
        }
        case 0x02: {
            if (is_arm9 && addr >= DTCM_START && addr < DTCM_END) {
                offset = addr & DTCM_MASK;
                return dtcm[offset] | (dtcm[offset + 1] << 8);
            } else {
                offset = addr & MAIN_RAM_MASK;
                return main_ram[offset] | (main_ram[offset + 1] << 8);
            }
            break;
        }
        case 0x03: {
            if (addr >= ARM7_WRAM_START && addr < ARM7_WRAM_END) {
                offset = addr & ARM7_WRAM_MASK;
                return arm7_wram[offset] | (arm7_wram[offset + 1] << 8);
            } else {
                offset = addr & SHARED_WRAM_MASK;
                return shared_wram[offset] | (shared_wram[offset + 1] << 8);
            }
            break;
        }
        default: break;
    }
    return 0;
}

uint32_t MMU::read32(uint32_t addr, bool is_arm9) {

    uint8_t type = addr >> 24;
    uint32_t offset = 0;

    if (addr & 3)
        return 0;
    switch (type) {
        case 0x00: {
            if (is_arm9) {
                offset = addr & ITCM_MASK;
                return itcm[offset] | (itcm[offset + 1] << 8) | (itcm[offset + 2] << 16) | (itcm[offset + 3] << 24);
            }
            break;
        }
        case 0x02: {
            if (is_arm9 && addr >= DTCM_START && addr < DTCM_END) {
                offset = addr & DTCM_MASK;
                return dtcm[offset] | (dtcm[offset + 1] << 8) | (dtcm[offset + 2] << 16) | (dtcm[offset + 3] << 24);
            } else {
                offset = addr & MAIN_RAM_MASK;
                return main_ram[offset] | (main_ram[offset + 1] << 8) | (main_ram[offset + 2] << 16) | (main_ram[offset + 3] << 24);
            }
            break;
        }
        case 0x03: {
            if (addr >= ARM7_WRAM_START && addr < ARM7_WRAM_END) {
                offset = addr & ARM7_WRAM_MASK;
                return arm7_wram[offset] | (arm7_wram[offset + 1] << 8) | (arm7_wram[offset + 2] << 16) | (arm7_wram[offset + 3] << 24);
            } else {
                offset = addr & SHARED_WRAM_MASK;
                return shared_wram[offset] | (shared_wram[offset + 1] << 8) | (shared_wram[offset + 2] << 16) | (shared_wram[offset + 3] << 24);
            }
            break;
        }
        default: break;
    }
    return 0;
}
