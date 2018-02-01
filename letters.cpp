#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include "letters.h"

void Letters::readLetters()
{
    std::ifstream file(fileName);
    if(!file.is_open()) {
        std::cout<<"Could not open letters file: "<<fileName<<std::endl;
        return;
    }

    std::string inString;
    int i = 1;
    while (std::getline(file, inString)) {
        mLetters[inString] = i;
        i++;
    }
}

Letters::Letters(char *fileName)
{
    this->fileName = fileName;
    readLetters();
}
