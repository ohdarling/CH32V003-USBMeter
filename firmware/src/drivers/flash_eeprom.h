#pragma once

#include <ch32v00x.h>

#ifdef __cplusplus
extern "C" {
#endif

void ch32v_eeprom_load();
void ch32v_eeprom_read(u8 offset, u8 *buffer, u8 size);
void ch32v_eeprom_write(u8 offset, u8 *buffer, u8 size);

#ifdef __cplusplus
}
#endif
