#!/bin/sh

trap "exit" INT TERM
trap "echo caught exit signal; kill 0" EXIT

cat pipe/render_f | bin/image_show &
cat pipe/render_d | bin/image_show &

cat pipe/control_in | bin/sim_state | cat > pipe/control_out

