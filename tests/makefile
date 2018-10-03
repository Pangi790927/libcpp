DIRS := ../libc/ ../stdio/ ../

CXX_FLAGS := -ffreestanding -fno-rtti -fno-exceptions
CXX_INCLUDE := $(patsubst %, -I%, $(DIRS))
CXX_FILES := $(foreach dir, $(DIRS), $(shell find ${dir} \
		-maxdepth 1 -type f -name "*.cpp" ))
CXX_FILES := ${CXX_FILES}

TESTS := $(shell find . -type f -name "test-*.cpp")
TESTS := $(filter-out "test-external.cpp", $(TESTS))
TEST_EXEC := $(patsubst %.cpp, %.exec, $(TESTS))

all: clean test-external.o	\
		test-compile.exec	\
		test-malloc.exec

test-external.o: test-external.cpp
	g++ -c ${CXX_INCLUDE} test-external.cpp -o test-external.o

${TEST_EXEC}:%.exec:%.cpp
	echo ${TESTS}
	g++ ${CXX_FLAGS} ${CXX_INCLUDE} ${CXX_FILES} \
			test-external.o $^ -o $@
	./$@

clean:
	rm -f *.exec