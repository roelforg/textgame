#ifndef __LEVEL_SHARED_H__
#define __LEVEL_SHARED_H__

#define CMD(x) } else if (args[0] == x) {
#define ADDV(x,y) x.push_back(y);
#define DELV(x,y) x.erase(x.begin()+y, x.end()+y);
#define TRUNCV(x) x.erase(x.begin(), x.end());
#define FIND(x) cout << "Found item: " << x << endl; \
items.push_back(x);
#define ACHIEVE(x) achievements.push_back(EA_##x);

#define hC_begin vector<string> args = parse_args(command); \
if (0) { //hack for the CMD macro
#define hC_end } else { \
throw E_CMDNOTFOUND; \
}

vector<string> items;
#ifndef NOEA
vector<EA_achieve> achievements;
#endif

bool has_item(string item)
{
	bool rc = false;
	for (unsigned i = 0; i < items.size(); i++)
		if (items[i] == item)
		{
			rc = true;
			break;
		}
	return rc;
}

#ifndef NOEA
bool has_achievement(EA_achieve ach)
{
	bool rc = false;
	for (unsigned i = 0; i < achievements.size(); i++)
		if (achievements[i] == ach)
		{
			rc = true;
			break;
		}
	return rc;
}
#endif

vector<string> parse_args(string cmd)
{
	vector<string> rc;
	string tmp;
	size_t found = 0, of = 0;
	found = cmd.find(' ', found);
	if (found != string::npos)
	while (found != string::npos)
	{
		tmp = cmd.substr((of == 0)?0:of+1, found-of);
		ADDV(rc,tmp);
		of = found;
		found = cmd.find(' ', found+1);
	}
	ADDV(rc,cmd.substr((of == 0)?0:of+1,found-of));

	return rc;
}

#endif

