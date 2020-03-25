AM_CPPFLAGS=$(MODULES_CFLAGS)
#AM_CFLAGS=
#AM_CXXFLAGS=
AM_LDFLAGS=-static-libgcc -static-libstdc++

bin_PROGRAMS = main
main_SOURCES = main.cpp

LIBS += -lpthread -Wl,-Bstatic $(MODULES_LIBS) -Wl,-Bdynamic -ldl -lrt 
