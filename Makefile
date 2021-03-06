
CXX ?= g++
OPT ?= -O2
CXXFLAGS += ${OPT} -Wall -std=c++2a -Iextern/include/eigen3 -Iextern/include/ -Iinclude
LDFLAGS += -lz -lpthread 

SRCD=src
OBJD=obj
TSTD=test
TSTB=test/binaries
BUILDD=build
PCH_LIB = libs.h
PCH_HEADERS = kdex.h
SOURCE_FILES = test.cpp

SOURCE_PATH = $(SOURCE_FILES:%.cpp=${SRCD}/%.cpp)
EXEC_FILES = $(SOURCE_FILES:%.cpp=${BUILDD}/%)
OBJECTS = $(SOURCE_FILES:%.cpp=${OBJD}/%.o)
PCH_OUT = $(PCH_LIB:%.h=${OBJD}/%.pch)
HEADER_PATH = $(PCH_HEADERS:%.h=${SRCD}/%.h)

all: $(EXEC_FILES)

$(BUILDD)/%:$(SRCD)/%.cpp
	mkdir -p ${BUILDD}
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(PCH_OUT): $(PCH_LIB) $(PCH_HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $<

${OBJD}/%.o:$(SRCD)/%.cpp 
	mkdir -p ${OBJD}
	$(CXX) $(CXXFLAGS) -o $@ $<

${TSTB}/%:${TSTD}/%.cpp
	mkdir -p ${TSTB}
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

	
all:
	@echo ${SOURCE_PATH}
	@echo ${OBJECTS}
	@echo ${PCH_LIB}
	@echo ${PCH_OUT}
	@echo ${HEADER_PATH}
	@echo ${EXEC_FILES}

.PHONY: clean

clean:
	rm -f ${BUILDD}/*
	rm -f ${OBJD}/*.o
