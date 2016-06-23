#  Makefile
#  aoneill - 01/22/16

CXX = gcc
CXXFLAGS = -Wall -fPIC -DPIC

# Top level
SRC = src
OBJ = obj

################################################################################

EXEC_NAME = infinifuck

################################################################################

SRC_C = $(shell cd $(SRC)/ && find * -type f -name "*.c" -not -name "main.c")
OBJ_O = $(addprefix $(OBJ)/,$(SRC_C:%.c=%.o))

all: CXXFLAGS += -Ofast
all: init $(EXEC_NAME)
debug: CXXFLAGS += -DDEBUG -g -pg
debug: init $(EXEC_NAME)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $^ -o $@

################################################################################

$(EXEC_NAME): $(OBJ_O) $(SRC)/main.c 
	$(CXX) $(CXXFLAGS) $^ -o $@

################################################################################

init:
	mkdir -p "$(OBJ)"

clean:
	rm -rf ./$(OBJ)/
	rm -rf $(EXEC_NAME) gmon.out
