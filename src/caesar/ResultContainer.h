//
// Created by Rai on 15.12.2021.
//
#pragma once
#include <QObject>
#include <QTextEdit>
#include <mutex>
#include "result.h"
#include "caesar.h"

class ResultContainer : public QObject {
	Q_OBJECT
public:
	ResultContainer();
	std::vector<Result> getResults();
	[[nodiscard]] int getBestSolution() const;
	void reset();
	void updateResultTextArea(
			const std::shared_ptr<std::string>&
			string,
			int rot, QTextEdit
	* textedit);
	signals:
			void resultsProcessed();
private:
	int bestValue = 0;
	int bestSolution = -1;
	int counter = 0;
	std::vector<Result> resultList;
	std::mutex counterMutex;
};

