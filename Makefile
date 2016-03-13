CC = g++
SRC = src
BUILD = build

CFLAGS = -ggdb -c -std=c++14 -Iinclude
LFLAGS = 

OPENCV_CFLAGS = `pkg-config --cflags opencv`
OPENCV_LFLAGS = `pkg-config --libs opencv` -pthread


MODEL = $(patsubst %,$(BUILD)/model/%.o,system distribution function matrix)
MODEL_CFLAGS = 

MODELING = $(patsubst %,$(BUILD)/modeling/%.o,main) $(MODEL)
MODELING_CFLAGS = 


IMAGE = $(patsubst %,$(BUILD)/image/%.o,image)
IMAGE_CFLAGS = $(OPENCV_CFLAGS)
IMAGE_LFLAGS = $(OPENCV_LFLAGS)

INTERFACE = $(patsubst %,$(BUILD)/interface/%.o, main connection functions data) $(MODEL) $(IMAGE)
INTERFACE_CFLAGS = $(OPENCV_CFLAGS)
INTERFACE_LFLAGS = $(OPENCV_LFLAGS)

all: modeling interface

modeling: $(MODELING)
	$(CC) $^ $(LFLAGS) $(MODELING_LFLAGS) -o $@

interface: $(INTERFACE)
	$(CC) $^ $(LFLAGS) $(INTERFACE_LFLAGS) -o $@

$(BUILD)/model/%.o: $(SRC)/model/%.cpp
	$(CC) $(CFLAGS) $(MODEL_CFLAGS) $< -o $@

$(BUILD)/modeling/%.o: $(SRC)/modeling/%.cpp
	$(CC) $(CFLAGS) $(MODELING_CFLAGS) $< -o $@

$(BUILD)/image/%.o: $(SRC)/image/%.cpp
	$(CC) $(CFLAGS) $(IMAGE_CFLAGS) $< -o $@

$(BUILD)/interface/%.o: $(SRC)/interface/%.cpp
	$(CC) $(CFLAGS) $(INTERFACE_CFLAGS) $< -o $@

clean:
	rm -f modeling
	rm -f interface
	rm -Rf $(BUILD)/*/*/*.o
	rm -Rf $(BUILD)/*/*.o
	rm -Rf $(BUILD)/*.o

