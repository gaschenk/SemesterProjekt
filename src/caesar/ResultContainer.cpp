//
// Created by Rai on 15.12.2021.
//

#include "ResultContainer.h"
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
void ResultContainer::updateResultTextArea(const std::shared_ptr<std::string>& string, int rot, QTextEdit* textedit)
{
	if (textedit==nullptr)
		std::cout << "Textedit: nullptr" << std::endl;
	if (string==nullptr)
		std::cout << "string: nullptr" << std::endl;
	if (rot>26) return;
	std::string decoded = *(caesar::decode(*string, rot));
	Result result = caesar::rateSolution(decoded);

	auto color = QColorConstants::Blue;
	if (result.TotalRating<0)
		color = QColorConstants::Red;

	std::stringstream stringStream;
	stringStream << decoded << " is rated " << result.TotalRating << "[WR: " << result.WordRating
				 << "; VR:" << result.VocalRating << "; CSR:" << result.CharacterSequenceRating << "]";

	textedit->setTextColor(color);
	textedit->append(QString::fromStdString(stringStream.str()));

	if (bestValue<result.TotalRating) {
		bestValue = result.TotalRating;
		bestSolution = rot;
	}
	resultList[rot] = result;
	try {
		std::lock_guard<std::mutex> guard(counterMutex);
		counter++;
		if (counter>=26) {
			emit
			this->resultsProcessed();
		}
	}
	catch (std::logic_error&) {
		std::cerr << "Exception caught\n";
	}
}
