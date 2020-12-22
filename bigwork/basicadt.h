#ifndef BASICADT_H
#define BASICADT_H
#include <QImage>

class BasicAdt
{
public:
    BasicAdt();
    QImage AdjustBrightness(QImage Img, int iBrightValue);//亮度
    QImage AdjustContrast(QImage Img, int iContrastValue);//对比度
    QImage AdjustSaturation(QImage Img, int iSaturateValue);//饱和度
    QImage AdjustTwoValued(QImage img,int iTwoValued);//二值化

};

#endif // BASICADT_H
