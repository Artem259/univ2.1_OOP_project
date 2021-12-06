#include <QLineEdit>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLocale defaulfLocale(QLocale::C);
    defaulfLocale.setNumberOptions(QLocale::OmitGroupSeparator | QLocale::RejectGroupSeparator | QLocale::OmitLeadingZeroInExponent);
    QLocale::setDefault(defaulfLocale);


    ui->mult_editA->setValidator(new QDoubleValidator(this));
    ui->mult_editB->setValidator(new QDoubleValidator(this));

    on_tableRowsA_valueChanged(0);
    on_tableRowsB_valueChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeTable(QTableWidget *table, size_t rowsTarget, size_t colsTarget)
{
    size_t currRows = table->rowCount();
    size_t currCols = table->columnCount();

    while(currRows > rowsTarget)
    {
        table->removeRow(currRows-1);
        currRows--;
    }
    while(currRows < rowsTarget)
    {
        table->insertRow(currRows);
        for(size_t i = 0; i<currCols; i++)
        {
            table->setItem(currRows, i, new QTableWidgetItem());

            QLineEdit *data = new QLineEdit(table);
            data->setObjectName(QString::number(currRows) + "_" + QString::number(i));
            data->setValidator(new QDoubleValidator(this));
            table->setCellWidget(currRows, i, data);
            data->setAlignment(Qt::AlignCenter);
        }
        currRows++;
    }

    while(currCols > colsTarget)
    {
        table->removeColumn(currCols-1);
        currCols--;
    }
    while(currCols < colsTarget)
    {
        table->insertColumn(currCols);
        for(size_t i = 0; i<currRows; i++)
        {
            table->setItem(i, currCols, new QTableWidgetItem());

            QLineEdit *data = new QLineEdit(table);
            data->setObjectName(QString::number(i) + "_" + QString::number(currCols));
            data->setValidator(new QDoubleValidator(this));
            table->setCellWidget(i, currCols, data);
            data->setAlignment(Qt::AlignCenter);
        }
        currCols++;
    }
}

void MainWindow::getMatrix(QTableWidget *from, Eigen::MatrixXd *to)
{
    size_t rows = from->rowCount();
    size_t cols = from->columnCount();

    to->resize(rows, cols);
    for(size_t i=0; i<rows; i++)
    {
        for(size_t k=0; k<cols; k++)
        {
            QLineEdit *data = from->findChild<QLineEdit*>(QString::number(i)+"_"+QString::number(k));
            if(data)
            {
                if(data->text() == "")
                {
                    data->setText("0");
                }
                (*to)(i,k) = (data->text()).toDouble();
            }
            else
            {
                if(from->item(i,k)->text() == "")
                {
                    from->item(i,k)->setText("0");
                }
                (*to)(i,k) = (from->item(i,k)->text()).toDouble();
            }
        }
    }
}

void MainWindow::setMatrix(Eigen::MatrixXd *from, QTableWidget *to)
{
    size_t rows = from->rows();
    size_t cols = from->cols();

    resizeTable(to, rows, cols);
    for(size_t i=0; i<rows; i++)
    {
        for(size_t k=0; k<cols; k++)
        {
            QLineEdit *data = to->findChild<QLineEdit*>(QString::number(i)+"_"+QString::number(k));
            if(data)
            {
                data->setText(QString::number((*from)(i,k)));
            }
            else
            {
                to->item(i,k)->setText(QString::number((*from)(i,k)));
            }
        }
    }
}

void MainWindow::on_tableRowsA_valueChanged(int arg1)
{
    resizeTable(ui->tableA, ui->tableRowsA->value(), ui->tableColsA->value());
}

void MainWindow::on_tableColsA_valueChanged(int arg1)
{
    resizeTable(ui->tableA, ui->tableRowsA->value(), ui->tableColsA->value());
}

void MainWindow::on_tableRowsB_valueChanged(int arg1)
{
    resizeTable(ui->tableB, ui->tableRowsB->value(), ui->tableColsB->value());
}

void MainWindow::on_tableColsB_valueChanged(int arg1)
{
    resizeTable(ui->tableB, ui->tableRowsB->value(), ui->tableColsB->value());
}

void MainWindow::on_DeterminantButtonA_clicked()
{
    getMatrix(ui->tableA, &MatrixA);
    qDebug()<<MatrixA.determinant();
}

void MainWindow::on_DeterminantButtonB_clicked()
{
    getMatrix(ui->tableB, &MatrixB);
    qDebug()<<MatrixB.determinant();
}

void MainWindow::on_swapTablesButton_clicked()
{
    Eigen::MatrixXd tempA, tempB;
    getMatrix(ui->tableA, &tempA);
    getMatrix(ui->tableB, &tempB);
    setMatrix(&tempA, ui->tableB);
    setMatrix(&tempB, ui->tableA);
}

