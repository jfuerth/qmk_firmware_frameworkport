RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = is31fl3743a

# Trying to use low-level RGB LED driver instead of RGB_MATRIX feature
#COMMON_VPATH += $(DRIVER_PATH)/led/issi
#SRC += is31fl3743a.c
#I2C_DRIVER_REQUIRED = yes

CUSTOM_MATRIX = lite
