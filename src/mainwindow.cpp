#include "mainwindow.h"

#include <QtGui/QFileDialog>
#include <QtGui/QMenuBar>
#include <QtGui/QMessageBox>

/*------- MainWindow::PrivateData -------------------------------------------*/
class MainWindow::PrivateData
{
public:
	QAction *actionCreateDatabase;
	QAction *actionOpenDatabase;
};

/*------- MainWindow --------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	m_pD = new PrivateData();

	ui = new Ui::Form();
	ui->setupUi(this);

	createActions();
	createMenus();
	connect();

	setWindowTitle(tr("Database"));
	showMaximized();
}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_pD;
}

void MainWindow::onCreateDatabase()
{
	QString filepath = QFileDialog::getSaveFileName(this, tr("Create Database"));

	if (!m_database.create(filepath)) {
		QMessageBox::warning(this,
							 tr("Error"),
							 tr("Database is not created."));
		return;
	}

	updateTableList();
}

void MainWindow::onOpenDatabase()
{
	QString filepath = QFileDialog::getOpenFileName(this, tr("Open Database"));

	if (!m_database.open(filepath)) {
		QMessageBox::warning(this,
							 tr("Error"),
							 tr("Database is not opened."));
		return;
	}

	updateTableList();
}

void MainWindow::updateTableList()
{
	ui->tableList->clear();
	ui->tableList->addItems(m_database.tables());
}

void MainWindow::updateTableContent(int index)
{
	if (index == -1) {
		return;
	}

	QString table = ui->tableList->item(index)->text();

	ui->tableContent->clear();
	ui->tableContent->setColumnCount(m_database.fieldCount());
	ui->tableContent->setHorizontalHeaderLabels(m_database.header());

	int rowCount = m_database.rowCount();
	ui->tableContent->setRowCount(rowCount);

	QStringList values;
	int valuesCount = 0;
	for (int i = 0; i < rowCount; i++) {
		values = m_database.record(i);
		valuesCount = values.size();
		for (int j = 0; j < valuesCount; j++) {
			QTableWidgetItem *item = new QTableWidgetItem(values[j]);
			ui->tableContent->setItem(i, j, item);
		}
	}
}

void MainWindow::createActions()
{
	m_pD->actionCreateDatabase = new QAction(tr("Create database..."), this);
	m_pD->actionOpenDatabase = new QAction(tr("Open database..."), this);
}

void MainWindow::createMenus()
{
	QMenuBar *menuBar = QMainWindow::menuBar();

	QMenu *databaseMenu = menuBar->addMenu(tr("Database"));
	databaseMenu->addAction(m_pD->actionCreateDatabase);
	databaseMenu->addAction(m_pD->actionOpenDatabase);
}

void MainWindow::connect()
{
	QObject::connect(m_pD->actionCreateDatabase, SIGNAL(triggered(bool)),
					 SLOT(onCreateDatabase()));

	QObject::connect(m_pD->actionOpenDatabase, SIGNAL(triggered(bool)),
					 SLOT(onOpenDatabase()));

	QObject::connect(ui->tableList, SIGNAL(currentRowChanged(int)),
					 SLOT(updateTableContent(int)));
}
