CC = g++
SRC = src
BUILD = build

CFLAGS = -ggdb -c -std=c++14 -Iinclude
LFLAGS = 

THIRDPARTY = ./3rdparty/

OPENCV_CFLAGS = `pkg-config --cflags opencv`
OPENCV_LFLAGS = `pkg-config --libs opencv` -pthread

FLYCAP = $(THIRDPARTY)/flycapture/
FLYCAP_CFLAGS = -I$(SRC) -I$(FLYCAP)/include/
FLYCAP_LFLAGS = -L$(FLYCAP)/lib -lflycapture -Wl,-rpath=$(FLYCAP)/lib/


MODEL = $(patsubst %,$(BUILD)/model/%.o,system distribution function matrix)
MODEL_CFLAGS = 

IMAGE = $(patsubst %,$(BUILD)/image/%.o,image)
IMAGE_CFLAGS = $(OPENCV_CFLAGS)


MODELING = $(patsubst %,$(BUILD)/modeling/%.o,main) $(MODEL)
MODELING_CFLAGS = 
MODELING_LFLAGS = 

INTERFACE = $(patsubst %,$(BUILD)/interface/%.o, main connection functions data) $(MODEL) $(IMAGE)
INTERFACE_CFLAGS = $(OPENCV_CFLAGS)
INTERFACE_LFLAGS = $(OPENCV_LFLAGS)

CAMERA = $(patsubst %,$(BUILD)/camera/%.o,main) $(IMAGE)
CAMERA_CFLAGS = $(OPENCV_CFLAGS) $(FLYCAP_CFLAGS)
CAMERA_LFLAGS = $(OPENCV_LFLAGS) $(FLYCAP_LFLAGS)

IMAGE_READ = $(patsubst %,$(BUILD)/image_read/%.o,main) $(IMAGE)
IMAGE_READ_CFLAGS = $(OPENCV_CFLAGS) $(IMAGE_CFLAGS)
IMAGE_READ_LFLAGS = $(OPENCV_LFLAGS)

IMAGE_SHOW = $(patsubst %,$(BUILD)/image_show/%.o,main) $(IMAGE)
IMAGE_SHOW_CFLAGS = $(OPENCV_CFLAGS) $(IMAGE_CFLAGS)
IMAGE_SHOW_LFLAGS = $(OPENCV_LFLAGS)

DROPPER = $(patsubst %,$(BUILD)/dropper/%.o,color_crop droppers) $(IMAGE)
DROPPER_CFLAGS = $(OPENCV_CFLAGS) 
DROPPER_LFLAGS = $(OPENCV_LFLAGS)
 
BUOYS = $(patsubst %, $(BUILD)/buoys/%.o,buoys) $(IMAGE)
BUOYS_CFLAGS = $(OPENCV_CFLAGS) 
BUOYS_LFLAGS = $(OPENCV_LFLAGS)

all: modeling interface camera image_read image_show dropper buoys

modeling: $(MODELING)
	$(CC) $^ $(LFLAGS) $(MODELING_LFLAGS) -o $@

interface: $(INTERFACE)
	$(CC) $^ $(LFLAGS) $(INTERFACE_LFLAGS) -o $@

camera: $(CAMERA)
	$(CC) $^ $(LFLAGS) $(CAMERA_LFLAGS) -o $@

image_read: $(IMAGE_READ)
	$(CC) $^ $(LFLAGS) $(IMAGE_READ_LFLAGS) -o $@

image_show: $(IMAGE_SHOW)
	$(CC) $^ $(LFLAGS) $(IMAGE_SHOW_LFLAGS) -o $@

dropper: $(DROPPER) 
	$(CC) $^ $(LFLAGS) $(DROPPER_LFLAGS) -o $@
 
buoys: $(BUOYS) 
	$(CC) $^ $(LFLAGS) $(BUOYS_LFLAGS) -o $@

$(BUILD)/model/%.o: $(SRC)/model/%.cpp
	$(CC) $(CFLAGS) $(MODEL_CFLAGS) $< -o $@

$(BUILD)/image/%.o: $(SRC)/image/%.cpp
	$(CC) $(CFLAGS) $(IMAGE_CFLAGS) $< -o $@

$(BUILD)/modeling/%.o: $(SRC)/modeling/%.cpp
	$(CC) $(CFLAGS) $(MODELING_CFLAGS) $< -o $@
 
$(BUILD)/interface/%.o: $(SRC)/interface/%.cpp
	$(CC) $(CFLAGS) $(INTERFACE_CFLAGS) $< -o $@

$(BUILD)/camera/%.o: $(SRC)/camera/%.cpp
	$(CC) $(CFLAGS) $(CAMERA_CFLAGS) $< -o $@

$(BUILD)/image_read/%.o: $(SRC)/image_read/%.cpp
	$(CC) $(CFLAGS) $(IMAGE_READ_CFLAGS) $< -o $@

$(BUILD)/image_show/%.o: $(SRC)/image_show/%.cpp
	$(CC) $(CFLAGS) $(IMAGE_SHOW_CFLAGS) $< -o $@

$(BUILD)/dropper/%.o: $(SRC)/dropper/%.cpp
	$(CC) $(CFLAGS) $(DROPPER_CFLAGS) $< -o $@
 
$(BUILD)/buoys/%.o: $(SRC)/buoys/%.cpp
	$(CC) $(CFLAGS) $(BUOYS_CFLAGS) $< -o $@

clean:
	rm -f modeling
	rm -f interface
	rm -f camera
	rm -f image_read
	rm -f image_show
	rm -f dropper
	rm -f buoys 
	rm -f $(BUILD)/*/*/*.o
	rm -f $(BUILD)/*/*.o
	rm -f $(BUILD)/*.o

