CXX = gcc
EXECUTABLE = lab
CXXFLAGS =  -D _DEBUG -ggdb3 -std=c11 
COMMON_DIR = sorts
TESTING_DIR = testing
SOURCES = main.c
OUT_SOURCES = sorts/common.c sorts/p1_quadraticSort.c sorts/p2_heapSort.c sorts/p3_mergeSort.c sorts/p4_fastSort.c sorts/p5_quickSortDifferPivot.c sorts/p6_introsort.c sorts/p7_introspectiveSort.c sorts/p8_LSD_MSD.c
OUT_SOURCES_TEST = testing/testing.c
OBJECTS = $(SOURCES:%.cpp=%.o)
OUT_OBJECTS = $(OUT_SOURCES:$(COMMON_DIR)/%.cpp=%.o)
EXECUTABLE = lab.out

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(OUT_OBJECTS) $(OUT_SOURCES_TEST)
	$(CXX) $^ -o $@ $(CXXFLAGS)

%.o: $(COMMON_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS)

%.o: $(TESTING_DIR)/%.c
	$(CXX) -c $< -o $@ $(CXXFLAGS)

%.o: %.c
	$(CXX) -c $< -o $@ $(CXXFLAGS)

run:
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(OUT_OBJECTS) $(OUT_SOURCES_TEST)
