#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
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
    void on_determinantButtonA_clicked();
    void on_determinantButtonB_clicked();
    void on_swapTablesButton_clicked();
    void on_multTablesButton_clicked();
    void on_addTablesButton_clicked();
    void on_subTablesButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_deleteButton_clicked();

    void on_copyButtonA_clicked();

    void on_copyButtonB_clicked();

    void on_inverseButtonA_clicked();

    void on_inverseButtonB_clicked();


    void on_transposeButtonA_clicked();

    void on_transposeButtonB_clicked();

    void on_rankButtonA_clicked();

    void on_rankButtonB_clicked();

    void on_multByButtonA_clicked();

    void on_multByButtonB_clicked();

private:
    Ui::MainWindow *ui;
    Eigen::MatrixXd MatrixA;
    Eigen::MatrixXd MatrixB;
    bool isError;
    int currSpin;
    std::vector<std::pair<QString, Eigen::MatrixXd>> spins;

    void hideButton(QPushButton *button);
    void showButton(QPushButton *button, const QString &background);
    void resizeTable(QTableWidget *table, size_t rowsTarget, size_t colsTarget);
    void getMatrix(QTableWidget *from, Eigen::MatrixXd *to);
    void setMatrix(Eigen::MatrixXd *from, QTableWidget *to);
    void updateSpins();
};

#endif
