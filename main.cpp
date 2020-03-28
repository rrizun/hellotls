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

//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/wait.h>
//#include <unistd.h>
//#include <sys/prctl.h>
//void print_trace() {
//    char pid_buf[30];
//    sprintf(pid_buf, "%d", getpid());
//    char name_buf[512];
//    name_buf[readlink("/proc/self/exe", name_buf, sizeof(name_buf)-1)]=0;
//
//    prctl(PR_SET_PTRACER, PR_SET_PTRACER_ANY, 0, 0, 0);
//
//    int child_pid = fork();
//    if (!child_pid) {
////        dup2(2,1); // redirect output to stderr
////        fprintf(stdout,"stack trace for %s pid=%s\n",name_buf,pid_buf);
//        execlp("gdb", "gdb", "--batch", "-n", "-ex", "thread", "-ex", "bt", name_buf, pid_buf, NULL);
////        abort(); /* If gdb failed to start */
//    } else {
//        waitpid(child_pid,NULL,0);
//    }
//}

using namespace std;

inline string dostring() {
  return "";
}

template<typename T, typename ... U>
inline string dostring(T first, U ... second) {
  return boost::lexical_cast<string>(first)+" "+dostring(second...);
}

#define LOGX(...) do{printf("%s\n", dostring(time(0),__PRETTY_FUNCTION__,__FILE__,__LINE__,##__VA_ARGS__).c_str());}while(0)

//printf("%s\n", dostring(time(0),__PRETTY_FUNCTION__,__FILE__,__LINE__,##__VA_ARGS__).c_str());\
//  for (auto it : boost::stacktrace::stacktrace())\
//    cout << to_string(it) << endl;\

#define THROWX(...) do{\
  stringstream e;\
  e << dostring(__VA_ARGS__);\
  e << boost::stacktrace::stacktrace();\
  throw runtime_error(e.str());}while(0)

//#define THROWX(...) do{\
//  printf("######################################################################\n");\
//  printf("%s\n", dostring(time(0),__PRETTY_FUNCTION__,__FILE__,__LINE__,##__VA_ARGS__).c_str());\
//  cout << boost::stacktrace::stacktrace() << endl;\
//  printf("######################################################################\n");\
//  throw runtime_error(dostring(time(0),__PRETTY_FUNCTION__,__FILE__,__LINE__,##__VA_ARGS__));}while(0)

vector<dnsmasq_lease> get_leases(string dnsmasq_leases) {
  vector<dnsmasq_lease> leases;
  return leases;
}

int baz(string fd) {
  THROWX("Oof! something really bad happened", "fd", fd);
}
int bar(int a) {
  return baz("1");
}
int foo() {
  return bar(1);
}

int main() {

  try {

    LOGX("hello", 123);

    foo();

    for (auto entry : boost::filesystem::directory_iterator("/tmp")) {

      if (fnmatch("create_ap.*.conf.*", entry.path().filename().c_str(), 0) == 0) {
        LOGX(entry);

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
            ++index;
            if (index == 0) {
              lease.mutable_expires()->set_seconds(
                  boost::lexical_cast<::google::protobuf::int64>(it));
            } else {
              lease.GetReflection()->SetString(&lease, lease.GetDescriptor()->field(index), it);
            }
          }

          LOGX(lease.DebugString());

        }


      }

    }

  } catch (const exception &e) {
    LOGX("what", e.what());
    LOGX("phew!");
  }

  return 0;
}
