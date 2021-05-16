#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include "libMinisteckBuilder.h"
#include "baseplate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionAddImageFile->setEnabled(false);
    ui->actionSettings->setEnabled(false);
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
        m_ministeck = LibMiniSteckBuilder::CreateIMinisteck(path, [this](const IMinisteck &libMinisteck,bool hasFile)
        {
            ui->actionAddImageFile->setEnabled(!hasFile);
            ui->actionSettings->setEnabled(hasFile);
            if (hasFile)
            {
                // during construction this callback can be called and the m_ministeck is not yet assigned
                m_rgbImage = libMinisteck.GetImage();
                //
                m_image = QImage((uchar*) m_rgbImage->data, m_rgbImage->cols, m_rgbImage->rows, m_rgbImage->step, QImage::Format_RGB888);

                ui->bitmap->setOriginalPixmap(std::make_unique<QPixmap>(QPixmap::fromImage(m_image)));
                ui->quantizedBitmap->setOriginalPixmap(std::make_unique<QPixmap>(QPixmap::fromImage(m_image)));

            }
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

void MainWindow::actionSettings()
{
    auto basePlate =std::make_unique<BasePlate>();
    BasePlateInfo info;
    info.imageWidth = m_rgbImage->cols;
    info.imageHeight = m_rgbImage->rows;
    auto [width, height] = m_ministeck->GetBasePlateSize();
    info.baseplateWidth = width;
    info.baseplateHeight = height;
    auto [offsetX, offsetY] =m_ministeck->GetImageOffset();
    info.imageOffsetX = offsetX;
    info.imageOffsetY = offsetY;

    info = basePlate->RunDialog(info);
    m_ministeck->SetBasePlateSize(info.baseplateWidth, info.baseplateHeight);
    m_ministeck->SetImageOffset(info.imageOffsetX, info.imageOffsetY);

}
