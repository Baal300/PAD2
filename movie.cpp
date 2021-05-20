#include "movie.h"
#include <iostream>

using namespace std;

int Movie::releaseDate() const
{
    return m_releaseDate;
}

void Movie::setReleaseDate(const int &releaseDate)
{
    m_releaseDate = releaseDate;
}

void Movie::play() const
{
    cout << "The Movie " << m_title << " is playing right now.\n";
}

void Movie::compareOlder(const Movie &movie)
{
    if (m_releaseDate > movie.releaseDate())
    {
        cout << movie.title() << " is older than " << m_title << '\n';
    }
    else
    {
        cout << m_title << " is older than " << movie.title() << '\n';
    }
}

void Movie::printInformation() const
{
    cout << "---------------------------------------\n"
         << "Title: " << m_title << '\n'
         << "Length: " << m_length << " minutes\n"
         << "Genre: " << m_genre << '\n'
         << "Release year: " << m_releaseDate << '\n';

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

Movie::Movie(const string title, const int length, const string genre) : MediaFile(title, length, genre)
{

}

Movie::Movie(const string title, const int length, const string genre, const vector<int> &ratings) : MediaFile(title, length, genre, ratings)
{

}
