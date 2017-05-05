#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2\opencv.hpp>
#include <highgui.h>
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <QDebug>
#include <QFileDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionOpen_Image_triggered();

    void on_actionExit_triggered();


    void on_actionFlip_horizontal_triggered();

    void on_actionFlip_vertical_triggered();

    void on_actionSave_Image_triggered();

    void on_actionTurn_left_triggered();

    void on_actionTurn_right_triggered();

    void on_actionBoxFilter_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void on_actionMeanBlur_triggered();

    void on_actionGaussianBlur_triggered();

    void on_actionMedianBlur_triggered();

    void on_actionBilateralFilter_triggered();

    void on_actionErode_triggered();

    void on_actionDilate_triggered();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_actionOpen_triggered();

    void on_actionClose_triggered();

    void on_actionMorphological_Gradient_triggered();

    void on_actionTop_Hat_triggered();

    void on_actionBlack_Hat_triggered();

    void on_actionResize_triggered();

    void on_actionGray_triggered();


    void on_actionCanny_triggered();

private:
    Ui::MainWindow *ui;
    cv::Mat Image,TempImage,element;
    QImage img;
    int OperateValue = 0;
    int CaseNumber = -1;
    int ElementShape = 0;
    int ResizeFlag;
};

#endif // MAINWINDOW_H
