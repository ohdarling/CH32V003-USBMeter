#include "flash_eeprom.h"

#include <string.h>
#include <ch32v00x_flash.h>

#define EEPROM_ADDR ((u32)(0x08003FC0))
#define CH32V003_PAGE_SIZE 64

u8 FLASH_BUF[CH32V003_PAGE_SIZE] = { 0 };

void ch32v_eeprom_load() {
    memcpy(FLASH_BUF, (u8 *)EEPROM_ADDR, CH32V003_PAGE_SIZE);
}

void ch32v_eeprom_read(u8 offset, u8 *buffer, u8 size) {
    memcpy(buffer, (FLASH_BUF + offset), size);
}

void ch32v_eeprom_write(u8 offset, u8 *buffer, u8 size) {
    FLASH_Unlock_Fast();
    FLASH_ErasePage_Fast(EEPROM_ADDR);

    memcpy(FLASH_BUF, buffer, size);

    for (int i = 0; i < CH32V003_PAGE_SIZE; i += 4) {
        FLASH_ProgramWord(EEPROM_ADDR + i, *(u32 *)(FLASH_BUF + i));
    }

    FLASH_ProgramPage_Fast(EEPROM_ADDR);
    FLASH_Lock_Fast();
}

