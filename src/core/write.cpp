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
                itcm[offset] = val & 0xFF;
                itcm[offset + 1] = (val >> 8) & 0xFF;
            }
            break;
        }
        case 0x02: {
            if (is_arm9 && addr >= DTCM_START && addr < DTCM_END) {
                offset = addr & DTCM_MASK;
                dtcm[offset] = val & 0xFF;
                dtcm[offset + 1] = (val >> 8) & 0xFF;
            } else {
                offset = addr & MAIN_RAM_MASK;
                main_ram[offset] = val & 0xFF;
                main_ram[offset + 1] = (val >> 8) & 0xFF;
            }
            break;
        }
        case 0x03: {
            if (addr >= ARM7_WRAM_START) {
                offset = addr & ARM7_WRAM_MASK;
                arm7_wram[offset] = val & 0xFF;
                arm7_wram[offset + 1] = (val >> 8) & 0xFF;
            } else {
                offset = addr & SHARED_WRAM_MASK;
                shared_wram[offset] = val & 0xFF;
                shared_wram[offset + 1] = (val >> 8) & 0xFF;
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
                itcm[offset] = val & 0xFF;
                itcm[offset + 1] = (val >> 8) & 0xFF;
                itcm[offset + 2] = (val >> 16) & 0xFF;
                itcm[offset + 3] = (val >> 24) & 0xFF;
            }
            break;
        }
        case 0x02: {
            if (is_arm9 && addr >= DTCM_START && addr < DTCM_END) {
                offset = addr & DTCM_MASK;
                dtcm[offset] = val & 0xFF;
                dtcm[offset + 1] = (val >> 8) & 0xFF;
                dtcm[offset + 2] = (val >> 16) & 0xFF;
                dtcm[offset + 3] = (val >> 24) & 0xFF;
            } else {
                offset = addr & MAIN_RAM_MASK;
                main_ram[offset] = val & 0xFF;
                main_ram[offset + 1] = (val >> 8) & 0xFF;
                main_ram[offset + 2] = (val >> 16) & 0xFF;
                main_ram[offset + 3] = (val >> 24) & 0xFF;
            }
            break;
        }
        case 0x03: {
            if (addr >= ARM7_WRAM_START) {
                offset = addr & ARM7_WRAM_MASK;
                arm7_wram[offset] = val & 0xFF;
                arm7_wram[offset + 1] = (val >> 8) & 0xFF;
                arm7_wram[offset + 2] = (val >> 16) & 0xFF;
                arm7_wram[offset + 3] = (val >> 24) & 0xFF;
            } else {
                offset = addr & SHARED_WRAM_MASK;
                shared_wram[offset] = val & 0xFF;
                shared_wram[offset + 1] = (val >> 8) & 0xFF;
                shared_wram[offset + 2] = (val >> 16) & 0xFF;
                shared_wram[offset + 3] = (val >> 24) & 0xFF;
            }
            break;
        }
        default: break;
    }
}
