#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <iostream>
#include "Surah.h"
#include "DoublyLinkedList.h" 
using namespace std;

class Playlist {
private:
	string name;
	DoublyLinkedList<Surah> surahs;
public:
	Playlist(const string& name);
	string getName();
	DoublyLinkedList<Surah>& getSurahList();

	void printLine() const;

	void addSurah(const Surah& surah);

	void removeSurah(const string& surahName);

	void updateSurahOrder(int oldPos, int newPos);

	void searchByType(const string& type) const;

	void sortSurahs();

	void reverseSurahs();

	void displaySurahs() const;

	DoublyLinkedList<Surah>& getSurahs();

	bool operator==(const Playlist& other) const;

};

#endif // PLAYLIST_H
