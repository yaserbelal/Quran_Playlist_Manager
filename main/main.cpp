#include <iostream>
#include <string>
#include <conio.h>
#include"AudioPlayer.h"
#include "PlaylistManager.h"
using namespace std;

void displayMenu() {
	cout << "\033[35m\n======== Quran Playlist Manager Menu ========\033[0m\n";
	cout << "1- Add a new playlist\n";
	cout << "2- Add Surah to an existing playlist\n";
	cout << "3- Remove Surah from an existing playlist\n";
	cout << "4- Update the order of existing playlist \n";
	cout << "5- Display All Current Playlists\n";
	cout << "6- Display All Playlists surah\n";
	cout << "7- Display surah in a specific Playlist\n";
	cout << "8- Play surah from specific playlist\n";
	cout << "   Use left arrow (<-) to play the previous surah\n";
	cout << "   Use right arrow (->) to play the next surah \n";
	cout << "   Use up arrow (^) to pause the current surah\n";
	cout << "   Use down arrow (V) to resume the paused surah \n";
	cout << "   Press q to exit current playlist & return back to menu\n";
	cout << "9- Save an existing playlist to a file\n";
	cout << "10- Load an existing playlist from a file \n";
	cout << "11- Remove an existing playlist\n";
	cout << "0- Exit\n";
	cout << "=============================================\n";
	cout << "Enter your choice: ";
}

void handleAddPlaylist(PlaylistManager& manager) {
	cin.ignore();
	string playlistName;
	cout << "Enter the name of the playlist: ";
	cin >> playlistName;
	Playlist newPlaylist(playlistName);
	manager.addPlaylist(newPlaylist);
	cout << "\033[32mPlaylist added successfully ^---^.\033[0m\n";
}

void handleAddSurahToPlaylist(PlaylistManager& manager) {
	cin.ignore();
	string playlistName;
	Playlist* playlist = nullptr;
	do {
		cout << "Enter the name of the playlist: ";
		cin >> playlistName;

		playlist = manager.getPlaylist(playlistName);
		if (!playlist) {
			cout << "\033[31mError: Playlist '" << playlistName << "' not found. Please try again.\033[0m\n";
		}
	} while (!playlist);
	string name, type, path;
	cin.ignore();
	cout << "Enter Surah name: ";
	getline(cin, name);
	cout << "Enter surah type (Makkah/Madinah): ";
	getline(cin, type);
	cout << "Enter Surah audio file path: ";
	getline(cin, path);

	Surah surah(name, type, path);
	manager.addSurahToPlaylist(playlistName, surah);
	cout << "\033[32mSurah added to playlist successfully ^---^.\033[0m\n";
	char addMore;
	while (true)
	{
		cout << "Add another surah to the current playlist? Press (y/n): ";
		cin >> addMore;
		cin.ignore();

		if (addMore == 'y' || addMore == 'Y')
		{
			cout << "Enter surah name: ";
			getline(cin, name);
			cout << "Enter surah type (e.g., Makkah/Madinah): ";
			getline(cin, type);
			cout << "Enter surah path: ";
			getline(cin, path);
			Surah surah(name, type, path);

			manager.addSurahToPlaylist(playlistName, surah);
			cout << "\033[32mSurah added to playlist successfully.\033[0m\n";
		}
		else if (addMore == 'n' || addMore == 'N')
		{
			break;
		}
		else
		{
			cout << "\033[31mInvalid choice, Please try again.\033[0m\n";
		}
	}

}

void handleRemoveSurahFromPlaylist(PlaylistManager& manager) {
	cin.ignore();
	string playlistName, surahName;

	Playlist* playlist = nullptr;
	bool surahFound = false;

	do {
		cout << "Enter playlist name: ";
		getline(cin, playlistName);

		playlist = manager.getPlaylist(playlistName);
		if (!playlist) {
			cout << "\033[31mError: Playlist '" << playlistName << "' not found. Please try again.\033[0m\n";
		}
	} while (!playlist);

	do {
		cout << "Enter Surah name to remove: ";
		getline(cin, surahName);
		auto* currentSurahNode = playlist->getSurahList().getHead();
		surahFound = false;

		while (currentSurahNode) {
			if (currentSurahNode->data.getName() == surahName) {
				surahFound = true;
				break;
			}
			currentSurahNode = currentSurahNode->next;
		}

		if (!surahFound) {
			cout << "\033[31mError: Surah '" << surahName << "' not found in playlist '" << playlistName << "'. Please try again.\033[0m\n";
		}
	} while (!surahFound);

	manager.removeSurahFromPlaylist(playlistName, surahName);
	cout << "\033[32mSurah '" << surahName << "' removed successfully from playlist '" << playlistName << "'.\033[0m\n";
}

