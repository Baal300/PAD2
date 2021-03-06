#ifndef SERIES_H
#define SERIES_H

#include "mediafile.h"


class Series : public MediaFile
{
private:
    string m_title;
    int m_length;   //Length is in minutes
    string m_genre;
    vector<int> m_ratings;
    double m_averageRating;
    int m_totalRatings{0};
    int m_numberOfEpisodes;
    int m_currentEpisode;
    vector <MediaFile> series; //Vector contains series with its episodes
    string m_type{"Series"}; //Could use enum for m_type
public:
    Series(const string title, const int length, const string genre);
    virtual void play();
    void play(int episode);
    int numberOfEpisodes() const;
    void setNumberOfEpisodes(int numberOfEpisodes);
    int currentEpisode() const;
    void setCurrentEpisode(int currentEpisode);
    virtual void printInformation() const;
    string type() const;
};

#endif // SERIES_H
