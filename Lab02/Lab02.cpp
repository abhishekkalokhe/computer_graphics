#include<iostream>
#include <fstream>

using namespace std;

int main() 
{

    char arr[9][10];
    ifstream File;
    File.open("input.txt");
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<10; j++)
        {
            File>> arr[i][j];
        }
    }
    
}