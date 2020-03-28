AM_CPPFLAGS=$(MODULES_CFLAGS)
#AM_CFLAGS=
#AM_CXXFLAGS=
AM_LDFLAGS=-static-libgcc -static-libstdc++

%.pb.h %.pb.cc: %.proto
	protoc -I. --cpp_out=. $<

BUILT_SOURCES = dnsmasq.pb.h dnsmasq.pb.cc

bin_PROGRAMS = main
main_SOURCES = main.cpp dnsmasq.pb.cc

LIBS += -lpthread -Wl,-Bstatic $(MODULES_LIBS) -lprotobuf -lboost_filesystem -lboost_stacktrace_basic -lboost_system -lbacktrace -Wl,-Bdynamic -ldl -lrt
