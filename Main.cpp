#include <iostream>
#include <fstream>

#include "Random.h"
#include "Sort.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        string input = argv[1];
        string fileName = argv[2];
        if (input == "Create")
        {
            fstream file;
            file.open(fileName);

            int numNums;


            if (file.is_open())
            {
                file >> numNums;

                file.close();
            }

            Random* rand = new Random();

            rand->RandomFile(numNums, fileName);
        }
        else if (input == "Sort")
        {
            Sort* sort = new Sort();

            sort->Test(fileName);
        }
    }

    return 0;
}