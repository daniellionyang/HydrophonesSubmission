#!/bin/bash

trap "exit" INT TERM
trap "echo caught exit signal; kill 0" EXIT

stty -F /dev/ttyUSB0 raw
stty -F /dev/ttyUSB0 speed 9600
stty -F /dev/ttyUSB0 -echo -echoe -echok

cat /dev/ttyUSB0 > pipe/control_out &
cat pipe/control_in > /dev/ttyUSB0 &

bin/camera i 0 1 < pipe/camera_f_in | tee pipe/camera_f_out > /ram/images &

cat
