#!/usr/bin/env sh

DIR=/tmp/bio_signal_converter_v$1_$2_$3
mkdir $DIR
cp ./build/partition_table/partition-table.bin $DIR
cp ./build/bootloader/bootloader.bin $DIR
cp ./build/bio-signal-converter.bin $DIR
tar -czf $DIR.tar.gz $DIR
