#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include "mediafile.h"

using namespace std;

class Database
{
private:
    static vector<MediaFile*> m_videos;         //Hint: Vector with pointers of Movie is more storage efficient
    static int m_totalPlaybackTime;
    static int m_averagePlaybackTime;
    static int m_entries;
    static string m_defaultFile;

    //Private constructor to prevent user from creating objects of Database
    Database();

    //Checks if a database file is loaded; this function isn't meant for the user to call
    static void missingFile();

public:
    static void printList();
    static void addVideo(const MediaFile &video);
    static void remove(const int pos);
    static void ratingSort();
    static void printPlaybackTime();
    static void play();
    static void play(const int pos);
    static void playAll();
    static void addRating();
    static void init();
    static void simulateReviews(const int numberOfReviews);
    static void writeFile();
    static int entries();
    static void menu();
    static void compareOlderMovies(const int pos1, const int pos2);

    //Loads file that we passed as an argument to main
    static void loadDefaultFile(const string &defaultFile);
};

#endif // DATABASE_H
