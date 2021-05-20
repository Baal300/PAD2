#include "series.h"
#include <iostream>
#include <assert.h>

using namespace std;

int Series::numberOfEpisodes() const
{
    return m_numberOfEpisodes;
}

void Series::setNumberOfEpisodes(int numberOfEpisodes)
{
    m_numberOfEpisodes = numberOfEpisodes;
}

int Series::currentEpisode() const
{
    return m_currentEpisode;
}

void Series::setCurrentEpisode(int currentEpisode)
{
    m_currentEpisode = currentEpisode;
}

Series::Series(const string title, const int length, const string genre) : MediaFile(title, length, genre)
{

}

void Series::play()
{
    cout << "Episode " << m_currentEpisode << "von der Serie " << m_title << "wird jetzt abgepielt.\n";

    //Set next episode only if there is one available
    if(m_currentEpisode < numberOfEpisodes())
    {
        setCurrentEpisode(m_currentEpisode+1);
    }
}

void Series::play(int episode)
{
    assert((episode > 0) && (episode <= numberOfEpisodes())); //Should never happen if we handle the user input correctly

    cout << "Episode " << episode << "von der Serie " << m_title << "wird jetzt abgepielt.\n";

    //Set next episode only if there is one available
    if(episode < numberOfEpisodes())
    {
        setCurrentEpisode(episode+1);
    }
}
