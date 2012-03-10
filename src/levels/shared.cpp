//some stuff for init's

#include <level.h>
#include <dlfcn.h>

using namespace std;

typedef void (*hC)(string);
typedef void (*vD)();
typedef string (*rS)();

namespace Fn {
hC enterLevel;
rS getNextLevel;
}

extern "C" {
void shared_init();
void shared_exit();
}

void shared_init()
{
	void *hnd, *init;
	hnd = dlopen(NULL, RTLD_NOW);
	init = dlsym(hnd,"enterLevel");
	if (init == NULL)
	{
		throw string("Symbol enterLevel not found!");
	}
	else
		Fn::enterLevel = (hC)init;
	init = dlsym(hnd,"getNextLevel");
	if (init == NULL)
	{
		throw string("Symbol getNextLevel not found!");
	}
	else
		Fn::getNextLevel = (rS)init;
	dlclose(hnd);
}

void shared_exit()
{

}

void enterLevel(string a)
{
	Fn::enterLevel(a);
}

string getNextLevel()
{
	return Fn::getNextLevel();
}

void goNextLevel()
{
	enterLevel(getNextLevel());
}

