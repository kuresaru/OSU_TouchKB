######################################
# 把这块的改一下
######################################

# GCC路径
#GCC_PATH = /home/kuresaru/gcc-arm-none-eabi-8-2018-q4-major/bin

# 目标名字
TARGET = STM32F103RCT6

# 输出文件夹
BUILD_DIR = build

# C源 用到的库什么的都写在这
C_SOURCES =  \
User/main.c \
User/common.c \
User/km.c \
User/hw_config.c \
User/usb_desc.c \
User/usb_endp.c \
User/usb_istr.c \
User/usb_prop.c \
User/usb_pwr.c \
User/stm32_it.c \
USB/src/usb_core.c \
USB/src/usb_init.c \
USB/src/usb_int.c \
USB/src/usb_mem.c \
USB/src/usb_regs.c \
USB/src/usb_sil.c \
CMSIS/CM3/CoreSupport/core_cm3.c \
CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c \
Libraries/src/misc.c \
Libraries/src/stm32f10x_gpio.c \
Libraries/src/stm32f10x_rcc.c \
Libraries/src/stm32f10x_exti.c

######################################



# ASM sources
ASM_SOURCES =  \
Startup/startup_stm32f103xe.s

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
#OPT = -Og


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_STDPERIPH_DRIVER \
-DSTM32F10X_MD


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-ICMSIS/CM3/CoreSupport \
-ICMSIS/CM3/DeviceSupport/ST/STM32F10x \
-ILibraries/inc \
-ILibraries/src \
-IStartup \
-IUser \
-IUSB/inc

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F103RCTx_FLASH.ld

# libraries
#LIBS = -lc -lm -lnosys 
LIBS = -lc
LIBDIR = 
#LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
LDFLAGS = $(MCU) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***