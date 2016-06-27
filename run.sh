#!/bin/sh

trap "exit" INT TERM
trap "echo caught exit signal; kill 0" EXIT

bin/mission  < pipe/mission_in  > pipe/mission_out  &
tee /ram/m < pipe/modeling_in | bin/modeling | tee pipe/modeling_out &

bin/buoys < pipe/buoys_in 2> /ram/log | tee pipe/buoys_out &

bin/interface

