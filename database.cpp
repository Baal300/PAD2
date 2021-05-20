#include "database.h"
#include "movie.h"
#include "series.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <time.h>

using namespace std;

vector<MediaFile*> Database::m_videos;
int Database::m_totalPlaybackTime{0};
int Database::m_averagePlaybackTime{0};
int Database::m_entries{0};
string Database::m_defaultFile;

int Database::entries()
{
    m_entries = m_videos.size();
    return m_entries;
}

void Database::menu()
{
    do{
        int menuSelection;

        //Try and Catch, in case user enters an invalid number
        do{
            try
            {
                cout << "*************MENU*************\n"
                     << "Please select an option from the menu by entering one of the following numbers\n"
                     << "(1) Play all videos\n"
                     << "(2) Play a video\n"
                     << "(3) Add rating to a video\n"
                     << "(4) Load video database from a file\n"
                     << "(5) Save video database\n"
                     << "(6) Quit\n"
                     << "\nMenu selection: ";

                cin >> menuSelection;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //In case we have extraneous inputs

                if (cin.fail())
                {
                    cin.clear(); //clears error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes bad input from stream
                    throw invalid_argument("Enter only valid numbers please!");
                }
                else if (menuSelection < 1 || menuSelection > 6)
                {
                    throw invalid_argument("Please enter a valid number from 1-6!");
                }

            }
            catch (invalid_argument &invalidNumber)
            {
                cerr << invalidNumber.what() << '\n';
                continue;
            }

            break;
        }while(true);

        switch (menuSelection) {
        case 1:
            playAll();
            break;
        case 2:
            play();             //Has to recognize which type of Media File we want to play
            break;
        case 3:
            addRating();
            break;
        case 4:
            init();
            break;
        case 5:
            writeFile();
            break;
        case 6:
            break;
        default:
            cerr << "ERROR\n";
            break;
        }

        //If user enters 6 loop is broken and user quits menu, otherwise menu opens again
        if(menuSelection == 6)
        {
            break;
        }

    }while(true);
}

void Database::compareOlderMovies(const int pos1, const int pos2)
{
    //Need a way to call compareOlder from Movie class with a MediaFile object
    Movie* a = static_cast<Movie*>(m_videos[pos1-1]);
    Movie* b = static_cast<Movie*>(m_videos[pos2-1]);
    a->compareOlder(*b);
}

Database::Database()
{

}


void Database::printList()
{
    cout << "*************MEDIAFILE DATABASE*************\n";
    for (int i{0}; i < m_videos.size(); i++)
    {
        cout << "\n<<" << i+1 << ">>\n";
        Movie* a = static_cast<Movie*>(m_videos[i]);

        //Identify as Movie if MediaFile has release date //Doesn't work WIP
        if(a->releaseDate() != 0)
        {
            a->printInformation();
        } else {
        m_videos[i]->printInformation();
        }
    }
}

void Database::addVideo(const MediaFile &video)
{
    MediaFile* dynamicVideo = new MediaFile(video);   //The object will keep their value until end of program
    m_videos.push_back(dynamicVideo);
}

void Database::remove(int pos)
{
    delete m_videos[pos];   //Free the dynamically located memory
    m_videos.erase(m_videos.begin()+pos);   //Removes the pointer

}

//Comparison function for std::sort()
bool descendingRating(const MediaFile & l, const MediaFile & r)
{
    return l.averageRating() > r.averageRating();
}

//Sorts by descending order of average ratings
void Database::ratingSort()
{
    sort(*m_videos.begin(), *m_videos.end(), descendingRating);
}

void Database::printPlaybackTime()
{
    cout << "Total playback time for all videos: " << m_totalPlaybackTime << '\n'
         << "Average playback time for all videos: " << m_averagePlaybackTime << '\n';
}

void Database::play()
{
    missingFile();
    int pos;

    //Error handling for position input
    do
    {
        try
        {
            cout << "Please enter the position of the media file you want to play: ";
            cin >> pos;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //In case we have extraneous inputs

            //In case of strings or characters as inputs
            if (cin.fail())
            {
                cin.clear(); //clears error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes bad input from stream
                throw invalid_argument("Only enter valid numbers please!");
            }
            //In case of an invalid position input
            else if (pos > m_videos.size() || pos <= 0)
            {
                throw invalid_argument("Please enter a valid position!");
            }
        }
        catch (invalid_argument &invalidPosition)
        {
            cerr << invalidPosition.what() << '\n';
            continue;
        }
        break;
    }while(true);

    //Another play method will be called depending on type of Media File
    Movie* m = static_cast<Movie*>(m_videos[pos-1]);
    Series* s = static_cast<Series*>(m_videos[pos-1]);

    /*
    if(m->type() == "Movie"){
        m->play();
        return;
    }
    else if(s->type() == "Series"){
        s->play();
        return;
    }
    */

    play(pos);
}

void Database::play(const int pos)
{
    missingFile();
    //Has to recognize which type of mediafile we want to play
    m_videos[pos-1]->play(); //Position 1 = index 0 in the vector
    m_totalPlaybackTime += m_videos[pos-1]->length();
    m_averagePlaybackTime = static_cast<double>(m_totalPlaybackTime) / m_videos.size();
}

