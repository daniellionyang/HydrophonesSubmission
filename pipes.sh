#!/bin/bash

PIPES='
mission_in
mission_out
control_in
control_out
modeling_in
modeling_out
buoys_in
buoys_out
pvc_in
pvc_out
bins_in
bins_out
torps_in
torps_out
hydrophones_in
hydrophones_out
camera_f_in
camera_d_in
camera_f_out
camera_d_out
sim_in
render_f
render_d
image_f
image_d
'

echo ${PIPES} | sed 's/ /\n/g' | sed 's/^/pipe\//g'

