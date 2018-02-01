#ifndef LETTERS
#define LETTERS
class Letters
{
public:
    std::map<std::string, int> mLetters;
    std::string fileName;
    void readLetters();
    Letters(char *fileName);
};
#endif // LETTERS_H
