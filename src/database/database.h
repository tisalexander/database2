#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>

/*------- Database ----------------------------------------------------------*/
class Database : public QObject
{
	Q_OBJECT

public:
	Database(QObject *parent = 0);
	~Database();

	bool create(const QString &filepath = QString());
	bool open(const QString &filepath = QString());

	QStringList tables() const;

private:
	QSqlDatabase m_db;

	void init();
};

#endif // DATABASE_DATABASE_H
