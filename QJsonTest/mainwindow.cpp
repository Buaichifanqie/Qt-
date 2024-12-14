#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QJsonDocument doc;
    if(doc.isEmpty())
    {
        qDebug()<<"json document is empty...";
    }
    if(doc.isNull())
    {
        qDebug()<<"json document is null...";
    }
    writeJson();
    readJson();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
{
    "Name":"Ace",
    "Sex":"man",
    "Age":20,
    "Family":{
        "Father":"Gol·D·Roger",
        "Mother":"Portgas·D·Rouge",
        "Brother":["Sabo", "Monkey D. Luffy"]
    },
    "IsAlive":false,
    "Comment":"yyds"
}
*/


void MainWindow::writeJson()
{
    QJsonObject obj;
    obj.insert("name","Ace");//发生了隐式类型转换，转换成了QJsonValue类型
    obj.insert("sex","man");
    obj.insert("age",20);

    QJsonObject sunobj;
    sunobj.insert("father","Gol·D·Roger");
    sunobj.insert("mother","Portgas·D·Rouge");

    QJsonArray array;
    array.append("Sabo");
    array.append("Monkey D. Luffy");
    sunobj.insert("brother",array);

    obj.insert("family",sunobj);
    obj.insert("isAlive","Ace");
    obj.insert("comment","yyds");

    //得到文档对象
    QJsonDocument doc(obj);
    //转换文档转换成字符串类型
    QByteArray json=doc.toJson();
    //写进磁盘
    QFile file("D:\\ace.json");
    //打开关联的磁盘文件
    file.open(QFile::WriteOnly);

    file.write(json);
    file.close();

}


//从磁盘中读文件
void MainWindow::readJson()
{
    // 打开并读取文件
    QFile file("D:\\ace.json");  // 定义文件路径
    file.open(QFile::ReadOnly);   // 打开文件为只读模式
    QByteArray json = file.readAll();  // 读取文件所有内容
    file.close();  // 关闭文件

    // 解析JSON数据
    QJsonDocument doc = QJsonDocument::fromJson(json);  // 将读取到的字节数组解析为QJsonDocument对象
    if(doc.isObject())  // 如果JSON文档是一个对象
    {
        QJsonObject obj = doc.object();  // 获取JSON对象
        QStringList keys = obj.keys();  // 获取对象的所有键
        for(int i=0; i<keys.size(); ++i)  // 遍历每个键
        {
            QString key = keys.at(i);  // 获取键
            QJsonValue value = obj.value(key);  // 获取键对应的值

            // 判断值的类型并输出
            if(value.isBool())  // 如果值是布尔类型
            {
                qDebug() << key << ":" << value.toBool();  // 输出键和值
            }
            if(value.isString())  // 如果值是字符串类型
            {
                qDebug() << key << ":" << value.toString();  // 输出键和值
            }
            if(value.isDouble())  // 如果值是数字类型
            {
                qDebug() << key << ":" << value.toInt();  // 输出键和值（转换为整型）
            }
            if(value.isObject())  // 如果值是一个嵌套的JSON对象
            {
                qDebug()<< key << ":";  // 输出当前键
                // 直接处理内部的键值对，不再进行类型判断的演示
                QJsonObject subObj = value.toObject();  // 获取嵌套的JSON对象
                QStringList ls = subObj.keys();  // 获取嵌套对象的所有键
                for(int i=0; i<ls.size(); ++i)  // 遍历嵌套对象的键
                {
                    QJsonValue subVal = subObj.value(ls.at(i));  // 获取嵌套对象中的值
                    if(subVal.isString())  // 如果值是字符串
                    {
                        qDebug() << "   " << ls.at(i) << ":" << subVal.toString();  // 输出嵌套键值对
                    }
                    if(subVal.isArray())  // 如果值是数组
                    {
                        QJsonArray array = subVal.toArray();  // 获取数组
                        qDebug() << "   " << ls.at(i) << ":";  // 输出嵌套键
                        for(int j=0; j<array.size(); ++j)  // 遍历数组
                        {
                            // 因为知道数组内部全部为字符串，不再对元素类型进行判断
                            qDebug() << "       " << array[j].toString();  // 输出数组中的每个元素
                        }
                    }
                }
            }
        }
    }
}
