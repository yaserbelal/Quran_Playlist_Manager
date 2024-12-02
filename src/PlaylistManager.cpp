#include "PlaylistManager.h"
#include <iostream>
PlaylistManager::PlaylistManager() {}

void PlaylistManager::addPlaylist(const Playlist& playlist) {
	playlists.add(playlist);
}

void PlaylistManager::addSurahToPlaylist(const string& playlistName, const Surah& surah) {
	Playlist* playlist = getPlaylist(playlistName);
	if (playlist) {
		playlist->addSurah(surah);
	}
	else {
		cerr << "\033[31mPlaylist not found:\033[0m " << playlistName << endl;
	}
}

void PlaylistManager::removeSurahFromPlaylist(const string& playlistName, const string& surahName) {
	Playlist* playlist = getPlaylist(playlistName);
	if (playlist) {
		playlist->removeSurah(surahName);
	}
	else {
		cerr << "\033[31mPlaylist not found:\033[0m " << playlistName << endl;
	}
}

void PlaylistManager::displayAllPlaylists() const {
	auto node = playlists.getHead();
	if (!node) {
		cout << "No playlists available." << endl;
		return;
	}
	int i = 1;
	cout << "\033[34mThe current Playlists are: \033[0m" << endl;
	cout << "ID   Playlist" << endl;
	cout << "-----------------------" << endl;
		while (node) {
			cout << i << "   " << node->data.getName() << endl;
			node = node->next;
			i++;
		}
}

void PlaylistManager::displayAllSurahs() const {
	auto* current = playlists.getHead();
	while (current) {
		cout << "--------------------------------------------------------------------\n";
		cout << "\033[34m";
		cout << setw(24) <<" " << "Playlist: " << current->data.getName() << endl;
		cout << "\033[0m";
		cout << "--------------------------------------------------------------------\n";
		current->data.displaySurahs();
		current = current->next;
	}
}

Playlist* PlaylistManager::getPlaylist(const string& name) {
	auto* current = playlists.getHead();
	while (current) {
		if (current->data.getName() == name) {
			return &(current->data);
		}
		current = current->next;
	}
	return nullptr;
}

void PlaylistManager::save(const string& fileName) const {
	ofstream outFile(fileName);
	if (!outFile) {
		cerr << "Error opening file for writing: " << fileName << endl;
		return;
	}

	auto* current = playlists.getHead();
	while (current) {
		// Write playlist header
		outFile << "Playlist: " << current->data.getName() << "\n";

		// Write all surahs in the playlist
		auto* surahNode = current->data.getSurahs().getHead();
		while (surahNode) {
			const Surah& surah = surahNode->data;
			outFile << surah.getName() << "|" << surah.getType() << "|" << surah.getPath() << "\n";
			surahNode = surahNode->next;
		}

		// Add the END separator
		outFile << "END\n";

		current = current->next;
	}

	outFile.close();
	cout << "\033[32mPlaylists saved successfully to \033[0m" << fileName << "\033[32m ^---^ \033[0m\n";
}

void PlaylistManager::load(const string& fileName) {
	ifstream inFile(fileName);
	if (!inFile) {
		cerr << "Error opening file for reading: " << fileName << endl;
		return;
	}
	playlists.clear();

	string line;
	Playlist currentPlaylist("");

	while (getline(inFile, line)) {
		if (line.find("Playlist: ") == 0) { // Line starts with "Playlist: "
			if (!currentPlaylist.getName().empty()) {
				addPlaylist(currentPlaylist); // Save the previous playlist
			}

			string playlistName = line.substr(10); // Extract name after "Playlist: "
			currentPlaylist = Playlist(playlistName); // Start a new playlist

		}
		else if (line == "END") {
			if (!currentPlaylist.getName().empty()) {
				addPlaylist(currentPlaylist); // Save the current playlist
				currentPlaylist = Playlist(""); // Reset for the next playlist
			}

		}
		else { // Parse Surah details
			size_t pos1 = line.find('|');
			size_t pos2 = line.rfind('|');

			if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
				string name = line.substr(0, pos1);
				string type = line.substr(pos1 + 1, pos2 - pos1 - 1);
				string path = line.substr(pos2 + 1);

				Surah surah(name, type, path);
				currentPlaylist.addSurah(surah);
			}
			else {
				cerr << "Invalid surah format in line: " << line << endl;
			}
		}
	}

	// Add the last playlist if it hasn't been added
	if (!currentPlaylist.getName().empty()) {
		addPlaylist(currentPlaylist);
	}

	inFile.close();
	cout << "\033[32mPlaylists loaded successfully from\033[0m " << fileName << "\033[32m ^---^ \033[0m\n";
}

void PlaylistManager::removePlaylist(const string& playlistName) {
	Playlist* playlist = getPlaylist(playlistName);
	if (playlist) {
		playlists.remove(*playlist);  
		cout << "Playlist '" << playlistName << "' removed successfully.\n";
	}
	else {
		cout << "Error: Playlist '" << playlistName << "' not found.\n";
	}
}

DoublyLinkedList<Playlist>& PlaylistManager::getPlaylists()
{
	return playlists;
}

