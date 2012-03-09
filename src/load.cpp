#include <general.h>
#include <dlfcn.h>

extern "C" void enterLevel(string level)
{
	cout << level << endl;
}

Level::Level(string name)
{
	this->filename = name;
	this->hnd = dlopen(string("/data/textgame/lib/"+name+".so").c_str(), RTLD_LAZY);
	void* init = dlsym(this->hnd,"init");
	if (init == NULL)
		throw string("Symbol init not found!");
	else
		this->FnInit = (vD)init;
	init = dlsym(this->hnd,"exit");
	if (init == NULL)
		throw string("Symbol exit not found!");
	else
		this->FnExit = (vD)init;
	init = dlsym(this->hnd,"handleCommand");
	if (init == NULL)
		throw string("Symbol handleCommand not found!");
	else
		this->FnHandle = (hC)init;
}

Level::~Level()
{
	dlclose(this->hnd);
}

