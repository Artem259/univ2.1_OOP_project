#include <QLineEdit>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLocale::setDefault(QLocale(QLocale::C));

    ui->mult_editA->setValidator(new QDoubleValidator(this));
    ui->mult_editB->setValidator(new QDoubleValidator(this));

    on_tableRowsA_valueChanged(0);
    on_tableRowsB_valueChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isNumber(const QString &str)
{
    bool ok;
    str.toDouble(&ok);
    return ok;
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

            QLineEdit *edit = new QLineEdit(table);
            edit->setValidator(new QDoubleValidator(edit));
            table->setCellWidget(currRows, i, edit);
            edit->setAlignment(Qt::AlignCenter);
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

            QLineEdit *edit = new QLineEdit(table);
            edit->setValidator(new QDoubleValidator(edit));
            table->setCellWidget(i, currCols, edit);
            edit->setAlignment(Qt::AlignCenter);
        }
        currCols++;
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

