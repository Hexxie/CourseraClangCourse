SOURCES:= ${wildcard *.cpp}
OBJECTS:= ${SOURCES:.cpp=.o}
DEP_FILES:= ${SOURCES:.cpp=.d}
CCFLAGS:= -std=c++17


.PHONY: all clean

all: $(OBJECTS)

clean:
	rm -f *.o
	rm -f *.d

$(OBJECTS):
	g++ $(CCFLAGS) -c ${@:.o=.cpp} -o $@

-include $(DEP_FILES)

