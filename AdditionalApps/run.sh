#!/bin/bash

cd RssiAppSniffer && make upload && python read.py &
cd RssiApp2 && make upload && python read.py &
cd RssiApp && make upload && python read.py

echo "done"
