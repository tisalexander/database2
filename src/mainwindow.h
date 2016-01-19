#ifndef DATABASE_MAINWINDOW_H
#define DATABASE_MAINWINDOW_H

#include "database/database.h"
#include "ui_mainform.h"
#include <QtGui/QMainWindow>

namespace Ui
{
	class Form;
}

/*------- MainWindow --------------------------------------------------------*/
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~MainWindow();

private slots:
	void onCreateDatabase();
	void onOpenDatabase();

	void updateTableList();
	void updateTableContent(int index);

private:
	class PrivateData;
	PrivateData *m_pD;
	Ui::Form *ui;
	Database m_database;

	void createActions();
	void createMenus();
	void connect();
};

#endif // DATABASE_MAINWINDOW_H
