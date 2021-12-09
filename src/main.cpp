#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	// Do not question why, but Qt is weird.. (exec is a static member)
	return a.exec(); // NOLINT(readability-static-accessed-through-instance)
}