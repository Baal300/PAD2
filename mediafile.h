#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <string>
#include <vector>

using namespace std;

class MediaFile
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
    MediaFile(const string title, const int length, const string genre);
    MediaFile(const string title, const int length, const string genre, const vector<int> &ratings);
    void printInformation() const;
    void addRating(const int rating);
    void play() const;
    double averageRating() const;
    int length() const;
    string title() const;
    vector<int> ratings() const;
    string genre() const;
    int releaseDate() const;
};

#endif // MEDIAFILE_H
