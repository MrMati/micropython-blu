#include "py/runtime.h"
#include "py/objstr.h"
#include "py/obj.h"
#include "py/binary.h"
#include "py/objarray.h"
#include <string.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"

static uint32_t counter  = 0;


static void core1_code() {
    counter = 0;
    
    gpio_init(2);
    gpio_set_dir(2, GPIO_OUT);
    
    while (true) {
        gpio_put(2, 1);
        sleep_ms(1);
        counter++;
        gpio_put(2, 0);
        sleep_ms(1);
    }
}

static mp_obj_t core1_launch(void) {
    multicore_launch_core1(core1_code);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_0(core1_launch_obj, core1_launch);

static mp_obj_t core1_counter(void) {
    return mp_obj_new_int(counter);
}



static mp_obj_t core1_register(mp_obj_t variable) {
    return mp_const_none;
}

static mp_obj_t core1_print(void) {
    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_0(core1_counter_obj, core1_counter);
MP_DEFINE_CONST_FUN_OBJ_1(core1_register_obj, core1_register);
MP_DEFINE_CONST_FUN_OBJ_0(core1_print_obj, core1_print);

static const mp_rom_map_elem_t core1_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_core1)     },
    { MP_ROM_QSTR(MP_QSTR_launch),   MP_ROM_PTR(&core1_launch_obj)  },
    { MP_ROM_QSTR(MP_QSTR_counter),  MP_ROM_PTR(&core1_counter_obj) },
    { MP_ROM_QSTR(MP_QSTR_register), MP_ROM_PTR(&core1_register_obj) },
    { MP_ROM_QSTR(MP_QSTR_print), MP_ROM_PTR(&core1_print_obj) },
};

static MP_DEFINE_CONST_DICT(core1_module_globals,
                            core1_module_globals_table);

const mp_obj_module_t mp_module_core1 = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&core1_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_core1, mp_module_core1);
