#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include "libMinisteckBuilder.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionAddImageFile->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionOpen()
{

    auto fileName = QFileDialog::getOpenFileName(this,
         tr("Ministeck"), "", tr("Ministeck Files (*.mini)"));
    CreateMinisteck(fileName.toStdString());
//    QMessageBox msgBox;
  //  msgBox.setText("The document has been modified.");
    //msgBox.exec();

}

void MainWindow::CreateMinisteck(std::string path)
{
    if (!path.empty())
    {
        m_ministeck = LibMiniSteckBuilder::CreateIMinisteck(path, [this](bool hasFile)
        {
            ui->actionAddImageFile->setEnabled(!hasFile);
        });
    }
}

void MainWindow::actionNew()
{
    QString filter("Ministeck Files (*.mini)");
    QString fileName = QFileDialog::getSaveFileName(this, tr("New File"),
                               "untitled.mini",
                               filter, &filter);
    CreateMinisteck(fileName.toStdString());

    std::cout << fileName.toStdString() << std::endl;
//    QMessageBox msgBox;
  //  msgBox.setText("The document has been modified.");
    //msgBox.exec();

}

void MainWindow::actionAddImageFile()
{
    auto fileName = QFileDialog::getOpenFileName(this,
         tr("Ministeck"), "", tr("Image Files (*.jpg)"));
    m_ministeck->AddImageFile(fileName.toStdString());
}
