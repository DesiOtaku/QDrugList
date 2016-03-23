/*
 * (C) 2016 Tej A. Shah
 * This file is part of QDrugList

    QDrugList is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QDrugList is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QDrugList.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "druginputedit.h"
#include "aboutdialog.h"

#include <QStringListModel>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(":/druglist.csv");
    if (file.open(QFile::ReadOnly)) {
        QStringList modelList;
        //_useHash.reserve(802107);
        while(!file.atEnd()) {
            QString genName = file.readLine().trimmed();
            QString brandName = file.readLine().trimmed();
            QString usedFor = file.readLine().trimmed();

            _useHash[genName] = usedFor;
            _useHash[brandName] = usedFor;

            if(!modelList.contains(genName)) {
                modelList<<genName;
            }

            if(!modelList.contains(brandName)) {
                modelList<<brandName;
            }
        }
        ui->drugListInput->setDrugList(modelList);
    }

    connect(ui->drugListInput,SIGNAL(drugNameChanged(QString)),this,SLOT(handleUpdateDrugName(QString)));
    connect(ui->actionCopy_All,SIGNAL(triggered()),this,SLOT(handleCopyAll()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleUpdateDrugName(QString newDrugName) {
    qDebug()<<newDrugName;
    if(_useHash.contains(newDrugName)) {
        ui->drugInfoBox->setText(_useHash[newDrugName]);
    } else {
        ui->drugInfoBox->setText("");
    }
}

void MainWindow::handleCopyAll() {
    ui->drugListInput->selectAll();
    ui->drugListInput->copy();

}

void MainWindow::showAbout() {
    AboutDialog dia;
    dia.exec();
}
