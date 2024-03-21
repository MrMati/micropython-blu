#include "py/runtime.h"
#include "py/objstr.h"
#include "py/obj.h"
#include "py/binary.h"
#include "py/objarray.h"

#include "modcore1.h"


static mp_obj_t core1_launch(void) {
    if(launch_interface()) {
        mp_obj_t exc = mp_obj_new_exception_msg(&mp_type_RuntimeError,
            MP_ERROR_TEXT("Core1 task already started"));
        nlr_raise(exc);
    
    }
    return mp_const_none;
}

static mp_obj_t core1_register(mp_obj_t variable) {
    return mp_obj_new_int(2 * mp_obj_get_int(variable));
}

static mp_obj_t core1_print(void) {
    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_0(core1_launch_obj, core1_launch);
MP_DEFINE_CONST_FUN_OBJ_1(core1_register_obj, core1_register);
MP_DEFINE_CONST_FUN_OBJ_0(core1_print_obj, core1_print);

static const mp_rom_map_elem_t core1_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_core1)     },
    { MP_ROM_QSTR(MP_QSTR_launch),   MP_ROM_PTR(&core1_launch_obj)  },
    { MP_ROM_QSTR(MP_QSTR_register), MP_ROM_PTR(&core1_register_obj) },
    { MP_ROM_QSTR(MP_QSTR_print),    MP_ROM_PTR(&core1_print_obj) },
};

static MP_DEFINE_CONST_DICT(core1_module_globals,
                            core1_module_globals_table);

const mp_obj_module_t mp_module_core1 = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&core1_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_core1, mp_module_core1);
