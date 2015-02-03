#!/usr/bin/env bash

set -e



SCRIPTS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd $SCRIPTS_DIR/..

CWD=$(readlink -f "$SCRIPTS_DIR/..")
SRC="$CWD/src"

AVR_GCC="/usr/local/share/avr-gcc"
ARDUINO="/usr/local/share/arduino"

source $SCRIPTS_DIR/bootstrap/chipkit.sh
source $SCRIPTS_DIR/bootstrap/arduino.sh
