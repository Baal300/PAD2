#ifndef MOVIE_H
#define MOVIE_H

#include "mediafile.h"

class Movie : public MediaFile
{
private:
    /*string m_title;
    int m_length;   //Length is in minutes
    string m_genre;
    vector<int> m_ratings;
    int m_releaseDate;  //Only year
    double m_averageRating;
    int m_totalRatings{0};  //Total score of ratings - needed for averageRating
    */
    int m_releaseDate{0};  //Only year
    string m_type{"Series"};
public:
    Movie();
    Movie(const string title, const int length, const string genre);
    Movie(const string title, const int length, const string genre, const vector<int> &ratings);
    int releaseDate() const;
    void setReleaseDate(const int &releaseDate);
    virtual void play() const;
    void compareOlder(const Movie &movie);
    virtual void printInformation() const;
    //ADD eventually virtual destructors
    string type() const;
};

#endif // MOVIE_H
