#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_writeButton_clicked()
{
    //Save the file to disk
    QString filename = QFileDialog::getSaveFileName(this,"Save");
    if(filename.isEmpty())
            return;

    //Creat file object
    QFile file(filename);

    //Open the file with 3 mode
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;

    //Create stream and write textEdit to stream
    QTextStream out(&file);
    out << ui->textEdit->toPlainText() << "\n";

    file.close();
}

void Widget::on_readButton_clicked()
{
    QString fileContent;
    //Save the file to disk
    QString filename = QFileDialog::getOpenFileName(this,"Open File");

    if(filename.isEmpty())
        return;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream in(&file);

    //read the first line
    QString line = in.readLine ();

    while(!line.isNull()){
        fileContent.append(line);
        line = in.readLine();
    }
    file.close();

    ui->textEdit->clear();
    ui->textEdit->setPlainText(fileContent);
}


void Widget::on_selectsrcFileButton_clicked()
{
    QString srcfilename = QFileDialog::getOpenFileName(this,"Choose File");
    if(srcfilename.isEmpty())
        return;

    //put filename to srcline
    ui->sourcelineEdit->setText(srcfilename);
}


void Widget::on_copyButton_clicked()
{
    //the path to src & dest file be stored
    QString srcFileName = ui->sourcelineEdit->text();
    QString destFileName = ui->destlineEdit->text();

    //check both file have chars
    if(srcFileName.isEmpty() || destFileName.isEmpty())
        return;

    //setup a file object point to the sourcefile
    QFile file(srcFileName);

    //copy the srcfile data and paste data in destfile
    if(file.copy(destFileName))
    {
        QMessageBox::information(this,"Success","Copy successful");
    }else
    {
        QMessageBox::information(this,"Failure","Copy Failed");
    }
}


