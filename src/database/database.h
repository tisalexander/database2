#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

/*------- Database ----------------------------------------------------------*/
class Database : public QObject
{
	Q_OBJECT

public:
	Database(QObject *parent = 0);
	~Database();

	bool create(const QString &filepath = QString());
	bool open(const QString &filepath = QString());
	void fill();

	int fieldCount() const;
	QStringList header() const;
	QStringList tables() const;

	int rowCount() const;
	QStringList record(int index) const;

private:
	const QString m_tableName;
	QSqlDatabase m_db;

	mutable QSqlQuery m_query;
	mutable bool m_queryExecuted;

	void init();
};

#endif // DATABASE_DATABASE_H
