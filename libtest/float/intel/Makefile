CC = $(ICCPATH)/bin/icc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh Sinpi Cospi

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CC) -std=c++11 -fp-model precise -fp-model strict -fp-model source -no-ftz -I../../../helper/ -I../../../include/  $^ ../../../lib/floatMathLib.a $(ICCPATH)/lib/intel64/libimf.a -lmpfr -lgmp -o $@

clean:
	rm -rf $(obj) *.dSYM
