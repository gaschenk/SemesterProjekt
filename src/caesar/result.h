//
// Created by Rai on 14.12.2021.
//

#pragma once

struct Result {
	int WordRating{ 0 };
	int VocalRating{ 0 };
	int CharacterSequenceRating{ 0 };
	int TotalRating = WordRating+VocalRating+CharacterSequenceRating;

};
