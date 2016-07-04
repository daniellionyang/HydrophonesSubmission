import sys
import os
import math

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

	# output compositing node (for rendering from blender ui)
	composite = tree.nodes.new('CompositorNodeComposite')
	composite.location = 750, 0
	composite.use_alpha = False

	# connect nodes
	links.new(render.outputs[0], viewer.inputs[0])
	links.new(render.outputs[0], composite.inputs[0])

def renderFrame(scene, camera):
	render = scene.render

	# set camera
	scene.camera = camera

	# render frame
	bpy.ops.render.render()

	# fetch image data
	node = bpy.data.images['Viewer Node']
	buffer = np.array(node.pixels[:])

	# return numpy array
	return (255 * buffer).astype(np.uint8).reshape([
		int(render.resolution_y * render.resolution_percentage/100), int(render.resolution_x * render.resolution_percentage/100), 4
	])[:,:,[2,1,0]].transpose([0,1,2])[::-1,:,:]

def run():
	print("Begin script")

	print("Setting material options")
	for m in bpy.data.materials:
		m.use_shadeless = False
		m.use_shadows = False
		m.use_cast_shadows = False
		m.use_cast_buffer_shadows = False
		m.use_cast_approximate = False
		m.use_raytrace = False
		m.subsurface_scattering.use = False

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
	input = open(path + 'pipe/sim_in', 'rb', 0)
	print("Opening output pipes")
	output_f = open(path + 'pipe/render_f', 'wb', 0)
	output_d = open(path + 'pipe/render_d', 'wb', 0)

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

		att[1] = state.pitch * 2*math.pi
		att[0] = state.roll * 2*math.pi
		att[2] = state.yaw * 2*math.pi

		print("Rendering images")
		img_f = renderFrame(scene, cam_f)
		img_d = renderFrame(scene, cam_d)

		print("Sending images over pipes")
		im.write(output_f, img_f)
		im.write(output_d, img_d)

run()

