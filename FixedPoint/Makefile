CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
CXX20FLAGS = -std=c++20 -Wall -Wextra -O2
INCLUDES = -I.

test: test_fixedpoint
	./test_fixedpoint

benchmark: benchmark_exe
	./benchmark_exe

benchmark20: benchmark20_exe
	./benchmark20_exe

test_fixedpoint: test_fixedpoint.cpp fixedpoint.cpp fixedpoint.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o test_fixedpoint test_fixedpoint.cpp fixedpoint.cpp

benchmark_exe: benchmark.cpp
	$(CXX) $(CXXFLAGS) -o benchmark_exe benchmark.cpp

benchmark20_exe: benchmark.cpp
	$(CXX) $(CXX20FLAGS) -o benchmark20_exe benchmark.cpp

clean:
	rm -f test_fixedpoint benchmark_exe benchmark20_exe

.PHONY: test benchmark benchmark20 clean