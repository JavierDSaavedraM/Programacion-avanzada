# -*- MakeFile -*-
CXX = g++
TEST_SOURCES = test/main.cpp
TARGET = main.exe
SOURCES = 1erParcial/LecturaJson.cpp

all: $(TARGET) run clean
test: exp run clean
debug: exp run clean

$(TARGET): $(SOURCES)
	$(CXX) -o $(TARGET) $(SOURCES)
run:
	./$(TARGET)
clean:
	@rm -rf $(TARGET)
exp:
	@clear
	$(CXX) -DDEBUG -o $(TARGET) $(SOURCES)
testInput:
	$(CXX) -o $(TARGET) $(SOURCES)
	./$(TARGET) < "cosa.txt"
