#ifndef RANDOM_H   
#define RANDOM_H

#include <chrono>
#include <random>
#include <fstream>
#include <string>

using namespace std;

class Random
{
    public:
        Random();
        ~Random();

        void RandomFile(int numNums, string fileName);
        double CreateRandom();
    
    private:
        minstd_rand0 mGenerator;
        fstream mFile;

};

#endif