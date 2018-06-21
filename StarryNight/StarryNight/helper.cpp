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

int seedCount = 0;
float fillStar(struct star &s, float posMin, float posMax)
{
	if (s.size > 0)
	{
		s.size -= 0.1f;
		return -1;
	}
	//srand(seedCount++);
	seedCount %= INT_MAX;
	if (s.starObj == nullptr) s.starObj = gluNewQuadric();
	s.size = randomFloatBetween(1, 1.2);
	float lengthPos = randomFloatBetween(posMin, posMax);
	getRandomVectorWithLength(lengthPos, s.vec);
	return 0;
}

void getRandomVectorWithLength(float length, float *vec)
{
	vec[0] = randomFloatBetween(-1.0f, 1.0f);
	vec[1] = randomFloatBetween(-1.0f, 1.0f);
	vec[2] = randomFloatBetween(-1.0f, 1.0f);

	double normScalar = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

	vec[0] = vec[0] / normScalar * length;
	vec[1] = vec[1] / normScalar * length;
	vec[2] = vec[2] / normScalar * length;
}

float randomFloatBetween(float lo, float hi)
{
	return lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
}

int randomIntBetween(int lo, int hi)
{
	return rand() % hi + lo;
}
