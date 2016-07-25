CC=gcc
CFLAGS=-O3 -fPIC -W -Wall -pthread -g
CXXFLAGS=-std=c++11 -fPIC -W -Wall -pthread -g
LDFLAGS=-lm -lfftw3 -pthread -g

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


OBJS=../dabtools/src/wf_sync.o ../dabtools/src/wf_prstables.o ../dabtools/src/wf_maths.o ../dabtools/src/fic.o ../dabtools/src/misc.o ../dabtools/src/dab_tables.o ../dabtools/src/input_wf.o ../dabtools/src/depuncture.o ../dabtools/src/input_sdr.o ../dabtools/src/sdr_fifo.o ../dabtools/src/sdr_sync.o ../dabtools/src/dab.o $(VITERBI_OBJS) libdabplus.o dab2eti.o

all:  libdabplus example example2

libdabplus: $(OBJS)
	g++ -Wall -shared -fPIC -o libdabplus.so $(OBJS) $(LDFLAGS) -lfftw3 -pthread

example: libdabplus
	g++ -Wall -std=c++11 example.cpp  -L . -ldabplus  -o example $(LDFLAGS) -pthread

example2: libdabplus
	g++ -Wall -std=c++11 example2.cpp  -L . -ldabplus  -o example2 $(LDFLAGS) -pthread

clean:
	rm -f *.o *.so ../dabtools/src/*.o *~ example

install: all
	cp libdabplus.so /usr/local/lib/
	cp example example2 /usr/local/bin/
	cp libdabplus.h /usr/local/include/

