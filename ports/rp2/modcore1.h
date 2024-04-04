#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int launch_interface();
int set_color_interface(uint32_t);
int set_slot_interface(uint8_t);
int set_view_interface(uint8_t);
int set_sensor_status_interface(uint8_t);

#ifdef __cplusplus
} // extern "C"
#endif
