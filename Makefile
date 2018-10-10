CXXFLAGS = -W -Wall -O0 $(INCLUDES) $(DEFS)

OUT = hello-cpp
OBJ = hello.o

CCLD ?= $(CXX)

$(OUT): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(OUT) $(OBJ) $(LIBS)

clean:
	rm -f $(OUT) $(OBJ)
