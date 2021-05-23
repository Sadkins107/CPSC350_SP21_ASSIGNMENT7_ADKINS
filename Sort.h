#ifndef SORT_H
#define SORT_H

#include <array>
#include <fstream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <string>

using namespace std;

class Sort
{
    public:
        Sort();
        ~Sort();

        void MakeArray(string fileName);

        time_t GetTime();
        time_t Start();
        time_t Stop();
        void PrintTime();

        void Bubble();
        void Selection();
        void Insertion();
        void Merge(double* array, int i, int k);
        void Join(double* array, int left, int middle, int right);
        void Quick(double* array, int low, int high);
        int Partition(double* array, int low, int high);
        void Shell(int start, int gap);

        void Test(string fileName);

    private:
        fstream mFile;

        int numNums;
        double* mArray;

};

#endif