#!/bin/sh

trap "exit" INT TERM
trap "echo caught exit signal; kill 0" EXIT

cat pipe/mission_in  | bin/mission  | cat > pipe/mission_out  &
cat pipe/modeling_in | bin/modeling | cat > pipe/modeling_out &

bin/interface

