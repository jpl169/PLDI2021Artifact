CC = $(ICCPATH)/bin/icc

funcNames = Log Log2 Log10 Exp Exp2 Exp10 Sinh Cosh Cospi Sinpi Log2_8 Log10_8

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CC) -std=c++11 -fp-model strict -fp-model source -no-ftz   -I../../../helper/ -I../../../include/  $^ ../../../lib/floatMathLib.a $(ICCPATH)/lib/intel64/libimf.a -o $@

clean:
	rm -rf $(obj) *.dSYM
