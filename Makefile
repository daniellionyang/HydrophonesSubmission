CC = g++
SRC = src
BUILD = build

CFLAGS = -ggdb -c -std=c++11 -Iinclude
LFLAGS = 

OPENCV_CFLAGS = `pkg-config --cflags opencv`
OPENCV_LFLAGS = `pkg-config --libs opencv`

MODELING_LIB = $(patsubst %,$(BUILD)/modeling/%.o,system distribution function matrix)
MODELING_OBJ = $(patsubst %,$(BUILD)/modeling/%.o,main) $(MODELING_LIB)

INTERFACE_OBJ = $(patsubst %,$(BUILD)/interface/%.o, main connection functions) $(MODELING_LIB)

all: modeling interface

modeling: $(MODELING_OBJ)
	echo $(MODELING_LIB)
	echo $(MODELING_OBJ)
	$(CC) $^ $(LFLAGS) -o $@

interface: $(INTERFACE_OBJ)
	$(CC) $^ $(LFLAGS) -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f modeling
	rm -f interface
	rm -Rf $(BUILD)/*/*/*.o
	rm -Rf $(BUILD)/*/*.o
	rm -Rf $(BUILD)/*.o

