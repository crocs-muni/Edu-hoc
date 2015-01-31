#!/usr/bin/env bash

SCRIPTS_DIR=$(dirname -- $(readlink -f -- "$0"))

CWD=$(readlink -f "$SCRIPTS_DIR/..")
SRC="$CWD/src"
TEST="$CWD/test"
ARDMK="$CWD/Arduino-Makefile"
EDU_HOC_HOME="SCRIPTS_DIR/.."

AVR_GCC="/usr/local/share/avr-gcc"
ARDUINO="/usr/local/share/arduino"

source "$SCRIPTS_DIR/install.sh"
