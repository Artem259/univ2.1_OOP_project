#include <QLineEdit>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

void MainWindow::hideButton(QPushButton *button)
{
    button->setEnabled(false);
    button->setStyleSheet("background: transparent; color: rgb(148, 203, 255);");
    button->setCursor(Qt::ArrowCursor);
}

void MainWindow::showButton(QPushButton *button, const QString &background)
{
    button->setEnabled(true);
    button->setStyleSheet("image: url(\"" + background + "\");\nbackground: transparent; color: rgb(255,205,0);");
    button->setCursor(Qt::PointingHandCursor);
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
            auto validator = new QDoubleValidator(this);
            validator->setDecimals(3);
            data->setValidator(validator);
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
            auto validator = new QDoubleValidator(this);
            validator->setDecimals(3);
            data->setValidator(validator);
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
                data->setText(QString::number((*from)(i,k), 'f', 3));
            }
            else
            {
                to->item(i,k)->setText(QString::number((*from)(i,k), 'f', 3));
            }
        }
    }
}

void MainWindow::updateSpins()
{
    if(currSpin != -1)
    {
        ui->spinAction->setText(spins[currSpin].first);
        setMatrix(&spins[currSpin].second, ui->spinTable);
    }

    ui->spinPage->setText(QString::number(currSpin+1) + "/" + QString::number(spins.size()));

    showButton(ui->upButton, ":/prefix1/images/up_arrow.png");
    showButton(ui->downButton, ":/prefix1/images/down_arrow.png");
    showButton(ui->deleteButton, ":/prefix1/images/delete.png");
    showButton(ui->copyButtonA, ":/prefix1/images/copy.png");
    showButton(ui->copyButtonB, ":/prefix1/images/copy.png");

    if(currSpin == -1)
    {
        hideButton(ui->upButton);
        hideButton(ui->downButton);
        hideButton(ui->deleteButton);
        hideButton(ui->copyButtonA);
        hideButton(ui->copyButtonB);

        ui->spinAction->setText("");
        ui->spinTable->setRowCount(0);
        ui->spinTable->setColumnCount(0);
    }
    if(currSpin == 0)
    {
        hideButton(ui->upButton);
    }
    if(currSpin == spins.size()-1)
    {
        hideButton(ui->downButton);
    }

    for(size_t i=0; i<ui->spinTable->rowCount(); i++)
    {
        for(size_t k=0; k<ui->spinTable->columnCount(); k++)
        {
            QLineEdit *data = ui->spinTable->findChild<QLineEdit*>(QString::number(i)+"_"+QString::number(k));
            data->setReadOnly(true);
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

void MainWindow::on_swapTablesButton_clicked()
{
    Eigen::MatrixXd tempMatrixA, tempMatrixB;
    size_t tempSizeRows, tempSizeCols;

    getMatrix(ui->tableA, &tempMatrixA);
    getMatrix(ui->tableB, &tempMatrixB);

    tempSizeRows = ui->tableA->rowCount();
    tempSizeCols = ui->tableA->columnCount();
    ui->tableRowsA->setValue(ui->tableB->rowCount());
    ui->tableColsA->setValue(ui->tableB->columnCount());
    ui->tableRowsB->setValue(tempSizeRows);
    ui->tableColsB->setValue(tempSizeCols);
    setMatrix(&tempMatrixA, ui->tableB);
    setMatrix(&tempMatrixB, ui->tableA);
}

void MainWindow::on_upButton_clicked()
{
    currSpin--;
    updateSpins();
}

void MainWindow::on_downButton_clicked()
{
    currSpin++;
    updateSpins();
}

void MainWindow::on_deleteButton_clicked()
{
    spins.erase(spins.begin()+currSpin);
    if(currSpin!=0) currSpin--;
    if(spins.size()==0) currSpin=-1;
    updateSpins();
}

void MainWindow::on_copyButtonA_clicked()
{
    ui->tableRowsA->setValue(spins[currSpin].second.rows());
    ui->tableColsA->setValue(spins[currSpin].second.cols());
    setMatrix(&spins[currSpin].second, ui->tableA);
}

void MainWindow::on_copyButtonB_clicked()
{
    ui->tableRowsB->setValue(spins[currSpin].second.rows());
    ui->tableColsB->setValue(spins[currSpin].second.cols());
    setMatrix(&spins[currSpin].second, ui->tableB);
}
