ARDUINO_PATH=/opt/arduino

ARDUINO_PROJECT := $(wildcard *.ino)

all: build/$(ARDUINO_PROJECT).hex

build/%.ino.hex: %.ino
	mkdir -p build libraries
	$(ARDUINO_PATH)/arduino-builder -compile -logger=machine -hardware "$(ARDUINO_PATH)/hardware" -tools "$(ARDUINO_PATH)/tools-builder" -tools "$(ARDUINO_PATH)/hardware/tools/avr" -built-in-libraries "$(ARDUINO_PATH)/libraries" -libraries "$$PWD/libraries" -fqbn=arduino:avr:uno -ide-version=10607 -build-path "$$PWD/build" -warnings=none -prefs=build.warn_data_percentage=80 -verbose "$$PWD/$<"

clean:
	rm -rf build libraries
