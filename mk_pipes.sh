#!/bin/bash

cd pipe
mkfifo mission_in mission_out control_in control_out modeling_in modeling_out camera_f_in camera_d_in camera_f_out camera_d_out sim_in render_f render_d

