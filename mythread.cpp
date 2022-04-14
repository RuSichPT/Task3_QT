#include "mythread.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QTimer>

MyThread::MyThread(MainWindow *w)
    :m_window(w), m_sqlTableModel(nullptr), m_updateTableView(false),
    m_userName(""), m_password(""), m_tableName("mytable")
{
    connect(m_window->getUI()->m_buttonStart, &QPushButton::clicked, this, &MyThread::onClickedStart);
    connect(m_window->getUI()->m_buttonStop, &QPushButton::clicked, this, &MyThread::onClickedStop);
    connect(m_window->getUI()->m_buttonTest1, &QPushButton::clicked, this, &MyThread::onClickedTest1);
    connect(m_window->getUI()->m_buttonTest2, &QPushButton::clicked, this, &MyThread::onClickedTest2);
    connect(m_window->getUI()->m_buttonCreateTable, &QPushButton::clicked, this, &MyThread::onCreateTable);
    connect(m_window->getUI()->m_buttonDeleteTable, &QPushButton::clicked, this, &MyThread::onDeleteTable);
}

MyThread::~MyThread()
{
    delete m_sqlTableModel;
}

void MyThread::run()
{
    qDebug() << "The second thread";

    while(true)
    {
        while(m_updateTableView)
        {
            updateTableView();
            m_updateTableView = false;
        }
    }
}

bool MyThread::initDataBase()
{
    if(!QFile::exists("./dataBase/my_db.sqlite"))
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Такой базы данных не существет");
        msgBox.exec();

        return false;
    }

    // Берем имя соединения по умолчанию
    QString connection = QString(QSqlDatabase::defaultConnection);

    // Проверка на наличие соединения с именем connection
    if (QSqlDatabase::contains(connection)) //это нужно, чтобы не возникало ошибки о повторном соединении
    {
        // Получаем указатель на открытое соединение
        m_db = QSqlDatabase::database(connection);
    }
    else
    {
        //Подключаемся через QSQLITE драйвер
        m_db = QSqlDatabase::addDatabase("QSQLITE", connection);
        m_db.setHostName("localhost");
        m_db.setDatabaseName("./dataBase/my_db.sqlite");//вписываем имя БД
        m_db.setUserName(m_userName);
        m_db.setPassword(m_password);
        m_db.open(); //открываем соединение

        qDebug() << "data base open";
        qDebug() << "driver has notification? "<< m_db.driver()->hasFeature(QSqlDriver::EventNotifications);
    }   

    if (hasTable())
    {
        if(!subscribe())
        {
            return false;
        }
    }

    return true;
}

void MyThread::initSqlTableModel()
{
    if (m_sqlTableModel != nullptr)
    {
        delete m_sqlTableModel;
    }

    m_sqlTableModel = new QSqlTableModel(this);
    m_sqlTableModel->setTable(m_tableName);

    m_sqlTableModel->setHeaderData(0, Qt::Orientation::Horizontal, "Id");
    m_sqlTableModel->setHeaderData(1, Qt::Orientation::Horizontal, "Flag");
    m_sqlTableModel->setHeaderData(2, Qt::Orientation::Horizontal, "Data");

    m_window->getUI()->m_tableView->setModel(m_sqlTableModel);
    m_window->getUI()->m_tableView->show();
}

void MyThread::onClickedStart()
{
    qDebug() << "click start ";

    if (initDataBase())
    {
        initSqlTableModel();

        m_updateTableView = true;
    }
}

void MyThread::onClickedStop()
{
    qDebug() << "click stop ";

    m_db.close();
    if (m_sqlTableModel != nullptr)
    {
        m_sqlTableModel->clear();
    }
    qDebug() << "data base close";
}

void MyThread::onClickedTest1()
{
    qDebug() << "click test1 ";

    QString str;
    int n = 1000;
    str = "INSERT INTO "+ m_tableName + " (flag, data)" + " VALUES";
    for (int i = 0; i < n; i++)
    {
        if (i < n-1)
        {
            str += " (true, 'test'),";
        }
        else
        {
            str += " (true, 'test');";
        }
    }

    QSqlQuery query;

    bool ok = query.exec(str);
    if(!ok)
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка при добавлении элемента в таблицу: " + query.lastError().databaseText());
        msgBox.exec();
    }
}

void MyThread::onClickedTest2()
{
    qDebug() << "click test2 ";

    QSqlQuery query;
    static bool value;

    query.exec("SELECT flag FROM " + m_tableName + " WHERE id=1;");

    while (query.next())
    {
        value = query.value("flag").toBool();
    }

    QString str;
    if (value)
    {
        str = "UPDATE "+ m_tableName + " SET flag = false;";
    }
    else
    {
        str = "UPDATE "+ m_tableName + " SET flag = true;";
    }

    bool ok = query.exec(str);
    if(!ok)
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка при добавлении элемента в таблицу: " + query.lastError().databaseText());
        msgBox.exec();
    }

    value = !value;
}

void MyThread::onCreateTable()
{
    if(!subscribe())
    {
        return;
    }

    QSqlQuery query;

    bool ok = query.exec("CREATE TABLE "+ m_tableName +" (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                                      " flag BIT,"
                                                      " data TEXT);");
    if (!ok)
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка при создании таблицы: " + query.lastError().databaseText());
        msgBox.exec();
    }

    initSqlTableModel();

    m_updateTableView = true;
}

void MyThread::onDeleteTable()
{
    m_sqlTableModel->clear();

    if(!unsubscribe())
    {
        return;
    }

    QSqlQuery query;

    bool ok = query.exec("DROP TABLE " + m_tableName);

    if (!ok)
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка при удалении таблицы: " + query.lastError().databaseText());
        msgBox.exec();
    }
}

void MyThread::onNotificationSQL()
{
    qDebug() << "notific slot";

    m_updateTableView = true;

}

bool MyThread::subscribe()
{
    if(!m_db.isOpen())
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка при подключении к базе данных: " + m_db.lastError().databaseText());
        msgBox.exec();

        return false;
    }
    else if(m_db.driver()->subscribeToNotification(m_tableName))
    {
        qDebug() << "subscribe to "<< m_tableName;
        connect(m_db.driver(), static_cast<void(QSqlDriver::*)(const QString &)>(&QSqlDriver::notification), this, &MyThread::onNotificationSQL);
        return  true;
    }
    else
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка notify: " + m_db.driver()->lastError().databaseText());
        msgBox.exec();
    }

    return false;
}

bool MyThread::unsubscribe()
{
    if(!m_db.isOpen())
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка при подключении к базе данных: " + m_db.lastError().databaseText());
        msgBox.exec();

        return false;
    }
    else if(m_db.driver()->unsubscribeFromNotification(m_tableName))
    {
        qDebug() << "unsubscribe to "<< m_tableName;
        disconnect(m_db.driver(), static_cast<void(QSqlDriver::*)(const QString &)>(&QSqlDriver::notification), this, &MyThread::onNotificationSQL);
        return  true;
    }
    else
    {
        QMessageBox msgBox;

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка notify: " + m_db.driver()->lastError().text());
        msgBox.exec();
    }

    return false;
}

void MyThread::updateTableView()
{
    if (m_sqlTableModel != nullptr)
    {
        if (m_sqlTableModel->select())
        {
            qDebug() << "updata data base ";
        }
        else
        {
            qDebug() << "not updata data base.Error: " << m_sqlTableModel->lastError().text();
        }
    }
}

bool MyThread::hasTable()
{
    QSqlQuery query;

    return query.exec("SELECT * FROM " + m_tableName);
}
