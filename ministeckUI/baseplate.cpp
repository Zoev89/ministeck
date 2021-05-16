#include "baseplate.h"
#include <iostream>
#include <sstream>

BasePlate::BasePlate(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    QRegularExpression rx("\\d{1,4}[x]\\d{1,4}");
    m_validator = new QRegularExpressionValidator(rx, this);
    standaardGeometry->setValidator(m_validator);
    leftTop->setValidator(m_validator);
}

BasePlateInfo BasePlate::RunDialog(const BasePlateInfo&info)
{
    // regexp: optional '-' followed by between 1 and 3 digits

    m_retInfo=info;
    QStringList items={"16x32", "32x16","32x32","32x48","48x32","64x80","80x64","128x160","160x128"};
    int index = -1;
    if ((info.baseplateWidth >1) && (info.baseplateHeight >1))
    {
        QString item=(std::to_string(info.baseplateWidth) + 'x' + std::to_string(info.baseplateHeight)).c_str();
        for (int i=0;i<items.size();i++)
        {
            if (items[i] == item)
            {
                index = i;
            }
        }
        if (index== -1)
        {
            index = items.size();
            items.append(item);
        }
    }
    standaardGeometry->setEditable(true);
    standaardGeometry->addItems(items);

    if (index>= 0)
    {
        standaardGeometry->setCurrentIndex(index);
    }

    auto ret = exec();
    m_retInfo.changed = (m_retInfo == info);
    return (ret == 1) ? m_retInfo: info;
}

void BasePlate::UpdateInfoBox()
{
    int decimation = std::min((m_retInfo.imageWidth-m_retInfo.imageOffsetX)/m_retInfo.baseplateWidth,
                              (m_retInfo.imageHeight-m_retInfo.imageOffsetY)/m_retInfo.baseplateHeight);
    decimationFactor->setText(std::to_string(decimation).c_str());
    widthHeight->setText((std::to_string(m_retInfo.imageWidth)+ "x" + std::to_string(m_retInfo.imageHeight)).c_str());
    rightBottom->setText((std::to_string(m_retInfo.imageOffsetX+m_retInfo.baseplateWidth*decimation)+ "x" + std::to_string(m_retInfo.imageOffsetY + m_retInfo.baseplateHeight*decimation)).c_str());
    leftTop->setText((std::to_string(m_retInfo.imageOffsetX)+ "x" + std::to_string(m_retInfo.imageOffsetY)).c_str());
}

void BasePlate::basePlateChanged(QString newValue)
{
    int pos=0;
    if (m_validator->validate(newValue, pos) == QValidator::State::Acceptable)
    {
        std::stringstream stream ( newValue.toStdString());
        stream >> m_retInfo.baseplateWidth;
        char x;
        stream >> x;
        stream >> m_retInfo.baseplateHeight;
        UpdateInfoBox();
    }
}

void BasePlate::offsetChanged(QString newValue)
{
    int pos=0;
    if (m_validator->validate(newValue, pos) == QValidator::State::Acceptable)
    {
        std::stringstream stream ( newValue.toStdString());
        stream >> m_retInfo.imageOffsetX;
        char x;
        stream >> x;
        stream >> m_retInfo.imageOffsetY;
        UpdateInfoBox();
    }
}

