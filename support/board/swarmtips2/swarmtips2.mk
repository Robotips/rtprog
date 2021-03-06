
DEVICE = 32MZ2048EFH064
ARCHI = pic32mzef

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += i2c pwm

SRC += swarmtips2.c motors.c
HEADER += swarmtips2.h motors.h
ARCHI_SRC += swarmtips2_fuses.c
