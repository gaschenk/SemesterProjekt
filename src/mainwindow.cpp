#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "caesar/caesar.h"
MainWindow::MainWindow(QWidget* parent)
		:QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	/*connect(ui->inputEdit, SIGNAL(textChanged(QString)), this, SLOT(updateCaesarField()));
	connect(ui->shiftSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCaesarField()));*/
	connect(ui->encodeButton, SIGNAL(clicked()), this, SLOT(updateCaesarField()));
	connect(ui->bruteForceButton, SIGNAL(clicked()), this, SLOT(updateResultWindow()));
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
	std::vector<std::tuple<std::string, QColor>> strings(26);
	std::vector<std::shared_future<void>> asyncIterationThreads;
	for (int i = 0; i<=25; ++i) {
		asyncIterationThreads
				.emplace_back(std::async(std::launch::async, [i, &strings, &bestSolution, &bestValue, &caesar] {
					std::stringstream stringstream;
					std::string decoded = *(caesar::decode(caesar, i));
					int value = caesar::rateSolution(decoded);
					auto color = QColorConstants::Blue;
					if (value<0)
						color = QColorConstants::Red;
					stringstream << decoded << " is rated " << value;

					strings[i] = std::make_tuple(stringstream.str(), color);
					if (bestValue<value) {
						bestValue = value;
						bestSolution = i;
					}
				}).share());
	}
	for (const auto& future : asyncIterationThreads)
		future.wait();

	for (auto[line, color] : strings) {
		ui->outputWindow->setTextColor(color);
		ui->outputWindow->append(QString::fromStdString(line));
	}

	std::stringstream resultStream;
	QColor color = QColorConstants::Black;
	std::thread resultThread{ [&bestSolution, &bestValue, &resultStream, &color, &caesar] {
		if (bestSolution>=0) {
			color = QColorConstants::Blue;
			resultStream << "\nThe best solution is " << *(caesar::decode(caesar, bestSolution)) << " (rot"
						 << bestSolution << ")" << " and a score of "
						 << bestValue;
		}
		else {
			color = QColorConstants::Red;
			resultStream << "We didn't find a proper solution.";
		}
	}};

	resultThread.join();
	ui->outputWindow->setTextColor(color);
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