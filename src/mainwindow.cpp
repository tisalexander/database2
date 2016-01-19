#include "mainwindow.h"

#include <QtGui/QFileDialog>
#include <QtGui/QMenuBar>

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
	m_database.create(filepath);
	updateTableList();
}

void MainWindow::onOpenDatabase()
{
	QString filepath = QFileDialog::getOpenFileName(this, tr("Open Database"));
	m_database.open(filepath);
	updateTableList();
}

void MainWindow::updateTableList()
{
	ui->tableList->clear();
	ui->tableList->addItems(m_database.tables());
}

void MainWindow::updateTableContent(int index)
{
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
}
