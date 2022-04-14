#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT

public:
    explicit MyThread(MainWindow *w);
    ~MyThread();

    void run() override;

    void setUserName(QString& userName){m_userName = userName;};
    void setPassword(QString& password){m_password = password;};
    void setSqlTableModel(QSqlTableModel* sqlTableModel){m_sqlTableModel = sqlTableModel;};

    QString& getUserName(){return m_userName;};
    QString& getPassword(){return m_password;};
    QSqlTableModel* getSqlTableModel(){return m_sqlTableModel;};

public slots:
    void onClickedStart();
    void onClickedStop();
    void onClickedTest1();
    void onClickedTest2();
    void onCreateTable();
    void onDeleteTable();
    void onNotificationSQL();

private:

    MainWindow *m_window;
    QSqlDatabase m_db;
    QSqlTableModel *m_sqlTableModel;

    bool m_updateTableView;

    QString m_userName;
    QString m_password;

    QString m_tableName;

    bool initDataBase();
    void initSqlTableModel();

    bool subscribe();
    bool unsubscribe();
    bool hasTable();
    void updateTableView();
};

#endif // MYTHREAD_H
