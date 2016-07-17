#!/usr/bin/env python3

import sys

import numpy as np

from lib.neural_network import NeuralNetwork

filename = sys.argv[1]

numInputs = 3
numFeatures = 4
numOutputs = 1

inputs = np.array([
], dtype=np.float32) / 256
targets = np.array([[1]]*0 + [[0]]*0, dtype=np.float32)

nn = NeuralNetwork(numInputs, numFeatures, numOutputs)

nn.load('/ram/weights.npz')

i = 0
while True:
	nn.train(inputs, targets)

	if i % 256 == 0:
		print("{} {}".format(int(i/256), nn.evaluate(inputs, targets)))
	if i % (256**2) == 0:
		nn.save(filename)
		print("{}".format(nn.session().run(nn.weights())))
	i += 1

