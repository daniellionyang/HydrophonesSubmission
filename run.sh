#!/bin/bash

trap "exit" INT TERM
trap "echo caught exit signal; kill 0" EXIT

bin/mission  < pipe/mission_in  > pipe/mission_out  &
bin/modeling < pipe/modeling_in | tee pipe/modeling_out &

bin/buoys     < pipe/buoys_in 2> logs/buoys.maga | tee pipe/buoys_out &
bin/pvc       < pipe/pvc_in   2> logs/pvc.maga   | tee pipe/pvc_out   &
bin/torpedoes < pipe/torps_in 2> logs/torps.maga | tee pipe/torps_out &
bin/dropper   < pipe/bins_in  2> logs/bins.maga  | tee pipe/bins_out  &

bin/interface

