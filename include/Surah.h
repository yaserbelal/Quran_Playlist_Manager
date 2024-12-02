#ifndef SURAH_H
#define SURAH_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Surah {
private:
    int number;
    string name;
    string type;
    string path;

public:
    // Constructor
    Surah(const int &number, const string& name, const string& type, const string& path);
    Surah(const string& name, const string& type, const string& path);

    int getNumber() const;
    string getName() const;
    string getType() const;
    string getPath() const;

    void setNumber(int number);
    void setName(const string& name);
    void setType(const string& type);
    void setPath(const string& path);

    void display() const;
    bool operator<(const Surah& other) const;
    bool operator==(const Surah& other) const;

};

#endif // SURAH_H
