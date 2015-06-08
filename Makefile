CC=gcc
CFLAGS=-O3 -fPIC -W -Wall -g
LDFLAGS=-lm -lfftw3 -lpthread -g

CFLAGS+=$(shell pkg-config --cflags librtlsdr)
LDFLAGS+=$(shell pkg-config --libs librtlsdr)

# Uncomment the following line to use the fast, but x86-only Spiral Viterbi function.
#ENABLE_SPIRAL_VITERBI=yes

ifdef ENABLE_SPIRAL_VITERBI
  CFLAGS+=-DENABLE_SPIRAL_VITERBI -msse2 -msse3 -std=gnu99 
  VITERBI_OBJS=../dabtools/src/viterbi_spiral.o ../dabtools/src/viterbi_spiral_sse16.o
else
  VITERBI_OBJS=../dabtools/src/viterbi.o
endif


OBJS=../dabtools/src/wf_sync.o ../dabtools/src/wf_prstables.o ../dabtools/src/wf_maths.o ../dabtools/src/fic.o ../dabtools/src/misc.o ../dabtools/src/dab_tables.o ../dabtools/src/input_wf.o ../dabtools/src/depuncture.o ../dabtools/src/input_sdr.o ../dabtools/src/sdr_fifo.o ../dabtools/src/sdr_sync.o ../dabtools/src/dab.o $(VITERBI_OBJS)

all:  libdabplus example

libdabplus: $(OBJS) libdabplus.cpp libdabplus.h
	g++ -c -std=c++11 -fPIC libdabplus.cpp -o libdabplus.o
	g++ -Wall -shared -fPIC -o libdabplus.so libdabplus.o $(OBJS) -lfftw3 -pthread

example: libdabplus
	g++ -Wall -std=c++11 example.cpp  -L . -ldabplus -o example

clean:
	rm -f *.o *.so *~
