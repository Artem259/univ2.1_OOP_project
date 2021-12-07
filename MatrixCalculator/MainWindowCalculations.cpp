#include <QLineEdit>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

void MainWindow::on_determinantButtonA_clicked()
{
    getMatrix(ui->tableA, &MatrixA);
    if(MatrixA.rows()==MatrixA.cols())
    {
        ui->outputLine->setText(QString::number(MatrixA.determinant(), 'g', 10));
        isError = false;
    }
    else
    {
        ui->outputLine->setText(" Cannot be calculated for a non-square matrix.");
        isError = true;
    }
}

void MainWindow::on_determinantButtonB_clicked()
{
    getMatrix(ui->tableB, &MatrixB);
    if(MatrixB.rows()==MatrixB.cols())
    {
        ui->outputLine->setText(QString::number(MatrixB.determinant(), 'g', 10));
        isError = false;
    }
    else
    {
        ui->outputLine->setText(" Cannot be calculated for a non-square matrix.");
        isError = true;
    }
}

void MainWindow::on_multTablesButton_clicked()
{
    getMatrix(ui->tableA, &MatrixA);
    getMatrix(ui->tableB, &MatrixB);
    if(MatrixA.cols() != MatrixB.rows())
    {
        ui->outputLine->setText(" The number of columns in the matrix A must be equal to the number of rows in the matrix B.");
        isError = true;
        return;
    }
    Eigen::MatrixXd res = MatrixA*MatrixB;

    if(isError) ui->outputLine->setText("");
    isError = false;
    spins.insert(spins.begin(), {"A × B", res});
    currSpin = 0;
    updateSpins();
}

void MainWindow::on_addTablesButton_clicked()
{
    getMatrix(ui->tableA, &MatrixA);
    getMatrix(ui->tableB, &MatrixB);
    if((MatrixA.rows()!=MatrixB.rows()) || (MatrixA.cols()!=MatrixB.cols()))
    {
        ui->outputLine->setText(" Matrix A and matrix B must have an equal number of rows and columns to be added.");
        isError = true;
        return;
    }
    Eigen::MatrixXd res = MatrixA+MatrixB;

    if(isError) ui->outputLine->setText("");
    isError = false;
    spins.insert(spins.begin(), {"A + B", res});
    currSpin = 0;
    updateSpins();
}

void MainWindow::on_subTablesButton_clicked()
{
    getMatrix(ui->tableA, &MatrixA);
    getMatrix(ui->tableB, &MatrixB);
    if((MatrixA.rows()!=MatrixB.rows()) || (MatrixA.cols()!=MatrixB.cols()))
    {
        ui->outputLine->setText(" Matrix A and matrix B must have an equal number of rows and columns to be subtracted.");
        isError = true;
        return;
    }
    Eigen::MatrixXd res = MatrixA-MatrixB;

    if(isError) ui->outputLine->setText("");
    isError = false;
    spins.insert(spins.begin(), {"A - B", res});
    currSpin = 0;
    updateSpins();
}

void MainWindow::on_inverseButtonA_clicked()
{
    getMatrix(ui->tableA, &MatrixA);
    if(MatrixA.rows()!=MatrixA.cols())
    {
        ui->outputLine->setText(" Cannot be calculated for a non-square matrix.");
        isError = true;
        return;
    }
    if(MatrixA.determinant()==0)
    {
        ui->outputLine->setText(" Cannot be calculated for a matrix with determinant equal to zero.");
        isError = true;
        return;
    }
    Eigen::MatrixXd res = MatrixA.inverse();

    if(isError) ui->outputLine->setText("");
    isError = false;
    spins.insert(spins.begin(), {"Inverse of A", res});
    currSpin = 0;
    updateSpins();
}

void MainWindow::on_inverseButtonB_clicked()
{
    getMatrix(ui->tableB, &MatrixB);
    if(MatrixB.rows()!=MatrixB.cols())
    {
        ui->outputLine->setText(" Cannot be calculated for a non-square matrix.");
        isError = true;
        return;
    }
    if(MatrixB.determinant()==0)
    {
        ui->outputLine->setText(" Cannot be calculated for a matrix with determinant equal to zero.");
        isError = true;
        return;
    }
    Eigen::MatrixXd res = MatrixB.inverse();

    if(isError) ui->outputLine->setText("");
    isError = false;
    spins.insert(spins.begin(), {"Inverse of B", res});
    currSpin = 0;
    updateSpins();
}

void MainWindow::on_transposeButtonA_clicked()
{
    getMatrix(ui->tableA, &MatrixA);
    Eigen::MatrixXd res = MatrixA.transpose();

    if(isError) ui->outputLine->setText("");
    isError = false;
    spins.insert(spins.begin(), {"Transpose of A", res});
    currSpin = 0;
    updateSpins();
}

void MainWindow::on_transposeButtonB_clicked()
{
    getMatrix(ui->tableB, &MatrixB);
    Eigen::MatrixXd res = MatrixB.transpose();

    if(isError) ui->outputLine->setText("");
    isError = false;
    spins.insert(spins.begin(), {"Transpose of B", res});
    currSpin = 0;
    updateSpins();
}

void MainWindow::on_rankButtonA_clicked()
{
    getMatrix(ui->tableA, &MatrixA);
    Eigen::FullPivLU<Eigen::MatrixXd> decomp(MatrixA);
    auto rank = decomp.rank();

    isError = false;
    ui->outputLine->setText(QString::number(rank));
}

void MainWindow::on_rankButtonB_clicked()
{
    getMatrix(ui->tableB, &MatrixB);
    Eigen::FullPivLU<Eigen::MatrixXd> decomp(MatrixB);
    auto rank = decomp.rank();

    isError = false;
    ui->outputLine->setText(QString::number(rank));
}

void MainWindow::on_multByButtonA_clicked()
{
    getMatrix(ui->tableA, &MatrixA);
    if(ui->multByEditA->text()=="") ui->multByEditA->setText("0");
    Eigen::MatrixXd res = (ui->multByEditA->text()).toDouble()*MatrixA;

    if(isError) ui->outputLine->setText("");
    isError = false;
    spins.insert(spins.begin(), {"Multiply A by " + ui->multByEditA->text(), res});
    currSpin = 0;
    updateSpins();
}

void MainWindow::on_multByButtonB_clicked()
{
    getMatrix(ui->tableB, &MatrixB);
    if(ui->multByEditB->text()=="") ui->multByEditB->setText("0");
    Eigen::MatrixXd res = (ui->multByEditB->text()).toDouble()*MatrixB;

    if(isError) ui->outputLine->setText("");
    isError = false;
    spins.insert(spins.begin(), {"Multiply B by " + ui->multByEditB->text(), res});
    currSpin = 0;
    updateSpins();
}
