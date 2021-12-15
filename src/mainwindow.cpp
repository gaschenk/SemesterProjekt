#include "mainwindow.h"
#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent)
		:QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	/*
	 * This would update on input changed, but this is rather bad in terms of performance especially with larger texts.
	 * connect(ui->inputEdit, SIGNAL(textChanged(QString)), this, SLOT(updateCaesarField()));
	 * connect(ui->shiftSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCaesarField()));
	*/
	connect(ui->encodeButton, SIGNAL(clicked()), this, SLOT(updateCaesarField()));
	connect(ui->bruteForceButton, SIGNAL(clicked()), this, SLOT(updateResultWindow()));
	connect(&this->resultContainer, SIGNAL(resultsProcessed()), this, SLOT(finalUpdateResults()));
	connect(&this->resultContainer, SIGNAL(singleResultProcessed(QColor, std::string)), this,
			SLOT(updateSingleResult(QColor, std::string)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updateResultWindow()
{
	resultContainer.reset();
	resultContainer.setBaseString(ui->bruteForceEdit->text().toStdString());
	ui->outputWindow->clear();
	for (int i = 0; i<=25; ++i) {
		std::thread iterationThread{ [this, i] {
			resultContainer.updateResultTextArea(i, ui->outputWindow);
		}};
		iterationThread.detach();
	}
}
void MainWindow::finalUpdateResults()
{
	std::string caesar = ui->bruteForceEdit->text().toStdString();
	int bestSolution = resultContainer.getBestSolution();
	auto results = resultContainer.getResults();

	std::stringstream resultStream;
	QColor color;
	if (bestSolution>=0) {
		color = QColorConstants::Blue;
		resultStream << "\nThe best solution is " << *(caesar::decode(caesar, bestSolution)) << " (rot"
					 << bestSolution << ")" << " and a total score of "
					 << results[bestSolution].TotalRating;
	}
	else {
		color = QColorConstants::Red;
		resultStream << "We didn't find a proper solution.";
	}
	ui->outputWindow->setTextColor(color);
	ui->outputWindow->append(QString::fromStdString(resultStream.str()));
}
void MainWindow::updateCaesarField()
{
	mutex.lock();
	ui->outputEdit->setText(
			QString::fromStdString(*(caesar::encode(ui->inputEdit->text().toStdString(), ui->shiftSpinBox->value()))));
	if (!ui->outputEdit->text().isEmpty()) {
		Result result = caesar::rateSolution(ui->outputEdit->text().toStdString());
		std::cout << "Total value: " << result.TotalRating << std::endl;
	}
	mutex.unlock();
}
void MainWindow::updateSingleResult(QColor color, std::string string)
{
	mutex.lock();
	ui->outputWindow->setTextColor(color);
	ui->outputWindow->append(QString::fromStdString(string));
	mutex.unlock();
}
