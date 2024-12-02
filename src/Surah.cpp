#include "Surah.h"

Surah::Surah(const int &number, const string& name, const string& type, const string& path)
	:number(number),name(name), type(type), path(path){}
Surah::Surah(const string& name, const string& type, const string& path)
	:name(name), type(type), path(path) {}

int Surah::getNumber() const {
	return number;
}

string Surah::getName() const {
	return name;
}

string Surah::getType() const {
	return type;
}

string Surah::getPath() const {
	return path;
}

void Surah::setNumber(int number) {
	this->number = number;
}

void Surah::setName(const string& name) {
	this->name = name;
}

void Surah::setType(const string& type) {
	this->type = type;
}

void Surah::setPath(const string& path) {
	this->path = path;
}

void Surah::display() const {
	cout << setw(20) << name
		 << setw(15) << type
		 << setw(20) << path << "\n";
}

bool Surah::operator<(const Surah& other) const
{
	return number < other.number;
}

bool Surah::operator==(const Surah& other) const
{
	return name == other.name;
}