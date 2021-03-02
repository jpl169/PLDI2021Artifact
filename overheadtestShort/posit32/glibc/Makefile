CC = g++

funcNames = Log Log2 Log10

src = $(patsubst %, %.cpp, $(funcNames))
obj = $(patsubst %, %, $(funcNames))

all: $(obj)

%: %.cpp
	$(CC) -O2 -std=c++11  -I../../../helper/ -I$(SOFTPOSITPATH)/source/include -I../../../include/  $^ ../../../lib/posit32MathLib.a $(SOFTPOSITPATH)/build/Linux-x86_64-GCC/softposit.a -lm -o $@

clean:
	rm -rf $(obj) *.dSYM
