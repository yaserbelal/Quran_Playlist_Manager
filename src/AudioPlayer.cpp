#include "AudioPlayer.h"
#include <iostream>
#include <string>

AudioPlayer::AudioPlayer()
    : soundEngine(createIrrKlangDevice()), currentSound(nullptr), currentPlaylist(nullptr), currentSurahNode(nullptr) {
    if (!soundEngine) {
        cerr << "Error: Could not initialize sound engine." << endl;
    }
}

AudioPlayer::~AudioPlayer() {
    if (soundEngine) {
        soundEngine->drop(); // Release the sound engine
    }
}

void AudioPlayer::playPlaylist(const string& playlistName, PlaylistManager& playlistManager) {
    stop(); 
    currentPlaylist = playlistManager.getPlaylist(playlistName);

    if (!currentPlaylist) {
        cerr << "Error: Playlist '" << playlistName << "' not found in PlaylistManager." << endl;
        return;
    }

    currentSurahNode = currentPlaylist->getSurahList().getHead();

    if (!currentSurahNode) {
        cerr << "Playlist '" << playlistName << "' is empty." << endl;
        return;
    }

    
    const string& surahPath = currentSurahNode->data.getPath();
    currentSound = soundEngine->play2D(surahPath.c_str(), false, false, true);
    cout << "Playing: " << currentSurahNode->data.getName() << endl;
    if (!currentSound) {
        cerr << "Error: Could not play file: " << surahPath << endl;
    }
}

void AudioPlayer::next() {
    if (!currentSurahNode || !currentSurahNode->next) {
        cout << "End of playlist reached." << endl;
        return;
    }
    currentSurahNode = currentSurahNode->next; 
    const string& surahPath = currentSurahNode->data.getPath();

    stop(); 
    currentSound = soundEngine->play2D(surahPath.c_str(), false, false, true);
    cout << "Playing: " << currentSurahNode->data.getName() << endl;
    if (!currentSound) {
        cerr << "Error: Could not play file: " << surahPath << endl;
    }
}

void AudioPlayer::Previous() {
    if (!currentSurahNode || !currentSurahNode->prev) {
        cout << "Start of playlist reached." << endl;
        return;
    }

    currentSurahNode = currentSurahNode->prev; 
    const string& surahPath = currentSurahNode->data.getPath();

    stop(); 
    currentSound = soundEngine->play2D(surahPath.c_str(), false, false, true);
    cout << "Playing: " << currentSurahNode->data.getName() << endl;

    if (!currentSound) {
        cerr << "Error: Could not play file: " << surahPath << endl;
    }
}

void AudioPlayer::pause() {
    if (currentSound && !currentSound->getIsPaused()) {
        currentSound->setIsPaused(true);
        cout << "Sound paused." << endl;
    }
    else {
        cerr << "Error: No sound is playing to pause." << endl;
    }
}

void AudioPlayer::resume() {
    if (currentSound && currentSound->getIsPaused()) {
        currentSound->setIsPaused(false);
        cout << "Sound resumed." << endl;
    }
    else {
        cerr << "Error: No paused sound to resume." << endl;
    }
}

void AudioPlayer::stop() {
    if (currentSound) {
        currentSound->stop();
        currentSound->drop();
        currentSound = nullptr;
    }
}

bool AudioPlayer::isPlaying() const {
    return currentSound && !currentSound->isFinished();
}
