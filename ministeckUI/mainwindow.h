#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "IMinisteck.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void actionOpen();
    void actionNew();
    void actionAddImageFile();
    void actionSettings();
    void actionQuantizeImage();
private:
    void CreateMinisteck(std::string path);
    virtual bool eventFilter(QObject *obj, QEvent *event);
    Ui::MainWindow *ui;
    std::unique_ptr<IMinisteck> m_ministeck;
    std::shared_ptr<cv::Mat> m_rgbImage;
    std::shared_ptr<cv::Mat> m_ministeckImage;
    std::shared_ptr<cv::Mat> m_quantizedImage;
    QImage m_image;
};
#endif // MAINWINDOW_H
