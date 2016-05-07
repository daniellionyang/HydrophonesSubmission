import numpy as np
import re
import time

class State(object):
	def __init__(self, x, y, depth, yaw, pitch, roll):
		self.x, self.y, self.depth, self.yaw, self.pitch, self.roll = \
			(x, y, depth, yaw, pitch, roll)

def read(input):
	buf = bytearray()
	rx = re.compile(b"s\s+([\d\.\-\+]+)\s+([\d\.\-\+]+)\s+([\d\.\-\+]+)\s+([\d\.\-\+]+)\s+([\d\.\-\+]+)\s+([\d\.\-\+]+)\s+$")
	while True:
		byt = input.read(1)
		if len(byt) == 0:
			time.sleep(.01)
			continue
		buf.append(byt[0])
		res = rx.search(buf)
		if res:
			return State(*[float(g) for g in res.group(1, 2, 3, 4, 5, 6)])

def write(output, state):
	numBytes = output.write(("s {} {} {} {} {} {}\n".format(
		state.x, state.y, state.depth, state.yaw, state.pitch, state.roll
	)).encode('utf-8'))
	output.flush()
	return numBytes

