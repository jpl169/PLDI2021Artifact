CC = $(ICCPATH)/compiler/2021.1.1/linux/bin/intel64/icc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh Sinpi Cospi

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CC) -std=c++11 -fp-model strict -fp-model source -no-ftz -I../../../helper/ -I../../../include/  $^ ../../../lib/floatMathLib.a $(ICCPATH)/compiler/2021.1.1/linux/compiler/lib/intel64/libimf.a -lmpfr -lgmp -o $@

clean:
	rm -rf $(obj) *.dSYM
