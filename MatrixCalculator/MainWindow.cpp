#include <QLineEdit>
#include <Eigen/LU>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    spins = {};
    currSpin = -1;
    isError = false;

    QLocale defaulfLocale(QLocale::C);
    defaulfLocale.setNumberOptions(QLocale::OmitGroupSeparator | QLocale::RejectGroupSeparator | QLocale::OmitLeadingZeroInExponent);
    QLocale::setDefault(defaulfLocale);

    ui->multByEditA->setValidator(new QDoubleValidator(this));
    ui->multByEditB->setValidator(new QDoubleValidator(this));

    on_tableRowsA_valueChanged(0);
    on_tableRowsB_valueChanged(0);
    updateSpins();
}

MainWindow::~MainWindow()
{
    delete ui;
}
