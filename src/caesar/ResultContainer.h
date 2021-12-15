//
// Created by Rai on 15.12.2021.
//
#pragma once
#include <QObject>
#include <QTextEdit>
#include <QLineEdit>
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
			int rot, QTextEdit
	* textedit);
	void setBaseString(std::string string);
signals:
	void singleResultProcessed(QColor color, std::string string);
	void resultsProcessed();
private:
	std::string baseString;
	int bestValue = 0;
	int bestSolution = -1;
	int counter = 0;
	std::vector<Result> resultList;
	std::mutex counterMutex;
};

