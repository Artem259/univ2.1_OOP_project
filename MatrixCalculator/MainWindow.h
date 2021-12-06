#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

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

private:
    Ui::MainWindow *ui;

    bool isNumber(const QString &str);
    void resizeTable(QTableWidget *table, size_t rowsTarget, size_t colsTarget);
};

#endif
