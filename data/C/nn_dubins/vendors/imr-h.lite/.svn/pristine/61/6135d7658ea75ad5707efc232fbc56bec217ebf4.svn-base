#
# Date:      2009/08/26 14:27
# Author:    Jan Faigl
#

SRC=src
LIBRARY=libimr-h.a

#installation prefix
INSTALL_PREFIX=../..

include ../Mk/libs.mk

CXXFLAGS+=-O2
#CXXFLAGS+=-g

CPPFLAGS+=$(BOOST_CPPFLAGS)
CPPFLAGS+=$(LOG4CXX_CPPFLAGS)

LIBRARY_OBJS=$(patsubst %.cc,%.o,$(wildcard $(SRC)/*.cc))
include ../Mk/comrob.mk

install: lib
	rm -rf $(INCLUDE_PREFIX)/common
	rm -rf $(INCLUDE_PREFIX)/concurrent
	mkdir -p $(INCLUDE_PREFIX)
	ln -s . $(INCLUDE_PREFIX)/common
	ln -s . $(INCLUDE_PREFIX)/concurrent
	cp $(SRC)/*.h $(INCLUDE_PREFIX)

deinstall:
	$(RM) -r $(LIBRARY_PREFIX) $(INCLUDE_PREFIX)
	$(RM) $(LIBRARY)

