#include <general.h>
#include <dlfcn.h>
#include <dirent.h>

extern Level *curr_level;

extern "C" {
void enterLevel(string);
string getNextLevel();
}

vector<string> level_list;

void init_level()
{
	vector<string> files;
	DIR *dir;
	struct dirent *ent;
	dir = opendir (LVL_LOC);
	if (dir != NULL) {

		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL)
			if (ent->d_name[0] != '.' && strncmp(ent->d_name,"entry",5) != 0 && strncmp(ent->d_name, "exit",4) != 0) {
			//printf ("%s\n", ent->d_name);
			char *tmp = (char*)malloc(strlen(ent->d_name));
			bool b = true;
			for (size_t i = 0; i < strlen(ent->d_name); i++)
				if (b && ent->d_name[i] != '.')
					tmp[i] = ent->d_name[i];
				else
					b = false;
			files.push_back(string(tmp));
		}
		closedir (dir);
		for (unsigned i = 0; i < files.size(); i++)
			level_list.push_back(files[i]);
	} else {
		/* could not open directory */
		throw E_GENERAL;
	}
}

string getNextLevel()
{
	if (level_list.size() > 0)
		return level_list[0];
	else
		return "exit";
}

string switchto;

void switchLevel()
{
	curr_level->exit_level();
	if (switchto != "exit")
		for (unsigned i = 0; i < level_list.size(); i++)
			if (level_list[i] == switchto)
				level_list.erase(level_list.begin()+i, level_list.begin()+i+1);
	curr_level->load_level(switchto);
}
void enterLevel(string level)
{
	switchto = level;
	throw E_SWLVL; //it's a hack, but otherwise we'd return to the unloaded shared lib
}

Level::Level(string name)
{
	this->load_level(name);
}

void Level::load_level(string name)
{
	cout << "Loading " << name << "...";
	this->filename = name;
	//open shared lib
	this->hnd = dlopen(string(string(LVL_LOC)+"/"+name+".so").c_str(), RTLD_NOW);
	//just find all the needed commands
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

	//this one will be executed in a bit
	init = dlsym(this->hnd,"shared_init");
	vD tmp;
	if (init == NULL)
		throw string("Symbol shared_init not found!");
	else
		tmp = (vD)init;
	tmp(); //execute shared_init
	cout << "OK!" << endl << "You've entered \"" << name << "\"!" << endl;
	this->FnInit(); //execute level init
}

void Level::exit_level()
{
	void *init;
	this->FnExit(); //execute level exit
	//same as shared_init but this time the exit
	init = dlsym(this->hnd,"shared_exit");
	vD tmp;
	if (init == NULL)
		throw string("Symbol shared_exit not found!");
	else
		tmp = (vD)init;
	tmp();
	//clean up
	dlclose(this->hnd);
	this->hnd = NULL;
}

Level::~Level()
{
	this->exit_level();
}

