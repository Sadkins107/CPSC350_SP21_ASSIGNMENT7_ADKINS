#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "Sort.h"

using namespace std;

Sort::Sort()
{

}

Sort::~Sort()
{

}

void Sort::MakeArray(string fileName)
{
    mFile.open(fileName);

    if (mFile.is_open())
    {
        mFile >> numNums;

        mArray = new double[numNums];  

        for (int i = 0; i < numNums; ++i)
        {
            mFile >> mArray[i];
        }

        mFile.close();
    }
    else
    {
        cout << "Sorry, that file couldn't be opened." << endl;
    }
}

void GetTime(){
    auto current = chrono::system_clock::now();
    auto now_timet = chrono::system_clock::to_time_t(current);
    auto now_local = localtime(&now_timet);
    cout << "Local Time " << std::put_time(now_local, "%c") << endl;
}

void Sort::PrintTime()
{
    for (int i = 0; i < numNums; ++i)
    {
        cout << mArray[i] << endl;
    }
}

void Sort::Bubble()
{
    double temp;

    for (int i = 0; i < numNums - 1; ++i)
    {
      for (int j = 0; j < numNums - i - 1; ++j)
      {
         if (mArray[j] > mArray[j+1])
         {
            temp = mArray[j];
            mArray[j] = mArray[j + 1];
            mArray[j + 1] = temp;
         }
      }
   }
}


void Sort::Selection()
{
    double temp;

    for (int i = 0; i < numNums; ++i)
    {
        int smallest = i;
        for (int j = i + 1; j < numNums; ++j)
        {
            if (mArray[j] < mArray[smallest])
            {
                smallest = j;
            }
        }
        temp = mArray[i];
        mArray[i] = mArray[smallest];
        mArray[smallest] = temp;
    }
}

void Sort::Insertion()
{
    double temp;
    int j;

    for (int i = 1; i < numNums; ++i) {
        j = i;
        while (j > 0 && mArray[j] < mArray[j - 1]) {
            temp = mArray[j];
            mArray[j] = mArray[j - 1];
            mArray[j - 1] = temp;
            --j;
        }
    }
}

void Sort::Merge(double* array, int i, int k)
{
   int j;
   
   if (i < k) {
      j = (i + k) / 2 ;
      
      Merge(array, i, j);
      Merge(array, j + 1, k);
      
      Join(array, i, j, k);
   }
}

void Sort::Join(double* array, int left, int middle, int right) {
    double* merge = new double[right + 1];

    int leftPos = 0;
    int rightPos = middle + 1;
    int mergePos = 0;
    while (leftPos <= middle && rightPos <= right) {
        if (array[leftPos] <= array[rightPos]) {
            merge[mergePos] = array[leftPos];
             ++leftPos;
        }
        else {
            merge[mergePos] = array[rightPos];
            ++rightPos;
        }
        ++mergePos;
    }

    while (leftPos <= middle) {
        merge[mergePos] = array[leftPos];
        ++leftPos;
        ++mergePos;
    }
    
    while (rightPos <= right) {
        merge[mergePos] = array[rightPos];
        ++rightPos;
        ++mergePos;
    }
    
    // Copy merge number back to array
    for (mergePos = 0; mergePos < right + 1; ++mergePos) {
        array[left + mergePos] = merge[mergePos];
    }
}

void Sort::Quick(double* array, int low, int high)
{
   if (low >= high) {
      return;
   }
   
   
   int lowEndIndex = Partition(array, low, high);
   
   Quick(array, low, lowEndIndex);
   Quick(array, lowEndIndex + 1, high);
}

int Sort::Partition(double* array, int low, int high)
{
   int midpoint = low + (high - low) / 2;
   int pivot = array[midpoint];
   int temp;
   
   bool done = false;
   while (!done) {
      while (array[low] < pivot) {
         low += 1;
      }
      
      while (pivot < array[high]) {
         high -= 1;
      }
      
      if (low >= high) {
         done = true;
      }
      else {
         temp = array[low];
         array[low] = array[high];
         array[high] = temp;
         
         ++low;
         --high;
      }
   }
   
   return high;
}

