#include "py/binary.h"
#include "py/obj.h"
#include "py/objarray.h"
#include "py/objstr.h"
#include "py/runtime.h"

#include "modcore1.h"

static mp_obj_t core1_launch(void) {
  if (launch_interface()) {
    mp_raise_msg_varg(&mp_type_RuntimeError,
                      MP_ERROR_TEXT("Core1 task already started"));
  }
  return mp_const_none;
}

static mp_obj_t check_error(int ret) {
  if (ret == 0)
    return mp_const_none;

  if (ret == 1) {
    mp_raise_msg_varg(&mp_type_RuntimeError, MP_ERROR_TEXT("Cmd FIFO full"));
  } else if (ret == 2) {
    mp_raise_msg_varg(&mp_type_RuntimeError, MP_ERROR_TEXT("Core1 not launched"));
  }

  mp_raise_msg_varg(&mp_type_Exception, MP_ERROR_TEXT("Unknown Error"));
  return mp_const_none;
}

static mp_obj_t core1_set_color(mp_obj_t colorVal) {
  int color = mp_obj_get_int(colorVal);
  int ret = set_color_interface(color);

  return check_error(ret);
}

static mp_obj_t core1_set_slot(mp_obj_t slotVal) {
  int slot = mp_obj_get_int(slotVal);
  int ret = set_slot_interface(slot);

  return check_error(ret);
}

static mp_obj_t core1_set_view(mp_obj_t viewVal) {
  int view = mp_obj_get_int(viewVal);
  int ret = set_view_interface(view);

  return check_error(ret);
}

static mp_obj_t core1_set_sensor_status(mp_obj_t sensorStatusVal) {
  int sensorStatus = mp_obj_get_int(sensorStatusVal);
  int ret = set_sensor_status_interface(sensorStatus);

  return check_error(ret);
}

MP_DEFINE_CONST_FUN_OBJ_0(core1_launch_obj, core1_launch);
MP_DEFINE_CONST_FUN_OBJ_1(core1_set_color_obj, core1_set_color);
MP_DEFINE_CONST_FUN_OBJ_1(core1_set_slot_obj, core1_set_slot);
MP_DEFINE_CONST_FUN_OBJ_1(core1_set_view_obj, core1_set_view);
MP_DEFINE_CONST_FUN_OBJ_1(core1_set_sensor_status_obj, core1_set_sensor_status);


static const mp_rom_map_elem_t core1_module_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_core1)},
    {MP_ROM_QSTR(MP_QSTR_launch), MP_ROM_PTR(&core1_launch_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_color), MP_ROM_PTR(&core1_set_color_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_slot), MP_ROM_PTR(&core1_set_slot_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_view), MP_ROM_PTR(&core1_set_view_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_sensor_status), MP_ROM_PTR(&core1_set_sensor_status_obj)},
};

static MP_DEFINE_CONST_DICT(core1_module_globals, core1_module_globals_table);

const mp_obj_module_t mp_module_core1 = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&core1_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_core1, mp_module_core1);
