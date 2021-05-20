#include <iostream>
#include "mediafile.h"
#include "database.h"
#include "movie.h"
#include <vector>
#include <time.h>
#include <string>
using namespace std;

//argv[1] = "database.txt"
int main(int argc, char *argv[])
{
    srand(time(NULL));
    //Pass the argument from main to database to use it as a member variable
    Database::loadDefaultFile(argv[1]);

    Movie a("Hello", 12, "Thriller");
    a.setReleaseDate(1991);
    a.printInformation();


    Database::menu();
    Database::compareOlderMovies(1,2);
    return 0;
}
