//
// Created by Rai on 09.11.2021.
//

#include "caesar.h"
#include <memory>

std::shared_ptr<std::string> caesar::decode(const std::string& string, int shift)
{
    return caesar::encode(string, 26-shift);
}

std::shared_ptr<std::string> caesar::encode(const std::string& string, int shift)
{
    auto output = std::make_shared<std::string>(string);
    for (char& i: *output) {
        if (!isalpha(i) && !isascii(i)) {
            continue;
        }
        else if (isupper(i)) {
            i = ((i-'A'+shift)%26)+'A';
        }
        else if (islower(i)) {
            i = ((i-'a'+shift)%26)+'a';
        }
    }
    std::cout << string << "|" << output << std::endl;
    return output;
}

int caesar::rateSolutionAccordingToTypicalCharacterSequence(const std::string& string)
{
    auto test = std::find(string.begin(), string.end(), 'Q');
    return 0;
}
/*int caesar::rateSolutionAccordingToVocals(const std::string &string) {
    return 0;
}
int caesar::rateSolutionAccordingToWordList(const std::string &string, dictionary &dictionary) {
    return 0;
}
int caesar::rateSolution(const std::string &string, dictionary &dictionary) {
    return caesar::rateSolutionAccordingToVocals(string) + caesar::rateSolutionAccordingToWordList(string, dictionary) + caesar::rateSolutionAccordingToTypicalCharacterSequence(string);
}*/
