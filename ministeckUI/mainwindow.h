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
private:
    void CreateMinisteck(std::string path);
    Ui::MainWindow *ui;
    std::unique_ptr<IMinisteck> m_ministeck;
};
#endif // MAINWINDOW_H