# Compilează și rulează fiecare lecție. Din rădăcina repo-ului: make -C Cpp
# Sau din acest director: make

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O0 -g
SRC      := $(shell find . -name '*.cpp' | sort)
BIN_DIR  := /tmp/cpp-challenges

.PHONY: all run clean

all: run

run:
	@mkdir -p $(BIN_DIR)
	@fail=0; \
	for f in $(SRC); do \
	  name=$$(echo $$f | sed 's|^\./||; s|/|_|g; s|\.cpp$$||'); \
	  echo "======== $$f ========"; \
	  if $(CXX) $(CXXFLAGS) $$f -o $(BIN_DIR)/$$name; then \
	    $(BIN_DIR)/$$name; echo; \
	  else \
	    echo "COMPILARE EȘUATĂ: $$f"; fail=1; \
	  fi; \
	done; \
	exit $$fail

clean:
	rm -rf $(BIN_DIR)
