#ifndef BASEPLATE_H
#define BASEPLATE_H

#include "./ui_basePlate.h"

struct BasePlateInfo
{
    bool changed=false;
    int baseplateWidth =0;
    int baseplateHeight = 0;
    int imageWidth = 0;
    int imageHeight = 0;
    int imageOffsetX = 0;
    int imageOffsetY = 0;
    bool operator==(const BasePlateInfo& lhs) const
    {
        return (changed == lhs.changed)
                &&(baseplateWidth==lhs.baseplateWidth)
                &&(baseplateHeight==lhs.baseplateHeight)
                && (imageWidth == lhs.imageWidth)
                && (imageHeight == lhs.imageHeight)
                && (imageOffsetX == lhs.imageOffsetX)
                && (imageOffsetY == lhs.imageOffsetY);
    };
};

class BasePlate : public QDialog, private Ui::BasePlate
{
    Q_OBJECT
public:
    explicit BasePlate(QWidget *parent = nullptr);
    BasePlateInfo RunDialog(const BasePlateInfo &info);
private slots:
    void basePlateChanged(QString);
    void offsetChanged(QString);

private:
    void UpdateInfoBox();

    QValidator *m_validator;
    BasePlateInfo m_retInfo;

};


#endif // BASEPLATE_H
