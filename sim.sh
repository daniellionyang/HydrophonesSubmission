#!/bin/sh

trap "exit" INT TERM
trap "echo caught exit signal; kill 0" EXIT

bin/image_show < pipe/render_f &
bin/image_show < pipe/render_d &

bin/sim_state < pipe/control_in > pipe/control_out

