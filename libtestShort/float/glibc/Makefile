CC = g++

funcNames = Log Log2 Log10 Sinh Cosh Exp Exp2 Exp10 Sinpi Cospi

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CC) -O2 -std=c++11  -I../../../helper/ -I../../../include/  $^ ../../../lib/floatMathLib.a -lm -lmpfr -lgmp -o $@

clean:
	rm -rf $(obj) *.dSYM
