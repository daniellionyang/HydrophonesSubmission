CC = g++
SRCDIR = src
BUILDDIR = build

CFLAGS = -ggdb -c -std=c++11
LDFLAGS = 

MODELING_LIB_OBJECTS = modeling/system modeling/distribution modeling/function modeling/matrix

MODELING_DEPS = $(MODELING_LIB_OBJECTS) modeling/main
MODELING_OBJECTS = $(addprefix $(BUILDDIR)/,$(addsuffix .o,$(MODELING_DEPS)))

all: $(BUILDDIR) modeling

$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/modeling

modeling: $(MODELING_OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f modeling
	rm -Rf build

