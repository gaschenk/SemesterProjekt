//
// Created by Rai on 09.11.2021.
//

#pragma once
#include <string>
#include <iostream>
namespace caesar {

    std::shared_ptr<std::string> decode(const std::string &string, int shift);
    std::shared_ptr<std::string> encode(const std::string &string, int shift);/*
    int rateSolution(const std::string &string, dictionary &dictionary);
    int rateSolutionAccordingToWordList(const std::string &string, dictionary &dictionary);*/
    int rateSolutionAccordingToVocals(const std::string &string);
    int rateSolutionAccordingToTypicalCharacterSequence(const std::string &string);

}// namespace caesar
