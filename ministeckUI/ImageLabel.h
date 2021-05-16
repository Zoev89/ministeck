#ifndef IMAGELABEL_H
#define IMAGELABEL_H
#include "QLabel"
#include "QPixmap"
#include <memory>
#include "QResizeEvent"
#include <iostream>

QT_BEGIN_NAMESPACE

class Q_WIDGETS_EXPORT ImageLabel: public QLabel
{
public:
    ImageLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags())
        :QLabel(parent,f)
    {

    }

    void setOriginalPixmap(std::unique_ptr<QPixmap> pixmap)
    {
        m_originalPixmap = std::move(pixmap);
        setScaledPixmap();
    }

    void resizeEvent (QResizeEvent *event) override
    {
        setScaledPixmap();
    }

    void setScaledPixmap (void)
    {
        if (m_originalPixmap)
        {
            auto scaledPixmap = m_originalPixmap->scaled(width(), height(), Qt::KeepAspectRatio, Qt::FastTransformation);
            setPixmap(scaledPixmap);
        }
    }
    ~ImageLabel()
    {
    }

private:
    std::unique_ptr<QPixmap> m_originalPixmap;

};

QT_END_NAMESPACE

#endif // IMAGELABEL_H
