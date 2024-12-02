#include "Playlist.h"
#include <iostream>

Playlist::Playlist(const  string& name) : name(name) {}

string Playlist::getName()
{
	return name;
}

DoublyLinkedList<Surah>& Playlist::getSurahList()
{
	return surahs;
}

void Playlist::printLine() const
{
	cout << "--------------------------------------------------------------------\n";

}

void Playlist::addSurah(const Surah& surah) {
	surahs.add(surah);  
}

void Playlist::removeSurah(const string& surahName) {
	typename DoublyLinkedList<Surah>::Node* current = surahs.getHead();  
	while (current) {
		if (current->data.getName() == surahName) {
			surahs.remove(current->data);
			return;
		}
		current = current->next;
	}
}

void Playlist::updateSurahOrder(int oldPos, int newPos) {
	typename DoublyLinkedList<Surah>::Node* current = surahs.getHead();  
	int index = 0;

	while (current && index != oldPos) {
		current = current->next;
		index++;
	}

	if (current) {
		Surah surahToMove = current->data;
		surahs.remove(surahToMove);
		index = 0;
		current = surahs.getHead();
		while (current && index != newPos) {
			current = current->next;
			index++;
		}

		surahs.add(surahToMove);
	}
}

void Playlist::searchByType(const string& type) const {
	const typename DoublyLinkedList<Surah>::Node* current = surahs.getHead(); 
	while (current) {
		if (current->data.getType() == type) {
			current->data.display();
		}
		current = current->next;
	}
}

void Playlist::sortSurahs() {
	surahs.sort();  
}

void Playlist::reverseSurahs() {
	surahs.reverse(); 
}

void Playlist::displaySurahs() const {
	const typename DoublyLinkedList<Surah>::Node* current = surahs.getHead();  // Const pointer here
	printLine();
	cout << left << setw(10) << "ID"
		<< setw(20) << "Surah"
		<< setw(15) << "Type"
		<< setw(20) << "Path" << "\n";
	printLine();
	int i = 1;
	while (current) {
		cout << left << setw(10) << i;
		current->data.display();
		current = current->next;
		i++;
	}
}

DoublyLinkedList<Surah>& Playlist::getSurahs()
{
	return surahs;
}

bool Playlist::operator==(const Playlist& other) const
{
	return name == other.name; 
}

