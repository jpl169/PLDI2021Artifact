CC = $(ICCPATH)/compiler/2021.1.1/linux/bin/intel64/icc

funcNames = Log Log2 Log10

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CC) -std=c++11 -fp-model strict -fp-model source -no-ftz -I$(SOFTPOSITPATH)/source/include -I../../../helper/ -I../../../include/  $^ ../../../lib/posit32MathLib.a $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a $(ICCPATH)/compiler/2021.1.1/linux/compiler/lib/intel64/libimf.a -o $@

clean:
	rm -rf $(obj) *.dSYM
