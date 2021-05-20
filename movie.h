#ifndef MOVIE_H
#define MOVIE_H

#include "mediafile.h"

class Movie : public MediaFile
{
private:
    string m_title;
    int m_length;   //Length is in minutes
    string m_genre;
    vector<int> m_ratings;
    int m_releaseDate;  //Only year
    double m_averageRating;
    int m_totalRatings{0};  //Total score of ratings - needed for averageRating
public:
    Movie(const string title, const int length, const string genre);
    Movie(const string title, const int length, const string genre, const vector<int> &ratings);
    int releaseDate() const;
    void setReleaseDate(const int &releaseDate);
    void play() const;
    void compareOlder(const Movie &movie);
    void printInformation() const;
};

#endif // MOVIE_H
