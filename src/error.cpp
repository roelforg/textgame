#include <general.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <signal.h>

string demangle(const char* symbol) {
  size_t size;
  int status;
  char temp[128];
  char* demangled;
  //first, try to demangle a c++ name
  if (1 == sscanf(symbol, "%*[^(]%*[^_]%127[^)+]", temp)) {
    if (NULL != (demangled = abi::__cxa_demangle(temp, NULL, &size, &status))) {
      std::string result(demangled);
      free(demangled);
      return result;
    }
  }
  //if that didn't work, try to get a regular c symbol
  if (1 == sscanf(symbol, "%127s", temp)) {
    return string(temp);
  }
 
  //if all else fails, just return the symbol
  return string(symbol);
}

#define MAX_FRAMES 100
void backtrace_generator() {
	void* addresses[MAX_FRAMES];
	int size;
	size = backtrace(addresses, MAX_FRAMES);
	char** symbols = backtrace_symbols(addresses, size);
	int x;
	for (x = 0; x < size; x++) {
	 	cerr << x << ": " << demangle(symbols[x]) << endl;
		cerr.flush();
	}
	free(symbols);
}

void signal_handler(int signum)
{
	printf("Caught signal %d\n",signum);

	backtrace_generator();

	//Terminate program
	exit(signum);
}

#define sig signal_handler

void init_error()
{
	signal(SIGSEGV, sig);
	signal(SIGABRT, sig);
	signal(SIGUSR1, sig);
	signal(SIGUSR2, sig);
	atexit(exit_error);
}

void exit_error()
{

}

