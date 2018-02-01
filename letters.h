#ifndef LETTERS
#define LETTERS

#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

class Letters
{
public:
    std::map<std::string, int> mLetters;
    std::string fileName;
    void readLetters();
    Letters(char *fileName);
    std::string getChar(int ch);
};
#endif // LETTERS_H
