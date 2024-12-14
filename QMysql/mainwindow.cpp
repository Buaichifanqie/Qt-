#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建数据库连接
    QSqlDatabase dp = QSqlDatabase::addDatabase("QMYSQL");  // 使用MySQL数据库驱动
    QStringList list = QSqlDatabase::drivers();  // 获取所有可用的数据库驱动
    qDebug() << list;  // 打印支持的数据库驱动（调试用）

    // 设置数据库连接参数
    dp.setHostName("localhost");  // 数据库主机地址
    dp.setUserName("root");       // 用户名
    dp.setDatabaseName("buaifanqie");  // 数据库名称
    dp.setPassword("123456");     // 密码
    dp.setPort(3306);             // 数据库端口

    // 打开数据库连接
    if (!dp.open()) {
        qDebug() << "连接失败，失败原因：" << dp.lastError().text();  // 如果连接失败，打印错误信息
    } else {
        qDebug() << "数据库连接成功！！！";  // 如果连接成功，打印成功信息
    }

    // 创建查询对象
    QSqlQuery query;

    //数据库中添加数据
    QString sql="insert into score value(4,'Aoqi',100,98,97)";
    bool flag=query.exec(sql);
    if(flag)
    {
        dp.commit();//提交
    }
    else
    {
        dp.rollback();//回滚
    }

   sql = "SELECT * FROM score";  // SQL 查询语句，获取表score的所有数据
    if (query.exec(sql)) {  // 执行查询语句
        while (query.next()) {
            // 获取每一行的数据
            qDebug() << query.value(0).toUInt()        // 获取第一个字段（假设为ID）
                     << query.value(1).toString()   // 获取第二个字段（假设为姓名）
                     << query.value("math").toUInt()  // 获取数学成绩（根据列名）
                     << query.value(3).toUInt()      // 获取第四个字段（假设为英语成绩）
                     << query.value("chinese").toUInt(); // 获取语文成绩（根据列名）
        }
    } else {
        // 如果查询执行失败，输出错误信息
        qDebug() << "查询失败：" << query.lastError().text();
    }

    // 关闭数据库连接
    dp.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
