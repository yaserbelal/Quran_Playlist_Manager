#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "PlaylistManager.h"
#include <string>
#include <iostream>
#include <irrKlang.h>
class PlaylistManger;
using namespace std;
using namespace irrklang;
class AudioPlayer {
private:
    ISoundEngine* soundEngine;
    ISound* currentSound;     
    Playlist* currentPlaylist;
    DoublyLinkedList<Surah>::Node* currentSurahNode; 

public:
    AudioPlayer();
    ~AudioPlayer();

    void stop();

    void playPlaylist(const std::string& playlistName, PlaylistManager& playlistManager);

    void next();

    void Previous();

    void pause();

    void resume();

    bool isPlaying() const;
};

#endif // AUDIOPLAYER_H
