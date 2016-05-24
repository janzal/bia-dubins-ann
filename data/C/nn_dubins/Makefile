#
# Date:      2011/07/11 17:55
# Author:    Jan Faigl
#

CXX:=ccache $(CXX)

include Mk/libs.mk

CXXFLAGS+=-std=c++11

CPPFLAGS+=$(LOCAL_CFLAGS)
LDFLAGS+=$(LOCAL_LDFLAGS)

CPPFLAGS+=$(IMR-H_CFLAGS) $(BOOST_CFLAGS) $(CAIRO_CFLAGS) $(LOG4CXX_CPPFLAGS)
LDFLAGS+=$(IMR-H-GUI_LDFLAGS) $(IMR-H_LIBS) $(CAIRO_LIBS) $(BOOST_LIBS) $(LOG4CXX_LDFLAGS)

LDFLAGS+=$(OPENDUBINS_LIBS)

CXXFLAGS+=-O2 -march=native
CXXFLAGS+=-g

OBJS=\
    dubins_demo.o\
    tdubins.o

# OBJS=pythonapi.o

TARGET=tdubins
# TARGET=pythonapi

pythonapi.so: $(OBJS)
	$(CXX) -shared -Wl -o libpythonapi.so $(OBJS) $(LDFLAGS)

include Mk/comrob.mk
