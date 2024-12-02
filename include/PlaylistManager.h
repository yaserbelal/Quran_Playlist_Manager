#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include "DoublyLinkedList.h"
#include "Playlist.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
class PlaylistManager {
private:
    DoublyLinkedList<Playlist> playlists; 

public:
    PlaylistManager();
    void addPlaylist(const Playlist& playlist);
    void addSurahToPlaylist(const string& playlistName, const Surah& surah);
    void removeSurahFromPlaylist(const string& playlistName, const string& surahName);
    void displayAllPlaylists() const;
    void displayAllSurahs() const;
    Playlist* getPlaylist(const string& name);
    void save(const string& fileName) const;
    void load(const string& fileName);
    void removePlaylist(const string& playlistName);
    DoublyLinkedList<Playlist>& getPlaylists();

};

#endif // PLAYLISTMANAGER_H
