import sys
import os

import bpy
import bgl
import gpu

# add this file's directory to path because blender does not add it by default
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
# also add the blender's file's directory to path
sys.path.append(os.path.dirname(bpy.data.filepath))

import numpy as np

from python.lib import state as st
from python.lib import image as im

def generateNodes(scene):
	# enable nodes
	scene.use_nodes = True
	tree = scene.node_tree
	links = tree.links

	# clear nodes
	for n in tree.nodes:
		tree.nodes.remove(n)

	# input node
	render = tree.nodes.new('CompositorNodeRLayers')
	render.location = 185, 285

	# output node
	viewer = tree.nodes.new('CompositorNodeViewer')
	viewer.location = 750, 210
	viewer.use_alpha = False

	# connect nodes
	links.new(render.outputs[0], viewer.inputs[0])

def renderFrame(scene, camera):
	# set camera
	scene.camera = camera

	# render frame
	bpy.ops.render.render()

	# fetch image data
	img = bpy.data.images['Viewer Node'].pixels

	# return numpy array
	return (255 * np.array(img[:]).reshape([644, 482, 4])[:,:,[2,1,0]]).transpose([1,0,2]).astype(np.uint8)

def run():
	print("Begin script")
	print("Fetching scene objects")
	scene = bpy.data.scenes[0]
	sub = scene.objects['Submarine']
	loc = sub.location
	att = sub.rotation_euler

	cam_f = scene.objects['CameraFront']
	cam_d = scene.objects['CameraDown']

	print("Generating nodes")
	generateNodes(scene)

	print("Opening input pipe")
	path = bpy.path.abspath('//')
	input = open(path + 'pipe/sim_in', 'rb')
	print("Opening output pipes")
	output_f = open(path + 'pipe/render_f', 'wb')
	output_d = open(path + 'pipe/render_d', 'wb')

	print("Begin main loop")
	quit = False
	while True:
		if (quit):
			print("Cleaning up")
			bpy.context.area.type = original_type
			input.close()
			output_f.close()
			output_d.close()
			print("Exit")
			return 0

		print("Waiting for input")
		state = st.read(input)
		print("Received state\n{}".format(state.__dict__))

		print("Moving objects")
		loc[0] = state.x
		loc[1] = state.y
		loc[2] = state.depth

		att[0] = state.yaw
		att[1] = state.pitch
		att[2] = state.roll

		print("Rendering images")
		img_f = renderFrame(scene, cam_f)
		img_d = renderFrame(scene, cam_d)
		print(img_d)

		print("Sending images over pipes")
		im.write(output_f, img_f)
		im.write(output_d, img_d)

run()

