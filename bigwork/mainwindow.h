#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QString>
#include <QMainWindow>
#include "basicadt.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTime>
#include <QDir>
#include <QFile>
#include <QIcon>
#include <QImage>
#include <QMatrix>
#include <QSpinBox>
#include <math.h>
#include <QSlider>
namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int globalMark;
    QImage globalImg;
private slots:

    void on_openfile_triggered();

    void on_savefile_triggered();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

    void on_horizontalSlider_7_sliderMoved(int position);


    void on_action_English_triggered();

    void on_action_4_triggered();


    void on_horizontalSlider_8_sliderMoved(int position);

    void on_action_Ctrl_O_triggered();

    void on_action_Ctrl_S_triggered();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

    void on_action_8_triggered();

    void on_horizontalSlider_4_sliderMoved(int position);

protected:
    int twoposition=0;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
