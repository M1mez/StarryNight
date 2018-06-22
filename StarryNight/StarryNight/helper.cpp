#include "helper.h"

using namespace std;
namespace fs = experimental::filesystem;
int seedCount = 0;

/*
<summary>
get the count of folders of a given path, containing specified name
</summary>
<param name = "folder">the path in which we look for subfolders</param>
<param name = "name">the name we are looking for</param>
*/
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

/*
<summary>
makes sure a given float never goes above |(-) 360| in value
</summary>
<param name="angle">the given float</param>
*/
void keepFloatBelow360(float *angle)
{
	if (*angle <= -360.0f) *angle += 360.0f;
	else if (*angle >= 360.0f) *angle -= 360.0f;
}



/*
<summary>
fills the star struct instance with random values for size,shrinkspeed, and position
the length of the vector from origin is bound with an lower and upper limit
</summary>
<param name="s"> </param>
<param name="posMin">lower limit of position </param>
<param name="posMax">upper limit of position </param>
*/
float fillStar(struct star &s, float posMin, float posMax)
{
	seedCount %= INT_MAX;
	if (s.starObj == nullptr) s.starObj = gluNewQuadric();
	s.maxSize = randomFloatBetween(0.2, 0.5);
	s.shrinkSpeed = randomFloatBetween(s.maxSize / 20, s.maxSize / 3);
	s.size = randomFloatBetween(0.1, s.maxSize);
	float lengthPos = randomFloatBetween(posMin, posMax);
	getRandomVectorWithLength(lengthPos, s.vec);
	return 0;
}

/*
<summary>
a given "vector"(float array) is filled with random values between -1 and 1
the "vector" is also normalized (length of 1)
</summary>
<param name="lenght"> lenght of the given vector </param>
<param name="vec"> given vector </param>
*/
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

/*
<summary>
gives a random float between a lower bound and an upper bound
</summary>
<param name="lo">lower bound</param>
<param name="hi">upper bound</param>
*/
float randomFloatBetween(float lo, float hi)
{
	return lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
}

/*
<summary>
gives a random int between a lower bound and an upper bound
</summary>
<param name="lo">lower bound</param>
<param name="hi">upper bound</param>
*/
int randomIntBetween(int lo, int hi)
{
	return rand() % hi + lo;
}
