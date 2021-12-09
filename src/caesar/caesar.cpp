//
// Created by Rai on 09.11.2021.
//

#include "caesar.h"
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>

std::shared_ptr<std::string> caesar::decode(const std::string& string, int shift)
{
    return caesar::encode(string, 26-shift);
}

std::shared_ptr<std::string> caesar::encode(const std::string& string, int shift)
{
	auto output = std::make_shared<std::string>(string);
	for (char& i : *output) {
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
	std::cout << *output << "|" << string << std::endl;
	return output;
}

int caesar::rateSolutionAccordingToTypicalCharacterSequence(const std::string& string)
{
	int value = 0;
	bool q = false;
	for (auto c : string) {
		if (q && c=='u')
			value += 25;
		else if (q)
			value -= 100;
		q = false;

		if (c=='q' || c=='Q')
			q = true;
	}
	std::cout << "Value of Qu: " << value << std::endl;
	return value;
}

int caesar::rateSolutionAccordingToVocals(const std::string& string)
{
	bool endOfWord = false;
	bool hasVocal = false;
	int value = 0;
	static const std::vector vocals = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
	for (auto c : string) {
		if (hasVocal && endOfWord) {
			value += 50;
			endOfWord = false;
			hasVocal = false;
		}
		else if (endOfWord) {
			value -= 75;
			endOfWord = false;
		}

		// Every non ascii character == End of Word.
		if (!isascii(c) || !isalpha(c)) {
			endOfWord = true;
		}
		else if (isascii(c) && isalpha(c)) {
			if (std::find(vocals.begin(), vocals.end(), c)!=vocals.end())
				hasVocal = true;
		}
	}
	// End of String check
	if (hasVocal)
		value += 50;
	else
		value -= 75;

	std::cout << "Value of vocals: " << value << std::endl;
	return value;
}

// https://sourceforge.net/projects/germandict/ <- Great Dictionary
int caesar::rateSolutionAccordingToWordList(const std::string& string)
{
	int value = 0;
	bool endOfWord = false;
	int start = 0, end = 0;
	for (auto c : string) {

		if (endOfWord) {
			value += getValueOfWord(string, start, end-1);
			start = end;
			endOfWord = false;
		}

		// Every non ascii character == End of Word.
		if (!isascii(c) || !isalpha(c)) {
			endOfWord = true;
		}
		end++;
	}
	// End of String scope check
	{
		value += getValueOfWord(string, start, end);
	}
	return value;
}
// Stringview potentiell besser.
int caesar::getValueOfWord(const std::string& string, int start, int end)
{
	int value = 0;
	std::string word = string.substr(start, end-start);
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	if (std::find(wordList.begin(), wordList.end(), word)!=wordList.end())
		value += 50;
	else
		value -= 50;
	std::cout << "Value of " << word << " " << value << std::endl;
	return value;
}

int caesar::rateSolution(const std::string& string)
{
	return caesar::rateSolutionAccordingToVocals(string)+caesar::rateSolutionAccordingToWordList(string)
			+caesar::rateSolutionAccordingToTypicalCharacterSequence(string);
}
