#include "database.h"

#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

/*------- Database ----------------------------------------------------------*/
Database::Database(QObject *parent)
	: QObject(parent), m_tableName("Indexes")
{
	m_queryExecuted = false;
}

Database::~Database()
{
}

bool Database::create(const QString &filepath)
{
	if (m_db.isOpen()) {
		m_db.close();
	}

	m_db = QSqlDatabase::addDatabase("QSQLITE");
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

	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName(filepath);

	if (!m_db.open()) {
		return false;
	}

	init();

	return true;
}

void Database::fill()
{
	if (!m_db.isOpen()) {
		return;
	}

	m_db.transaction();

	QSqlQuery query(m_db);
	for (int ffid = 1; ffid <= 100; ffid++) {
		for (int ch = 1; ch <= 100; ch++) {
			query.exec(QString("INSERT INTO 'Indexes' VALUES (%1,%2,%3,%4)")
					   .arg(ffid)
					   .arg(ch)
					   .arg(123456.01)
					   .arg(123456.01));
		}
	}

	m_db.commit();

	m_queryExecuted = false;
}

QStringList Database::tables() const
{
	if (m_db.isOpen()) {
		return m_db.tables();
	}

	return QStringList();
}

int Database::rowCount() const
{
	if (!m_db.isOpen()) {
		return -1;
	}

	if (!m_queryExecuted) {
		QSqlQuery query(QString("SELECT * FROM '%1'").arg(m_tableName),
						m_db);
		m_query = query;
		m_queryExecuted = true;
	}

	QSqlQuery query(QString("SELECT COUNT(*) FROM '%1'").arg(m_tableName),
					m_db);
	query.next();

	return query.record().value(0).toInt();
}

QStringList Database::record(int index) const
{
	if (!m_db.isOpen()) {
		return QStringList();
	}

	if (!m_queryExecuted) {
		QSqlQuery query(QString("SELECT * FROM '%1'").arg(m_tableName),
						m_db);
		m_query = query;
		m_queryExecuted = true;
	}

	m_query.seek(index);
	QSqlRecord record = m_query.record();

	int count = record.count();

	QStringList values;
	for (int i = 0; i < count; i++) {
		values.append(record.value(i).toString());
	}

	return values;
}

int Database::fieldCount() const
{
	if (!m_db.isOpen()) {
		return 0;
	}

	QSqlQuery query(QString("SELECT * FROM '%1'").arg(m_tableName));

	return query.record().count();
}

QStringList Database::header() const
{
	if (!m_db.isOpen()) {
		return QStringList();
	}

	QSqlQuery query(QString("SELECT * FROM '%1'").arg(m_tableName));

	QSqlRecord record = query.record();
	int count = record.count();

	QStringList header;
	for (int i = 0; i < count; i++) {
		header.append(record.fieldName(i));
	}

	return header;
}

void Database::init()
{
	if (!m_db.isOpen()) {
		return;
	}

	QSqlQuery query("CREATE TABLE IF NOT EXISTS '" + m_tableName +
					"'(FFID int NOT NULL,"
					"CH int NOT NULL,"
					"XSHOT double NOT NULL,"
					"YSHOT double NOT NULL)",
					m_db);

	fill();
}
