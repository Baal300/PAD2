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
    cout << "The Movie " << title() << " is playing right now.\n";
}

void Movie::compareOlder(const Movie &movie)
{
    if (m_releaseDate > movie.releaseDate())
    {
        cout << movie.title() << " is older than " << title() << '\n';
    }
    else
    {
        cout << title() << " is older than " << movie.title() << '\n';
    }
}

void Movie::printInformation() const
{
    cout << "---------------------------------------\n"
         << "*Movie*\n"
         << "Title: " << title() << '\n'
         << "Length: " << length() << " minutes\n"
         << "Genre: " << genre() << '\n'
         << "Release year: " << m_releaseDate << '\n';

    if(ratings().size() >= 1)
    {
        cout << "Average rating: " << averageRating() << '\n'
             << "List of ratings: " << '\n';

        for (int rating : ratings())
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

string Movie::type() const
{
    return m_type;
}

Movie::Movie()
{

}

Movie::Movie(const string title, const int length, const string genre) : MediaFile(title, length, genre)
{

}

Movie::Movie(const string title, const int length, const string genre, const vector<int> &ratings) : MediaFile(title, length, genre, ratings)
{

}
