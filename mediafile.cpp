#include "mediafile.h"
#include <iostream>


using namespace std;


double MediaFile::averageRating() const
{
    return m_averageRating;
}

int MediaFile::length() const
{
    return m_length;
}

string MediaFile::title() const
{
    return m_title;
}

vector<int> MediaFile::ratings() const
{
    return m_ratings;
}

string MediaFile::genre() const
{
    return m_genre;
}

int MediaFile::releaseDate() const
{
    return m_releaseDate;
}

MediaFile::MediaFile(const string title, const int length, const string genre) : m_title{title}, m_length{length}, m_genre{genre}
{

}

MediaFile::MediaFile(const string title, const int length, const string genre, const vector<int> &ratings) : m_title{title}, m_length{length}, m_genre{genre}
{
    for (int rating: ratings)
    {
        addRating(rating);
    }
}

void MediaFile::printInformation() const
{
    cout << "---------------------------------------\n"
         << "Title: " << m_title << '\n'
         << "Length: " << m_length << " minutes\n"
         << "Genre: " << m_genre << '\n';

    if(m_ratings.size() >= 1)
    {
        cout << "Average rating: " << m_averageRating << '\n'
             << "List of ratings: " << '\n';

        for (int rating : m_ratings)
        {
            cout << rating << "\n";
        }

        cout << "---------------------------------------\n";

    }
    else {
        cout << "No ratings available for this title\n"
             << "---------------------------------------\n";
    }

}

void MediaFile::addRating(const int rating)
{
    //Rating has to be between 1 and 5
    if(rating >= 1 && rating <=5)
    {
        m_ratings.push_back(rating);

        //With added rating average rating changes respectively
        m_totalRatings += rating;
        m_averageRating = static_cast<double>(m_totalRatings) / m_ratings.size();

        //cout << "Rating was sucessfully added.\n";
    }
    else
    {
        //try and catch here
        cout << "Rating was not added. Please enter a valid rating from 1-5.\n";
    }


}

void MediaFile::play() const
{
    cout << m_title << " is playing right now.\n";
}