void handleUpdatePlaylistOrder(PlaylistManager& manager) {
	cin.ignore();
	string playlistName;
	int oldPos, newPos;
	Playlist* playlist = manager.getPlaylist(playlistName);
	do {
		cout << "Enter playlist name: ";
		getline(cin, playlistName);

		playlist = manager.getPlaylist(playlistName);
		if (!playlist) {
			cout << "\033[31mError: Playlist '" << playlistName << "' not found. Please try again.\033[0m\n";
		}
	} while (!playlist);
	cout << "Enter old position of Surah: ";
	cin >> oldPos;
	cout << "Enter new position of Surah: ";
	cin >> newPos;
	oldPos--;
	newPos--;
	playlist->updateSurahOrder(oldPos, newPos);
	cout << "Surah order updated successfully.\n";

}

void handleDisplayAllPlaylists(PlaylistManager& manager) {
	manager.displayAllPlaylists();
}

void handleDisplayAllSurahs(PlaylistManager& manager) {
	manager.displayAllSurahs();
}

void handleDisplaySurahsInPlaylist(PlaylistManager& manager) {
	cin.ignore();
	string playlistName;
	cout << "Enter playlist name: ";
	getline(cin, playlistName);

	Playlist* playlist = manager.getPlaylist(playlistName);
	if (playlist) {
		playlist->displaySurahs();
	}
	else {
		cout << "Playlist not found.\n";
	}
}

void handlePlaySurah(PlaylistManager& manager) {
	AudioPlayer player;

	manager.displayAllPlaylists();
	cout << endl;
	cout << "   Use left arrow (<-) to play the previous surah\n";
	cout << "   Use right arrow (->) to play the next surah \n";
	cout << "   Use up arrow (^) to pause the current surah\n";
	cout << "   Use down arrow (V) to resume the paused surah \n";
	cout << "   Press q to exit current playlist & return back to menu\n";

	string playlistToPlay;

	Playlist* playlist = nullptr;
	do {
		cout << "Enter the name of the playlist to play: ";
		cin >> playlistToPlay;

		playlist = manager.getPlaylist(playlistToPlay);
		if (!playlist) {
			cout << "\033[31mError: Playlist '" << playlistToPlay << "' not found. Please try again.\033[0m\n";
		}
	} while (!playlist);

	player.playPlaylist(playlistToPlay, manager);

	while (true) {
		int key = _getch();
		if (key == 224)
		{
			key = _getch();
			switch (key) {
			case 75:
				player.Previous();
				break;
			case 77:
				player.next();
				break;
			case 72:
				player.pause();
				break;
			case 80:
				player.resume();
				break;
			}
		}
		else if (key == 'q')
		{
			cout << "Exiting playback." << endl;
			system("cls");
			return;
		}
	}
}

void handleSavePlaylists(PlaylistManager& manager) {
	cin.ignore();
	string fileName;
	cout << "Enter file name to save playlists: ";
	getline(cin, fileName);

	manager.save(fileName);
}

void handleLoadPlaylists(PlaylistManager& manager) {
	cin.ignore();
	string fileName;
	cout << "Enter file name to load playlists: ";
	getline(cin, fileName);

	manager.load(fileName);
}

void handleRemovePlaylist(PlaylistManager& manager) {
	cin.ignore();
	string playlistName;
	cout << "Enter playlist name to remove: ";
	getline(cin, playlistName);

	manager.removePlaylist(playlistName);
}

int main() {
	PlaylistManager manager;
	int choice;

	do {
		displayMenu();
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1: handleAddPlaylist(manager); break;
		case 2: handleAddSurahToPlaylist(manager); break;
		case 3: handleRemoveSurahFromPlaylist(manager); break;
		case 4: handleUpdatePlaylistOrder(manager); break;
		case 5: handleDisplayAllPlaylists(manager); break;
		case 6: handleDisplayAllSurahs(manager); break;
		case 7: handleDisplaySurahsInPlaylist(manager); break;
		case 8: handlePlaySurah(manager); break;
		case 9: handleSavePlaylists(manager); break;
		case 10: handleLoadPlaylists(manager); break;
		case 11: handleRemovePlaylist(manager); break;
		case 0: cout << "\033[35mExiting Quran Playlist Manager. Goodbye!\033[0m\n"; break;

		default:
			cout << "\033[31mInvalid choice, Please try again.\033[0m\n";
			break;
		}
	} while (choice != 0);
	return 0;
}