#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "basicadt.h"
#include<QTranslator>
#include<QGraphicsBlurEffect>
#include<QScreen>
QImage AdjustBrightness(QImage Img, int iBrightValue);
QImage AdjustContrast(QImage Img, int iContrastValue);
QImage AdjustSaturation(QImage Img, int iSaturateValue);
QImage AdjustTwoValued(QImage img,int iTwoValued);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle(tr("IMG Processing"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//打开图片
void MainWindow::on_openfile_triggered()
{
    ui->label->clear();//先清除label内容
        //打开图片操作
        QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open image file"),
                    "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));

        if(fileName.isEmpty())
        {
            QMessageBox mesg;
            mesg.warning(this,tr("Waring"),tr("Open Image Failure!"));
            return;
        }
        else
        {
            QImage img(fileName);
            img=img.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
            ui->label->setPixmap(QPixmap::fromImage(img));
            if(img.isNull())
            {
                QMessageBox::information(this,tr("Information"),tr("Open Image Failure"));
            }
            else
            {
                globalMark=1;
                globalImg=img;
            }
        }
         ui->label->setAlignment(Qt::AlignCenter);
}
void MainWindow::on_action_Ctrl_O_triggered()
{
    ui->label->clear();

        QString fileName = QFileDialog::getOpenFileName(
                    this, tr("open image file"),
                    "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));

        if(fileName.isEmpty())
        {
            QMessageBox mesg;
            mesg.warning(this,tr("Waring"),tr("Open Image Failure!"));
            return;
        }
        else
        {
            QImage img(fileName);
            img=img.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);//Qt::KeepAspectRatio自适应大小，不变形
            ui->label->setPixmap(QPixmap::fromImage(img));
            if(img.isNull())
            {
                QMessageBox::information(this,tr("Information"),tr("Open Image Failure"));
            }
            else
            {
                globalMark=1;
                globalImg=img;
            }
        }
         ui->label->setAlignment(Qt::AlignCenter);
}
//保存图片
void MainWindow::on_savefile_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
            QScreen *screen = QGuiApplication::primaryScreen();
            screen->grabWindow(ui->label->winId()).save(filename);
}
void MainWindow::on_action_Ctrl_S_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
            QScreen *screen = QGuiApplication::primaryScreen();
            screen->grabWindow(ui->label->winId()).save(filename);
}
//slide
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    QImage img;
    int x = abs(position-twoposition);;
    if(twoposition<position){
        img = AdjustBrightness(globalImg, x);
    }else{
        img = AdjustBrightness(globalImg, -x);
    }
    twoposition = position;
    ui->label->setPixmap(QPixmap::fromImage(img));
    globalImg = img;
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    QImage img;
    img = AdjustContrast(globalImg, position);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    QImage img;
    img = AdjustSaturation(globalImg, position);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_horizontalSlider_7_sliderMoved(int position)
{
    QImage img;
    img = AdjustTwoValued(globalImg, position);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_horizontalSlider_8_sliderMoved(int position)
{

}

//button
void MainWindow::on_pushButton_7_clicked()
{
    QImage* img=new QImage;
       *img=ui->label->pixmap()->toImage();
       QImage* imgRotate = new QImage;
       QMatrix matrix;
       matrix.rotate(270);
       *imgRotate = img->transformed(matrix);
       ui->label->setPixmap(QPixmap::fromImage(*imgRotate));
}

void MainWindow::on_pushButton_8_clicked()
{
    QImage* img=new QImage;
        *img=ui->label->pixmap()->toImage();
        QImage* imgRotate = new QImage;
        QMatrix matrix;
        matrix.rotate(90);
        *imgRotate = img->transformed(matrix);
        ui->label->setPixmap(QPixmap::fromImage(*imgRotate));
}

void MainWindow::on_pushButton_clicked()
{
    QImage* img=new QImage;
        *img=ui->label->pixmap()->toImage();
        QImage mirroredImage = img->mirrored(true, true);
        QPixmap pixmap = QPixmap::fromImage(mirroredImage);
         ui->label->setPixmap(QPixmap::fromImage(mirroredImage));
}

void MainWindow::on_pushButton_2_clicked()
{
    QImage* img=new QImage;
        *img=ui->label->pixmap()->toImage();
        QImage mirroredImage = img->mirrored(true, false);
        QPixmap pixmap = QPixmap::fromImage(mirroredImage);
         ui->label->setPixmap(QPixmap::fromImage(mirroredImage));
}

void MainWindow::on_pushButton_3_clicked()
{
    QImage* img=new QImage;
        *img=ui->label->pixmap()->toImage();
        qreal width = img->width();
        qreal height = img->height();
        QImage *pix=new QImage;
        *pix = img->scaled(width*2,height*2,Qt::KeepAspectRatio);
        ui->label->setPixmap(QPixmap::fromImage(*pix));
}

void MainWindow::on_pushButton_4_clicked()
{
    QImage* img=new QImage;
        *img=ui->label->pixmap()->toImage();
        qreal width = img->width();
        qreal height = img->height();
        QImage *pix=new QImage;
        *pix = img->scaled(width/2,height/2,Qt::KeepAspectRatio);
        ui->label->setPixmap(QPixmap::fromImage(*pix));
}

void MainWindow::on_pushButton_5_clicked()
{
 ui->label->adjustSize();
}

void MainWindow::on_pushButton_6_clicked()
{
ui->label->clear();
}
//window
void MainWindow::on_action_5_triggered()
{
    ui->dockWidget->show();
}

void MainWindow::on_action_6_triggered()
{
    ui->dockWidget_3->show();
}

void MainWindow::on_action_7_triggered()
{
    ui->dockWidget_5->show();
}

void MainWindow::on_action_8_triggered()
{
    QImage* img=new QImage;
        *img=ui->label->pixmap()->toImage();
    int height = img->height();
        int width = img->width();
        QImage ret(width, height, QImage::Format_Indexed8);
        ret.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            ret.setColor(i, qRgb(i, i, i));
        }
        switch(img->format())
        {
        case QImage::Format_Indexed8:
            /*for(int i = 0; i < height; i ++)
            {
                const uchar *pSrc = (uchar *)image->constScanLine(i);
                uchar *pDest = (uchar *)ret.scanLine(i);
                memcpy(pDest, pSrc, width);
            } */
            break;
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
            for(int i = 0; i < height; i ++)
            {
                const QRgb *pSrc = (QRgb *)img->constScanLine(i);
                uchar *pDest = (uchar *)ret.scanLine(i);

                for( int j = 0; j < width; j ++)
                {
                     pDest[j] = qGray(pSrc[j]);
                }
            }
            break;
        }
        ui->label->setPixmap(QPixmap::fromImage(ret));
}
void MainWindow::on_action_English_triggered()
{
       QTranslator translator;
       translator.load(":/translator/translator/Lidar_en.qm");
       qApp->installTranslator(&translator);
       ui->retranslateUi(this);

}

void MainWindow::on_action_4_triggered()
{
    QTranslator translator;
    translator.load(":/translator/translator/Lidar_zh.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void MainWindow::on_horizontalSlider_4_sliderMoved(int position)
{

}
