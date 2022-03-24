#include "includes.h"

void submit(vector<string> result)
{
    ofstream solution_txt("../output/solution.txt");
    // ofstream solution_txt("/output/solution.txt");

    if (solution_txt.is_open())
    {
        
        for (unsigned int i = 0; i < result.size(); i++)
        {
            solution_txt << result[i] << "\r\n";
        }
        
        solution_txt.close();
    }
    else
    {
        cout << "Open solution.txt failed." << endl;
        exit(-1);
    }

    return;
}
