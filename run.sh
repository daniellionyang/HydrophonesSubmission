#!/bin/sh

trap "exit" INT TERM
trap "echo caught exit signal; kill 0" EXIT

bin/mission  < pipe/mission_in  > pipe/mission_out  &
bin/modeling < pipe/modeling_in > pipe/modeling_out &

bin/buoys < pipe/buoys_in > pipe/buoys_out &

bin/interface

