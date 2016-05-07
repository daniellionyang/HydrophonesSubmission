#!/bin/sh

trap "exit" INT TERM
trap "echo caught exit signal; kill 0" EXIT

cat pipe/mission_in &
cat > pipe/mission_out

