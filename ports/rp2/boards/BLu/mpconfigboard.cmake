# cmake file for Raspberry Pi Pico W

set(PICO_BOARD "pico_w")

set(MICROPY_PY_LWIP ON)
set(MICROPY_PY_NETWORK_CYW43 ON)

# Bluetooth
set(MICROPY_PY_BLUETOOTH ON)
set(MICROPY_BLUETOOTH_BTSTACK ON)
set(MICROPY_PY_BLUETOOTH_CYW43 ON)

set(MICROPY_PY_TFT_ESPI ON)

# Needed for libstdc++ stuff
set(MICROPY_C_HEAP_SIZE 50*1024)

# Board specific version of the frozen manifest
set(MICROPY_FROZEN_MANIFEST ${MICROPY_BOARD_DIR}/manifest.py)
