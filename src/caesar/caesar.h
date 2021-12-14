//
// Created by Rai on 09.11.2021.
//

#pragma once
#include <string>
#include <iostream>
#include "result.h"
namespace caesar {

	std::shared_ptr<std::string> decode(const std::string& string, int shift);
	std::shared_ptr<std::string> encode(const std::string& string, int shift);
	Result rateSolution(const std::string& string);
	int rateSolutionAccordingToWordList(const std::string& string);
	int rateSolutionAccordingToVocals(const std::string& string);
	int rateSolutionAccordingToTypicalCharacterSequence(const std::string& string);

	void loadDictionary();
	int getValueOfWord(const std::string& string, int start, int end);
}// namespace caesar
