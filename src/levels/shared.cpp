//some stuff for init's

#include <level.h>
#include <dlfcn.h>

using namespace std;

typedef void (*hC)(string);
typedef void (*vD)();

namespace Fn {
hC enterLevel;
}

extern "C" {
void shared_init();
void shared_exit();
}

void shared_init()
{
	void *hnd;
	hnd = dlopen(NULL, RTLD_NOW);
	void* init = dlsym(hnd,"enterLevel");
	if (init == NULL)
	{
		throw string("Symbol enterLevel not found!");
	}
	else
		Fn::enterLevel = (hC)init;
	dlclose(hnd);
}

void shared_exit()
{

}

void enterLevel(string a)
{
	Fn::enterLevel(a);
}

