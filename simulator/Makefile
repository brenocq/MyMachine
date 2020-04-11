CC = g++
# Text style
RED    = \033[0;31m
GREEN  = \033[0;32m
NC     = \033[0m
BOLD   = \033[1m

# Folders
BIN	   = bin/
SRC	   = src/
LIB    = lib/
OBJ    = obj/

# Files
FILES = main

SOURCES=$(patsubst %, ${SRC}%.cpp, ${FILES})

HEADERS=$(patsubst %, ${LIB}%.h, ${FILES})

OBJECTS=$(patsubst %, ${OBJ}%.o, ${FILES})

DEPENDENCIES=${LIB}defines.h

EXECUTABLE=${BIN}simulator

# Flags
FLAGS= -Wall -I${LIB} -std=c++11

# Targets
${EXECUTABLE}: ${OBJECTS} ${DEPENDENCIES}
	@/bin/echo -e "${GREEN}${BOLD}----- Creating executable -----${NC}"
	${CC} -g ${OBJECTS} -o ${EXECUTABLE} ${FLAGS} 


# Compile project files
${OBJ}%.o: ${SRC}%.cpp
	@/bin/echo -e "${GREEN}Compiling $<${NC}"
	${CC} -c $< -o $@ ${FLAGS} 

clean:
	@/bin/echo -e "${GREEN}${BOLD}----- Cleaning project -----${NC}"
	rm -rf ${OBJ}*.o
	rm -rf ${EXECUTABLE}

run: ${EXECUTABLE}
	@/bin/echo -e "${GREEN}${BOLD}----- Running ${EXECUTABLE} -----${NC}"
	./${EXECUTABLE}
