CC = $(ICCPATH)/bin/icc

objects = log2 log log10

all: $(objects)

$(objects): %: %.cpp
	$(CC) -std=c++11 -fp-model strict -fp-model source -no-ftz -I../../../include/ -I$(SOFTPOSITPATH)/source/include $^ $(ICCPATH)/lib/intel64/libimf.a ../../../lib/posit32MathLib.a $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a  -lmpfr -lgmp -o $@


clean:
	rm -rf $(objects) *.dSYM
