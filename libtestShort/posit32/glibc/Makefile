objects = log2 log log10

all: $(objects)

$(objects): %: %.cpp
	g++ -O2 -std=c++11 $^ -lm -lmpfr -lgmp ../../../lib/posit32MathLib.a $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a  -I$(SOFTPOSITPATH)/source/include -I../../../include/ -o $@


clean:
	rm -rf $(objects) *.dSYM
