//
// Created by Rai on 15.12.2021.
//

#include "ResultContainer.h"
#include <QMutex>
QMutex mutex;
ResultContainer::ResultContainer()
{
	resultList.resize(26);
}
std::vector<Result> ResultContainer::getResults()
{
	return resultList;
}
int ResultContainer::getBestSolution() const
{
	return bestSolution;
}
void ResultContainer::reset()
{
	resultList.clear();
	resultList.resize(26);
	counter = 0;
	bestValue = 0;
	bestSolution = -1;
}
void ResultContainer::updateResultTextArea(int rot, QTextEdit* textedit)
{
	if (rot>26) return;
	std::string decoded = *(caesar::decode(baseString, rot));
	Result result = caesar::rateSolution(decoded);

	auto color = QColorConstants::Blue;
	if (result.TotalRating<0)
		color = QColorConstants::Red;

	std::stringstream stringStream;
	stringStream << decoded << " is rated " << result.TotalRating << "[WR: " << result.WordRating
				 << "; VR:" << result.VocalRating << "; CSR:" << result.CharacterSequenceRating << "]";

	try {
		mutex.lock();
		if (bestValue<result.TotalRating) {
			bestValue = result.TotalRating;
			bestSolution = rot;
		}
		emit this->singleResultProcessed(color, stringStream.str());
		resultList[rot] = result;
		counter++;
		mutex.unlock();
		if (counter>=26) {
			emit
			this->resultsProcessed();
		}
	}
	catch (std::logic_error&) {
		std::cerr << "Exception caught\n";
	}
}
void ResultContainer::setBaseString(std::string string)
{

	this->baseString = string;
}
