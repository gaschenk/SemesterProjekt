#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>
#include <QMainWindow>
#include <QMutex>
#include "caesar/caesar.h"
#include "caesar/ResultContainer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	QMutex mutex;
	ResultContainer resultContainer;
	Ui::MainWindow* ui;
private
	slots:
	void updateCaesarField();
	void updateResultWindow();
	void finalUpdateResults();
	void updateSingleResult(QColor color, std::string string);
};
#endif// MAINWINDOW_H
