ifeq ($(OS),Windows_NT)
	ARDUINO_PATH = ${ProgramFiles(x86)}\Arduino
	MKDIR = mkdir $(subst /,\,$(1)) > nul 2>&1 || (exit 0)
	RM = $(wordlist 2,65535,$(foreach FILE,$(subst /,\,$(1)),& del /f /q $(FILE) > nul 2>&1)) || (exit 0)
	RMDIR = rmdir $(subst /,\,$(1)) > nul 2>&1 || (exit 0)
	ECHO = @echo $(1)
else
	ARDUINO_BIN = $(shell readlink -f `which arduino`)
	ARDUINO_PATH = $(shell dirname "$(ARDUINO_BIN)")
	MKDIR = mkdir -p $(1)
	RM = rm -f $(1) > /dev/null 2>&1 || true
	RMDIR = rmdir $(1) > /dev/null 2>&1 || true
	ECHO = @echo "$(1)"
endif

ARDUINO_PROJECT := $(wildcard *.ino)

all: build/$(ARDUINO_PROJECT).hex

build/%.ino.hex: %.ino
	$(call MKDIR,build libraries)
	"$(ARDUINO_PATH)/arduino-builder" -compile -logger=machine -hardware "$(ARDUINO_PATH)/hardware" -tools "$(ARDUINO_PATH)/tools-builder" -tools "$(ARDUINO_PATH)/hardware/tools/avr" -built-in-libraries "$(ARDUINO_PATH)/libraries" -libraries "$(CURDIR)/libraries" -fqbn=arduino:avr:uno -ide-version=10607 -build-path "$(CURDIR)/build" -warnings=none -prefs=build.warn_data_percentage=80 -verbose "$(CURDIR)/$<"

clean:
	$(call RM,build/core/* build/libraries/EEPROM/* build/libraries/* build/preproc/* build/sketch/* build/* libraries/*)
	$(call RMDIR,build/core build/libraries/EEPROM build/libraries build/preproc build/sketch build libraries)

test:
	$(call ECHO,$(CURDIR))
	$(call ECHO,$(ARDUINO_PATH))