void Database::playAll()
{
    missingFile();
    for (int i{0}; i < m_videos.size(); i++)
    {
        m_videos[i]->play();
    }

}

void Database::missingFile()
{
    try
    {
        if (m_videos.size() == 0)
        {
            throw invalid_argument("Missing database file");
        }
    }
    catch (invalid_argument &missingFile)
    {
        cerr << missingFile.what() <<'\n';
        init();         //Lets the user enter a file if database file is missing or empty
    }
}

void Database::loadDefaultFile(const string &defaultFile)
{
    m_defaultFile = defaultFile;
}

void Database::addRating()
{
    cout << "Please enter the position of the movie you want to rate: ";
    int pos;
    cin >> pos;
    cout << "You want to rate the movie " << m_videos[pos-1]->title() << '\n'
         << "Enter an integer from 1 to 5 as a rating: ";
    int rating;
    cin >> rating;
    m_videos[pos-1]->addRating(rating);
}

void Database::init()
{
    ifstream source;
    string sourceFileName;
    int invalidFileCounter{0};
    do
    {
        try
        {
            cout << "Enter database file: ";
            cin >> sourceFileName;
            source.open(sourceFileName.c_str(), ios::in);

            if (!source)
            {
                throw invalid_argument(sourceFileName + " cannot be opened!");
            }

        }
        catch(invalid_argument &invalidFile)
        {
            cerr << invalidFile.what() << '\n';
            invalidFileCounter++;

            if(invalidFileCounter == 3)
            {
                source.open(m_defaultFile, ios::in);
                cout << "************3 invalid inputs************\n"
                     << m_defaultFile << " was loaded instead.\n";
                break;
            }

            continue;
        }

        //Set counter to 0 again if file can be opened
        invalidFileCounter = 0;
        break;
    }while(true);



    while(!source.eof())    //Don't know if eof() is okay, it reads to end of file but while-loop only ends after error flag is set
    {
        //variables for inputs to database; struct might be possible instead
        string inputTitle;
        int inputLength{-1};
        vector<int> inputRatings;
        string inputGenre;
        int inputReleaseDate{0};

        string line;

        //Reads file as lines
        while(getline(source, line))
        {
            if (line.find("Titel: ") != string::npos)
            {
                /*Gets a subtring with line.find(' ')+1 as starting
                  position to get the substring after the whitespace in "Titel: " until the end of the whole string*/
                inputTitle = line.substr(line.find(' ')+1, line.npos);
            }

            if (line.find("Laenge: ") != string::npos)
            {
                inputLength = stoi(line.substr(line.find(' ')+1, line.npos) );
                break;                  //Don't read as lines anymore
            }

        }

        string word;

        //Read file as words
        while (source >> word)
        {
            if( (word != "Bewertungen:") && (word != "Genre:") && (word != "Erscheinungsdatum:") && (word!= "*****"))
            {
                inputRatings.push_back(stoi(word));     //Ratings are stored in a vector
            }

            if(word == "Genre:")
            {
                source >> word;
                inputGenre = word;
            }
            //Check for release date
            if(word == "Erscheinungsdatum:")
            {
                source >> word;
                inputReleaseDate = stoi(word);
                break;
            } else if (word == "*****") {
                break;
            }
        }

        //Create a Movie object to include in database
        Movie inputMovie(inputTitle, inputLength, inputGenre, inputRatings);

        //Only if there is a release date for the entry
        if(inputReleaseDate != 0)
        {
        inputMovie.setReleaseDate(inputReleaseDate);
        }

        //Adds movie to database
        Database::addVideo(inputMovie);
    }
    source.clear(); //removes eof error flag
    source.close();

    Database::printList();

}

void Database::simulateReviews(const int numberOfReviews)
{
    for(int i{0}; i < numberOfReviews; i++)
    {
        m_videos[rand()%m_videos.size()]->addRating((rand()%5)+1); //adds random rating between 1 and 5 to a random video; potential macro for readability
    }
}

void Database::writeFile()
{
     string fileName;
     ofstream textfile;
     int invalidFileCounter{0};
     do
     {
         try
         {
             cout << "Enter database file: ";
             cin >> fileName;
             textfile.open(fileName.c_str(), ios::out);

             if (!textfile)
             {
                 throw invalid_argument(fileName + " cannot be opened!");
             }

         }
         catch(invalid_argument &invalidFile)
         {
             cerr << invalidFile.what() << '\n';
             invalidFileCounter++;

             if(invalidFileCounter == 3)
             {
                 textfile.open(m_defaultFile, ios::in);
                 cout << "************3 invalid inputs************\n"
                      << m_defaultFile << " was loaded instead.\n";
                 break;
             }

             continue;
         }

         //Set counter to 0 again if file can be opened
         invalidFileCounter = 0;
         break;
     }while(true);

      textfile << "Film-Datenbank\nEintraege: " << m_videos.size();

     for (int i{0}; i < m_videos.size(); i++)
     {
         textfile << "\n*****\nTitel: " << m_videos[i]->title()
                  << "\nLaenge: " << m_videos[i]->length()
                  << "\nBewertungen: ";
         for (int rating : m_videos[i]->ratings())
         {
            textfile << rating << ' ';
         }
         textfile << "\nGenre: " << m_videos[i]->genre();
     }

     textfile.close();
     cout << fileName << " saved.\n";
}


