#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "caesar/caesar.h"
MainWindow::MainWindow(QWidget* parent)
		:QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->inputEdit, SIGNAL(textChanged(QString)), this, SLOT(updateCaesarField()));
	connect(ui->shiftSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCaesarField()));
}

MainWindow::~MainWindow()
{
	delete ui;
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