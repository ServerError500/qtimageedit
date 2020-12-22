#include "basicadt.h"

BasicAdt::BasicAdt()
{

}
//亮度调整
QImage AdjustBrightness(QImage Img, int iBrightValue)
{
    int red, green, blue;
    int pixels = Img.width() * Img.height();
    unsigned int *data = (unsigned int *)Img.bits();

    for (int i = 0; i < pixels; ++i)
    {
        red= qRed(data[i])+ iBrightValue;
        red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
        green= qGreen(data[i]) + iBrightValue;
        green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
        blue= qBlue(data[i]) + iBrightValue;
        blue =  (blue  < 0x00) ? 0x00 : (blue  > 0xff) ? 0xff : blue ;
        data[i] = qRgba(red, green, blue, qAlpha(data[i]));
    }

    return Img;
}
//对比度调整
QImage AdjustContrast(QImage Img, int iContrastValue)
{
    int pixels = Img.width() * Img.height();
    unsigned int *data = (unsigned int *)Img.bits();

    int red, green, blue, nRed, nGreen, nBlue;

    if (iContrastValue > 0 && iContrastValue < 100)
    {
        float param = 1 / (1 - iContrastValue / 100.0) - 1;

        for (int i = 0; i < pixels; ++i)
        {
            nRed = qRed(data[i]);
            nGreen = qGreen(data[i]);
            nBlue = qBlue(data[i]);

            red = nRed + (nRed - 127) * param;
            red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
            green = nGreen + (nGreen - 127) * param;
            green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
            blue = nBlue + (nBlue - 127) * param;
            blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;

            data[i] = qRgba(red, green, blue, qAlpha(data[i]));
        }
    }
    else
    {
        for (int i = 0; i < pixels; ++i)
        {
            nRed = qRed(data[i]);
            nGreen = qGreen(data[i]);
            nBlue = qBlue(data[i]);

            red = nRed + (nRed - 127) * iContrastValue / 100.0;
            red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
            green = nGreen + (nGreen - 127) * iContrastValue / 100.0;
            green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
            blue = nBlue + (nBlue - 127) * iContrastValue / 100.0;
            blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;

            data[i] = qRgba(red, green, blue, qAlpha(data[i]));
        }
    }

    return Img;
}

QImage AdjustSaturation(QImage Img, int iSaturateValue)
{
    int red, green, blue, nRed, nGreen, nBlue;
    int pixels = Img.width() * Img.height();
    unsigned int *data = (unsigned int *)Img.bits();

    float Increment = iSaturateValue/100.0;

    float delta = 0;
    float minVal, maxVal;
    float L, S;
    float alpha;

    for (int i = 0; i < pixels; ++i)
    {
        nRed = qRed(data[i]);
        nGreen = qGreen(data[i]);
        nBlue = qBlue(data[i]);

        minVal = std::min(std::min(nRed, nGreen), nBlue);
        maxVal = std::max(std::max(nRed, nGreen), nBlue);
        delta = (maxVal - minVal) / 255.0;
        L = 0.5*(maxVal + minVal) / 255.0;
        S = std::max(0.5*delta / L, 0.5*delta / (1 - L));

        if (Increment > 0)
        {
            alpha = std::max(S, 1 - Increment);
            alpha = 1.0 / alpha - 1;
            red = nRed + (nRed - L*255.0)*alpha;
            red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
            green = nGreen + (nGreen - L*255.0)*alpha;
            green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
            blue = nBlue + (nBlue - L*255.0)*alpha;
            blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;
        }
        else
        {
            alpha = Increment;
            red = L*255.0 + (nRed - L * 255.0)*(1+alpha);
            red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
            green = L*255.0 + (nGreen - L * 255.0)*(1+alpha);
            green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
            blue = L*255.0 + (nBlue - L * 255.0)*(1+alpha);
            blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;
        }

        data[i] = qRgba(red, green, blue, qAlpha(data[i]));
    }

    return Img;
}
//二值化
QImage AdjustTwoValued(QImage img,int iTwoValued)
{
          QSize size = img.size();
          QImage binaryImage(size, QImage::Format_RGB32);
          int width = size.width();
          int height = size.height();
          for(int i = 0; i < width; i++)
            for(int j = 0; j < height; j++)
            {
              QRgb pixel = img.pixel(i, j);
              int r = qRed(pixel) * 0.3;
              int g = qGreen(pixel) * 0.59;
              int b = qBlue(pixel) * 0.11;
              int rgb = r + g + b;//先把图像灰度化，转化为灰度图像
              if (rgb > iTwoValued)//然后按某一阀值进行二值化
              {
                rgb = 255;
              }else
              {
                rgb = 0;
              }
              QRgb newPixel = qRgb(rgb, rgb, rgb);
              binaryImage.setPixel(i, j, newPixel);
            }
        return binaryImage;
}

