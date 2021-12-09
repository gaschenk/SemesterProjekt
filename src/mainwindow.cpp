#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "caesar/caesar.h"
MainWindow::MainWindow(QWidget* parent)
		:QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->inputEdit, SIGNAL(textChanged(QString)), this, SLOT(updateCaesarField()));
	connect(ui->shiftSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCaesarField()));
	connect(ui->bruteForceEdit, SIGNAL(textChanged(QString)), this, SLOT(updateResultWindow()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updateResultWindow()
{
	ui->outputWindow->clear();
	std::string caesar = ui->bruteForceEdit->text().toStdString();
	int bestSolution = -1;
	int bestValue = 0;
	for (int i = 0; i<=26; ++i) {
		std::stringstream stringstream;
		std::string decoded = *(caesar::decode(caesar, i));
		int value = caesar::rateSolution(decoded);
		if (value<0)
			ui->outputWindow->setTextColor(QColor("red"));
		else
			ui->outputWindow->setTextColor(QColor("green"));
		stringstream << decoded << " is rated " << value;
		ui->outputWindow->append(QString::fromStdString(stringstream.str()));
		if (bestValue<value) {
			bestValue = value;
			bestSolution = i;
		}
	}

	std::stringstream resultStream;
	if (bestSolution>=0) {
		ui->outputWindow->setTextColor(QColor("red"));
		resultStream << "\nThe best solution is " << *(caesar::decode(caesar, bestSolution)) << " (rot"
					 << bestSolution << ")" << " and a score of "
					 << bestValue;
	}
	else {
		ui->outputWindow->setTextColor(QColor("green"));
		resultStream << "We didn't find a proper solution.";
	}
	ui->outputWindow->append(QString::fromStdString(resultStream.str()));
}
void MainWindow::updateCaesarField()
{
	ui->outputEdit->setText(
			QString::fromStdString(*(caesar::encode(ui->inputEdit->text().toStdString(), ui->shiftSpinBox->value()))));
	if (!ui->outputEdit->text().isEmpty()) {
		int value = caesar::rateSolution(ui->outputEdit->text().toStdString());
		std::cout << "Total value: " << value << std::endl;
	}
}