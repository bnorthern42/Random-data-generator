/**
* @Brief A bit of an old file, Some code came from a Stack Overflow webpage. I do not claim 100% ownership for the idea of the code
* @Param rando.exe
* @Param <Size in KB you want>
* @return A CSV File of size KB, does 64byte strings in 8 columns. Minimum data size = 512 Bytes / 0.5 KB
*/

#include <iostream>
#include <fstream>
#include <string>
#include <omp.h>
#include <cmath> //for std::round
#include <vector>
#include <random>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n
using namespace std;
typedef std::vector<char> char_array;

char_array charset() //stuck overflow lambda versions
{
    //Change this to suit
    return char_array( 
    {
    'A','B','C','D','E','F',
    'G','H','I','J','K',
    'L','M','N','O','P',
    'Q','R','S','T','U',
    'V','W','X','Y','Z'
    });
};    

// given a function that generates a random character,
// return a string of the requested length
std::string random_string( size_t length, std::function<char(void)> randchar )
{
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

int main(int argv, char* argc[])
{
    if(argv < 2)
    {
        cout << "Correct Usage: program.exe <size of data>";
        cout << "\nTry Again!\n";
        return 1;
    }
     //Independent of character set, 
    //Distribution can be changed
    //Output is non-deterministic
    const auto ch_set = charset();
    std::default_random_engine rng(std::random_device{}()); 
    std::uniform_int_distribution<> dist(0, ch_set.size()-1);
    auto randchar = [ ch_set,&dist,&rng ](){return ch_set[ dist(rng) ];};
           double size = stod(argc[1]);
           auto length = 64;
           ofstream outF;
          
          long int byte = 1;
           long int kilo = 1024;
           long int columns = 8;
           long int rows = ((size*kilo)/length)/columns;
          
                cout << "for "<< length << " byte strings at " << columns << " Columns, this will equal : " << rows*columns << "  data cells, or " << rows*columns*length << " bytes of data\n";
                 string filename = "datasize_"+to_string((std::round(size)))+"KB.csv";
            outF.open(filename);
                //outF << "ID, DATA_R" << endl;
                
                double start = omp_get_wtime();
                for(int r = 0; r < rows; r++){
                outF << r+1 << ", ";
                for(int i = 0; i < columns ; i++ )
                {
                  string aa = random_string(length, randchar); //1
               
                    outF << aa << ", ";
                }
                outF << endl;
                }
                double end = omp_get_wtime();
                cout << "Data Exported to: " << filename << "\nThis took: " << end-start << " seconds to run\n";
                outF.close();
    return 0;
    
    
    
    
}
