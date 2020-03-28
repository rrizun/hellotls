#include <stdio.h>
#include <stdlib.h>
#include <fnmatch.h>

#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#define BOOST_STACKTRACE_LINK 1
#define BOOST_STACKTRACE_USE_BACKTRACE 1
#include <boost/stacktrace.hpp>
#include <boost/tokenizer.hpp>

#include "dnsmasq.pb.h"

using namespace std;

inline string dostring() {
  return "";
}

template<typename T, typename ... U>
inline string dostring(T first, U ... second) {
  return boost::lexical_cast<string>(first)+" "+dostring(second...);
}

#define LOG(...) do{printf("%s\n", dostring(time(0),__PRETTY_FUNCTION__,__FILE__,__LINE__,##__VA_ARGS__).c_str());}while(0)
#define THROW(...) do{throw runtime_error(dostring(time(0),__PRETTY_FUNCTION__,__FILE__,__LINE__,##__VA_ARGS__));}while(0)

vector<dnsmasq_lease> get_leases(string dnsmasq_leases) {
  vector<dnsmasq_lease> leases;
  return leases;
}

int baz() {
  cout << boost::stacktrace::stacktrace() << endl;
  for (auto it : boost::stacktrace::stacktrace()) {
    LOG(it);
  }
  THROW("baz");
}
int bar() {
  return baz();
}
int foo() {
  return bar();
}

int main() {

  LOG("hello", 123);

  foo();

  for (auto entry : boost::filesystem::directory_iterator("/tmp")) {

    if (fnmatch("create_ap.*.conf.*", entry.path().filename().c_str(), 0) == 0) {
      LOG(entry);

      boost::filesystem::ifstream in(boost::filesystem::path(entry).append("dnsmasq.leases"));

      string line;
      while (getline(in, line)) {
//        stringstream linestream(line);

//        log(line);
        int index = -1;
        dnsmasq_lease lease;
        boost::char_separator<char> sep{" "};
        boost::tokenizer<boost::char_separator<char>> tok{line, sep};
        for (auto it : tok) {
//          log(it);

          ++index;
          if (index == 0) {
            lease.mutable_expires()->set_seconds(
                boost::lexical_cast<::google::protobuf::int64>(it));
          } else {
            lease.GetReflection()->SetString(&lease, lease.GetDescriptor()->field(index), it);
          }
        }

        LOG(lease.DebugString());

      }


    }

  }

  return 0;
}
