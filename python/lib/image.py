import numpy as np
import re
import time

def read(input):
	buf = bytearray()
	rx = re.compile(b"i\s+(\d+)\s+(\d+)\s+\\\\$")
	while True:
		byt = input.read(1)
		if len(byt) == 0:
			time.sleep(.01)
			continue
		buf.append(byt[0])
		res = rx.search(buf)
		if res:
			n, m = res.group(1, 2)
			rows = int(n)
			cols = int(m)
			return np.reshape(np.frombuffer(input.read(3 * rows * cols), np.uint8), [rows, cols, 3])

def write(output, img):
	s = img.shape
	numBytes = 0
	numBytes += output.write(("i {} {}\n\\".format(s[0], s[1])).encode('utf-8'))
	numBytes += output.write(img.tobytes())
	numBytes += output.write(b'\n')
	output.flush()
	return numBytes

