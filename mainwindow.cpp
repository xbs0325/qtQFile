#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        QFileDialog fdlog(this);
        fileName = fdlog.getOpenFileName(this,"打开文件","C:\\Users\\as\\Desktop");
        ui->lineEdit->setText(fileName);

        QFile file(fileName);
        QFileInfo fileInfo(fileName);

        file.open(QIODevice::ReadOnly);
        QString text = file.readAll();
        ui->textEdit->setText(text);

        ui->label_1->setText("文件名: "+fileInfo.fileName());
        ui->label_2->setText("创建日期: "+fileInfo.birthTime().toString("yyyy/MM/dd hh:mm:ss"));
        ui->label_3->setText("后缀名: "+fileInfo.suffix());
    });
    connect(ui->btnSave,&QPushButton::clicked,this,[=](){
        qDebug() <<"保存成功";
        QString text2 = ui->textEdit->toPlainText();
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        file.write(text2.toUtf8());
        file.close();
    });
    connect(ui->btnClose,&QPushButton::clicked,this,[=](){
        close();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

