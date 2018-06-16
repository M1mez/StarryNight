#include "helper.h"

using namespace std;
namespace fs = experimental::filesystem;

int getCountOfNamesContainingString(std::string folder, std::string name)
{
	stringstream ss;
	int count = 0;
	for (const auto& p : fs::directory_iterator(folder))
	{
		ss << p;
		string str = ss.str();
		if (str.find(name) != string::npos) count++;
		ss.str(string());
	}
	return count;
}

void keepFloatBelow360(float *angle)
{
	if (*angle <= -360.0f) *angle += 360.0f;
	else if (*angle >= 360.0f) *angle -= 360.0f;
}