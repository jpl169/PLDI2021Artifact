objects = Log2 Log Log10 Exp2 Exp Exp10 Cosh Sinh Sinpi Cospi
	

CC=g++

INCLUDES= -I$(SOPLEXPATH)/src -I../../helper/

CPP_FLAGS= -O2 -std=c++17

LD_FLAGS= -lmpfr -lz -lm

all: $(objects)

$(objects): %: %.cpp
	$(CC) $(CPP_FLAGS) $(INCLUDES) $^ $(LD_FLAGS) -o $@

clean:
	rm -rf *.o $(objects) *~ *.dSYM