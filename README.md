# libdabplus
C++ library wrapper for DAB receivers, based on code from dabtools and rtl-sdr

WARNING: This library is not yet in a usable state


Required packages for compiling this library:

rtl-sdr (git clone git://git.osmocom.org/rtl-sdr.git or apt-get install librtlsdr-dev)
dabtools (git clone https://github.com/linuxstb/dabtools)

rtl-sdr is used for tuning the USB receiver stick. dabtools contains
the code that does the actual demodulation/decoding of the DAB signal
and outputs the ETI stream.

This library is just a wrapper around the above tools that makes their
functionality available to C++ programs like eg. dablin


Included example programs
*************************

example.cpp:
The client calls a library function repeatedly to get an ETI frame each time

example2.cpp:
The client implements a callback function that gets called by the library
each time an ETI frame is ready, with this ETI frame as the argument.