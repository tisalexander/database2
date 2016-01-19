#include "database.h"

#include <QtCore/QStringList>
#include <QtSql/QSqlQuery>

/*------- Database ----------------------------------------------------------*/
Database::Database(QObject *parent)
	: QObject(parent)
{
}

Database::~Database()
{
}

bool Database::create(const QString &filepath)
{
	if (m_db.isOpen()) {
		m_db.close();
	}

	m_db.addDatabase("QSQLITE");
	m_db.setDatabaseName(filepath);

	if (!m_db.open()) {
		return false;
	}

	init();

	return true;
}

bool Database::open(const QString &filepath)
{
	if (m_db.isOpen()) {
		m_db.close();
	}

	m_db.addDatabase("QSQLITE");
	m_db.setDatabaseName(filepath);

	if (!m_db.open()) {
		return false;
	}

	init();

	return true;
}

QStringList Database::tables() const
{
	if (m_db.isOpen()) {
		return m_db.tables();
	}

	return QStringList();
}

void Database::init()
{
	if (!m_db.isOpen()) {
		return;
	}

	QSqlQuery query("CREATE TABLE IF NOT EXISTS 'Indexes'"
					"(FFID int)",
					m_db);
}
