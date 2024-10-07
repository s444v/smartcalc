#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>
#include <QLocale>
#include <iostream>
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    ui->x_max->setText("10");
    ui->x_min->setText("-10");
    ui->y_max->setText("10");
    ui->y_min->setText("-10");
    ui->step->setText("0.2");
    ui->x_value->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_0_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"0");
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"1");
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"2");
}
void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"3");
}
void MainWindow::on_pushButton_4_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"4");
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"5");
}
void MainWindow::on_pushButton_6_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"6");
}
void MainWindow::on_pushButton_7_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"7");
}
void MainWindow::on_pushButton_8_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"8");
}
void MainWindow::on_pushButton_9_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"9");
}

void MainWindow::on_pushButton_mod_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"%");
}

void MainWindow::on_pushButton_plus_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"+");
}
void MainWindow::on_pushButton_minus_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"-");
}

void MainWindow::on_pushButton_divide_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"/");
}

void MainWindow::on_pushButton_multiply_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"*");
}

void MainWindow::on_pushButton_point_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+".");
}

void MainWindow::on_pushButton_ob_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"(");
}

void MainWindow::on_pushButton_cb_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+")");
}

void MainWindow::on_pushButton_sin_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"sin(");
}
void MainWindow::on_pushButton_cos_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"cos(");
}
void MainWindow::on_pushButton_tan_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"tan(");
}
void MainWindow::on_pushButton_asin_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"asin(");
}
void MainWindow::on_pushButton_acos_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"acos(");
}
void MainWindow::on_pushButton_atan_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"atan(");
}
void MainWindow::on_pushButton_ln_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"ln(");
}
void MainWindow::on_pushButton_lg_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"lg(");
}
void MainWindow::on_pushButton_sqrt_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"sqrt(");
}

void MainWindow::on_pushButton_pow_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"^");
}

void MainWindow::on_pushButton_x_clicked()
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText()+"x");
}

void MainWindow::on_pushButton_graph_clicked()
{
    setlocale(LC_NUMERIC, "C");
    QString textToSend = ui->textBrowser->toPlainText();
    QByteArray byteArray = textToSend.toUtf8();
    const char* charArray = byteArray.constData();
    int flag = 0;
    bool flag2, flag3, flag4,flag5,flag6 = true;
    QVector<double> arrayX;
    QVector<double> arrayY;
    double x_max = ui->x_max->text().toDouble(&flag2);
    double x_min = ui->x_min->text().toDouble(&flag3);
    double y_max = ui->y_max->text().toDouble(&flag4);
    double y_min = ui->y_min->text().toDouble(&flag5);
    double step = ui->step->text().toDouble(&flag6);
    if (flag2&&flag3&&flag4&&flag5&&flag6){
    double i = x_min;
    while (i<=x_max){
        double result = graphResult(charArray,i,&flag);
        if (result>=y_min && result<=y_max){
            arrayX.push_back(i);
            arrayY.push_back(result);
        }
        i+=step;
    }
    if (flag){
        QMessageBox::warning(this, "Внимание","Некорректный ввод");

    }
    else{
        ui->plot->addGraph();
        ui->plot->graph(0)->setData(arrayX,arrayY);
        ui->plot->xAxis->setLabel("x");
        ui->plot->yAxis->setLabel("y");
        ui->plot->xAxis->setRange(x_min,x_max);
        ui->plot->yAxis->setRange(y_min,y_max);
        ui->plot->replot();
        }
    }
    else{
        QMessageBox::warning(this, "Внимание","Некорректный ввод");
    }
    arrayY.clear();
    arrayX.clear();
}

void MainWindow::on_pushButton_remove_clicked() {
    QString res = ui->textBrowser->toPlainText();
    res.chop(1);
    ui->textBrowser->setText(res);
    if (ui->textBrowser->toPlainText() == "") {
        ui->textBrowser->setText("");
    }
}

void MainWindow::on_pushButton_equal_clicked() {
    setlocale(LC_NUMERIC, "C");
    QString textToSend = ui->textBrowser->toPlainText();
    QByteArray byteArray = textToSend.toUtf8();
    const char* charArray = byteArray.constData();
    int flag = 0;
    bool flag_value = true;
    ui->x_value->text().toDouble(&flag_value);
    double resultNumber = outputResult(charArray,ui->x_value->text().toDouble(), &flag);
    if (flag||flag_value==false){
        QMessageBox::warning(this, "Внимание","Некорректный ввод");

    }
    else{
        QString myStringValue = QString::number(resultNumber);
        ui->textBrowser->setText(myStringValue);
    }
}