void Sort::Shell(int start, int gap)
{
   int i = 0;
   int j = 0;
   int temp = 0;

   for (i = start + gap; i < numNums; i = i + gap)
   {
      j = i;
      while (j - gap >= start && mArray[j] < mArray[j - gap])
      {
         temp = mArray[j];
         mArray[j] = mArray[j - gap];
         mArray[j - gap] = temp;
         j = j - gap;
      }
   }
}

void Sort::Test(string fileName)
{
    MakeArray(fileName);

    auto start = chrono::system_clock::now();
    Bubble();
    auto stop = chrono::system_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>((stop - start));

    auto tStart = chrono::system_clock::to_time_t(start);
    auto localStart = localtime(&tStart);
    cout << "Bubble Start: " << std::put_time(localStart, "%c") << endl;
    auto tStop = chrono::system_clock::to_time_t(stop);
    auto localStop = localtime(&tStop);
    cout << "Bubble End: " << std::put_time(localStop, "%c") << endl;
    cout << "Bubble Duration: " << duration.count() * 1e-6 << " seconds" << endl;

    cout << endl;

    MakeArray(fileName);
    
    start = chrono::system_clock::now();
    Selection();
    stop = chrono::system_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>((stop - start));

    tStart = chrono::system_clock::to_time_t(start);
    localStart = localtime(&tStart);
    cout << "Selection Start: " << std::put_time(localStart, "%c") << endl;
    tStop = chrono::system_clock::to_time_t(stop);
    localStop = localtime(&tStop);
    cout << "Selection End: " << std::put_time(localStop, "%c") << endl;
    cout << "Selection Duration: " << duration.count() * 1e-6 << " seconds" << endl;

    cout << endl;

    MakeArray(fileName);
    
    start = chrono::system_clock::now();
    Insertion();
    stop = chrono::system_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>((stop - start));

    tStart = chrono::system_clock::to_time_t(start);
    localStart = localtime(&tStart);
    cout << "Insertion Start: " << std::put_time(localStart, "%c") << endl;
    tStop = chrono::system_clock::to_time_t(stop);
    localStop = localtime(&tStop);
    cout << "Insertion End: " << std::put_time(localStop, "%c") << endl;
    cout << "Insertion Duration: " << duration.count() * 1e-6 << " seconds" << endl;

    cout << endl;

    MakeArray(fileName);
    
    start = chrono::system_clock::now();
    Merge(mArray, 0, numNums - 1);
    stop = chrono::system_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>((stop - start));

    tStart = chrono::system_clock::to_time_t(start);
    localStart = localtime(&tStart);
    cout << "Merge Start: " << std::put_time(localStart, "%c") << endl;
    tStop = chrono::system_clock::to_time_t(stop);
    localStop = localtime(&tStop);
    cout << "Merge End: " << std::put_time(localStop, "%c") << endl;
    cout << "Merge Duration: " << duration.count() * 1e-6 << " seconds" << endl;

    cout << endl;

    MakeArray(fileName);
    
    start = chrono::system_clock::now();
    Quick(mArray, 0, numNums - 1);
    stop = chrono::system_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>((stop - start));

    tStart = chrono::system_clock::to_time_t(start);
    localStart = localtime(&tStart);
    cout << "Quick Start: " << std::put_time(localStart, "%c") << endl;
    tStop = chrono::system_clock::to_time_t(stop);
    localStop = localtime(&tStop);
    cout << "Quick End: " << std::put_time(localStop, "%c") << endl;
    cout << "Quick Duration: " << duration.count() * 1e-6 << " seconds" << endl;

    cout << endl;

    MakeArray(fileName);
    
    start = chrono::system_clock::now();
    Shell(0, 3);
    stop = chrono::system_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>((stop - start));

    tStart = chrono::system_clock::to_time_t(start);
    localStart = localtime(&tStart);
    cout << "Shell Start: " << std::put_time(localStart, "%c") << endl;
    tStop = chrono::system_clock::to_time_t(stop);
    localStop = localtime(&tStop);
    cout << "Shell End: " << std::put_time(localStop, "%c") << endl;
    cout << "Shell Duration: " << duration.count() * 1e-6 << " seconds" << endl;
}