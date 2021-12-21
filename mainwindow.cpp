#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../../db/Employees.db");
    if (db.open())
    {
        ui->statusbar->showMessage("Вы успешно подключились к базе данных: " + db.databaseName());

        model = new QSqlTableModel(this, db);
        model->setTable("USERS");
        model->select();

        ui->tableView->setModel(model);
    }
    else
    {
        ui->statusbar->showMessage("При подключении к базе данных произошла ошибка: " + db.lastError().databaseText());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    model->insertRow(model->rowCount());
}


void MainWindow::on_btnRemove_clicked()
{
    model->removeRow(currentRow);
    model->select();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

