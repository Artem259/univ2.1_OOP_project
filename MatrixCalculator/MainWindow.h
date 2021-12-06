#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <Eigen/Dense>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tableRowsA_valueChanged(int arg1);
    void on_tableRowsB_valueChanged(int arg1);
    void on_tableColsA_valueChanged(int arg1);
    void on_tableColsB_valueChanged(int arg1);

    void on_DeterminantButtonA_clicked();

    void on_DeterminantButtonB_clicked();

    void on_swapTablesButton_clicked();

private:
    Ui::MainWindow *ui;
    Eigen::MatrixXd MatrixA;
    Eigen::MatrixXd MatrixB;

    void resizeTable(QTableWidget *table, size_t rowsTarget, size_t colsTarget);
    void getMatrix(QTableWidget *from, Eigen::MatrixXd *to);
    void setMatrix(Eigen::MatrixXd *from, QTableWidget *to);
};

#endif
