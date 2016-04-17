#!/usb/bin/env blender -B render_sim.blend -P

import numpy as np
import threading 

import state as st
import image as im

from bge import logic
from bge import texture

class RenderSim(threading.Thread):
	def __init__(self):
		self.quit = False
		self.isThreadAlive = True
		
		threading.Thread.__init__(self)

	def run(self):
		print("In 'run' function. Hi.")
		path = logic.expandPath('//')

		input = open(path + 'pipe/sim_in', 'rb')
		output_f = open(path + 'pipe/camera_f', 'wb')
		output_d = open(path + 'pipe/camera_d', 'wb')

		sub = logic.getCurrentController().owner
		scene = logic.getCurrentScene()

		cam_f = texture.ImageRender(scene, scene.objects["CameraFront"])
		cam_d = texture.ImageRender(scene, scene.objects["CameraDown"])

		self.cameraFront.alpha = self.cameraDown.alpha = False
		self.cameraFront.background = self.cameraDown.background = [0, 0, 0, 0]
		self.cameraFront.capsize = self.cameraDown.capsize = [644, 482]

		while True:
			if (self.quit):
				input.close()
				output_f.close()
				output_d.close()
				self.isThreadAlive = False
				break

			state = st.read(input)

			sub.worldPosition = [state.x, state.y, state.depth]
			att = obj.worldOrientation.to_euler()
			att[0] = state.yaw
			att[1] = state.pitch
			att[2] = state.roll
			sub.worldOrientation = att.to_matrix()

			img_f = np.reshape(np.frombuffer(texture.imageToArray(cam_f, "BGR"), np.uint8), [cam_f.size[0], cam_f.size[1], 3])
			im.write(output_f, img_f)

			img_d = np.reshape(np.frombuffer(texture.imageToArray(cam_d, "BGR"), np.uint8), [cam_d.size[0], cam_d.size[1], 3])
			im.write(output_d, img_d)

RenderSim().start()

