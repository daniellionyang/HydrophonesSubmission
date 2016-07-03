#!/bin/bash

trap "exit" INT TERM
trap "echo caught exit signal; kill 0" EXIT

tee pipe/image_f < pipe/render_f | bin/image_show 5 &
tee pipe/image_d < pipe/render_d | bin/image_show 5 &

bin/camera_pipe pipe/image_f < pipe/camera_f_in > pipe/camera_f_out &
bin/camera_pipe pipe/image_d < pipe/camera_d_in > pipe/camera_d_out &

bin/sim_state < pipe/control_in > pipe/control_out

