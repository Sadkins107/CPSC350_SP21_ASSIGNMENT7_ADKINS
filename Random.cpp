#include <chrono>
#include <random>
#include <iostream>

#include "Random.h"

using namespace std;

Random::Random()
{
    mGenerator.seed(chrono::system_clock::now().time_since_epoch().count());
}

Random::~Random()
{

}

double Random::CreateRandom()
{
    return mGenerator();
}

void Random::RandomFile(int numNums, string fileName)
{
    mFile.open(fileName);

    if (mFile.is_open())
    {
        mFile << numNums << endl;

        for (int i = 1; i <= numNums; ++i)
        {
            mFile << this->CreateRandom() << endl;
        }

        mFile.close();
    }
    else
    {
        cout << "Sorry, that file couldn't be opened." << endl;
    }
}