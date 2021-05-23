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
    ui->quantizedBitmap->installEventFilter(this);
    ui->quantizedBitmap->setMouseTracking(true);

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
        statusBar()->showMessage("Status");
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

void MainWindow::actionQuantizeImage()
{
    m_quantizedImage = m_ministeck->QuantizeImage();
    auto image = QImage((uchar*) m_quantizedImage->data, m_quantizedImage->cols, m_quantizedImage->rows, m_quantizedImage->step, QImage::Format_RGB888);

    ui->quantizedBitmap->setOriginalPixmap(std::make_unique<QPixmap>(QPixmap::fromImage(image)));

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
/*
        if (event->type() == QEvent::MouseButtonPress) {
            qDebug("Mouse has been pressed\n");
            statusBar()->showMessage("Mousepress");
        }
*/
    if (obj == ui->quantizedBitmap)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            const QMouseEvent* const me = static_cast<const QMouseEvent*>( event );
            //might want to check the buttons here
            const QPoint p = me->pos(); //...or ->globalPos();

            QString string(("MousePress "+ std::to_string(p.x()) + " "  + std::to_string(p.y()) + " " + std::to_string(ui->quantizedBitmap->width()) + "x" + std::to_string(ui->quantizedBitmap->height())).c_str());
            if (m_quantizedImage)
            {
                double scaling = std::max(static_cast<double>(m_quantizedImage->cols) / ui->quantizedBitmap->width(),
                                          static_cast<double>(m_quantizedImage->rows) / ui->quantizedBitmap->height());
                int x=static_cast<int>(p.x()*scaling);
                int y=static_cast<int>(p.y()*scaling);
                string = m_ministeck->GetStatus(x,y).c_str();

                //auto s = QString(" %1x%2 pos %3x%4").arg(m_quantizedImage->cols).arg(m_quantizedImage->rows).arg(x).arg(y);
                //string = string + s;
            }

            statusBar()->showMessage(string);
            return true;
        }
    }

    return false;
}
