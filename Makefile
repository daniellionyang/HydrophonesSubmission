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

all: modeling interface camera

modeling: $(MODELING)
	$(CC) $^ $(LFLAGS) $(MODELING_LFLAGS) -o $@

interface: $(INTERFACE)
	$(CC) $^ $(LFLAGS) $(INTERFACE_LFLAGS) -o $@

camera: $(CAMERA)
	$(CC) $^ $(LFLAGS) $(CAMERA_LFLAGS) -o $@

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

clean:
	rm -f modeling
	rm -f interface
	rm -f camera
	rm -Rf $(BUILD)/*/*/*.o
	rm -Rf $(BUILD)/*/*.o
	rm -Rf $(BUILD)/*.o

