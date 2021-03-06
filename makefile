UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
		HEAD := \"sdlheaders/mac.hpp\"
  	CCFLAGS= -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
		HEAD := \"sdlheaders/linux.hpp\"
		CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
endif

all: text_input rsdl.o head

text_input: rsdl.o examples/textInput.cpp
		g++ src/rsdl.o examples/textInput.cpp $(CCFLAGS) -o textInput.out

rsdl.o: src/rsdl.cpp
		g++ -c src/rsdl.cpp -o src/rsdl.o
head:
		echo "#include "$(HEAD) > ./src/sdlHeaders.hpp
