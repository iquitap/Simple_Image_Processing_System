#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QImage>
#include <QtPlugin>
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
        Image = imread(fileName.toLatin1().data());
    if(!Image.data)
    {
        return;
    }
    else
    {
        cvtColor(Image,TempImage,CV_BGR2RGB);
        img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
        ui->label->clear();
        ui->label->setPixmap(QPixmap::fromImage(img));
        ui->label->resize(ui->label->pixmap()->size());

        //namedWindow("Original Image");
        //imshow("Original Image",Image);
    }

}

void MainWindow::on_actionExit_triggered()
{
    close() ;
}

void MainWindow::on_actionFlip_horizontal_triggered()
{
    CaseNumber = -1;
    if(!Image.data) { return;}
    flip(Image, Image, 1);
    cvtColor(Image,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", Image);
}

void MainWindow::on_actionFlip_vertical_triggered()
{
    CaseNumber = -1;
    if(!Image.data) { return;}
    flip(Image, Image, 0);
    cvtColor(Image,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", Image);
}

void MainWindow::on_actionSave_Image_triggered()
{
    if(!TempImage.data) { return ;}
    img.save("Image.jpg");
}

void MainWindow::on_actionTurn_left_triggered()
{
    CaseNumber = -1;
    if(!Image.data) { return;}
    transpose(Image, Image);
    flip(Image, Image, 0);
    cvtColor(Image,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->clear();
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());

    //namedWindow("Output Image");
    //imshow("Output Image", Image);
}

void MainWindow::on_actionTurn_right_triggered()
{
    CaseNumber = -1;
    if(!Image.data) { return;}
    transpose(Image, Image);
    flip(Image, Image, 1);
    cvtColor(Image,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->clear();
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());

    //namedWindow("Output Image");
    //imshow("Output Image", Image);
}

void MainWindow::on_actionBoxFilter_triggered()
{
    CaseNumber = 1;
    boxFilter(Image, TempImage, -1, Size(OperateValue + 1, OperateValue + 1));
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    OperateValue = value;
    if(!Image.data) {return;}
    switch(CaseNumber)
    {
        case 1:boxFilter(Image, TempImage, -1, Size(OperateValue + 1, OperateValue + 1));break;
        case 2:blur(Image, TempImage, Size(OperateValue + 1, OperateValue + 1), Point(-1, -1));break;
        case 3:GaussianBlur(Image, TempImage, Size(OperateValue * 2 + 1, OperateValue * 2 + 1), 0, 0);break;
        case 4:medianBlur(Image, TempImage, OperateValue * 2 + 1);break;
        case 5:bilateralFilter(Image, TempImage, OperateValue, OperateValue * 2, OperateValue / 2);break;
        case 6:element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
               erode(Image, TempImage, element);break;
        case 7:element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
               dilate(Image, TempImage, element);break;
        case 8:element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
               morphologyEx(Image,TempImage, MORPH_OPEN, element); break;
        case 9:element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
               morphologyEx(Image,TempImage, MORPH_CLOSE, element); break;
        case 10:element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
                morphologyEx(Image,TempImage, MORPH_GRADIENT, element); break;
        case 11:element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
                morphologyEx(Image,TempImage, MORPH_TOPHAT, element); break;
        case 12:element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
                morphologyEx(Image,TempImage, MORPH_BLACKHAT, element); break;
        case 13:ResizeFlag = (OperateValue>49)?1:0;
                if(ResizeFlag)  cv::resize(Image,TempImage,Size( Image.cols*(OperateValue-49), Image.rows*(OperateValue-49) ),(0,0),(0,0));
                else    cv::resize(Image,TempImage,Size( Image.cols/(50-OperateValue), Image.rows/(50-OperateValue) ),(0,0),(0,0));break;
        default:return;
    }


    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionMeanBlur_triggered()
{
    CaseNumber = 2;
    blur(Image, TempImage, Size(OperateValue + 1, OperateValue + 1), Point(-1, -1));
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionGaussianBlur_triggered()
{
    CaseNumber = 3;
    GaussianBlur(Image, TempImage, Size(OperateValue * 2 + 1, OperateValue * 2 + 1), 0, 0);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionMedianBlur_triggered()
{
    CaseNumber = 4;
    medianBlur(Image, TempImage, OperateValue * 2 + 1);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionBilateralFilter_triggered()
{
    CaseNumber = 5;
    bilateralFilter(Image, TempImage, OperateValue, OperateValue * 2, OperateValue / 2);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionErode_triggered()
{
    CaseNumber = 6;
    element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
    erode(Image, TempImage, element);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionDilate_triggered()
{
    CaseNumber = 7;
    element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
    dilate(Image, TempImage, element);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_radioButton_clicked()
{
    ElementShape = MORPH_RECT;
}

void MainWindow::on_radioButton_2_clicked()
{
    ElementShape = MORPH_RECT;
}

void MainWindow::on_radioButton_3_clicked()
{
    ElementShape = MORPH_CROSS;
}

void MainWindow::on_actionOpen_triggered()
{
    CaseNumber = 8;
    element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
    morphologyEx(Image,TempImage, MORPH_OPEN, element);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionClose_triggered()
{
    CaseNumber = 9;
    element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
    morphologyEx(Image,TempImage, MORPH_CLOSE, element);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionMorphological_Gradient_triggered()
{
    CaseNumber = 10;
    element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
    morphologyEx(Image,TempImage, MORPH_GRADIENT, element);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionTop_Hat_triggered()
{
    CaseNumber = 11;
    element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
    morphologyEx(Image,TempImage, MORPH_TOPHAT, element);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionBlack_Hat_triggered()
{
    CaseNumber = 12;
    element = getStructuringElement(ElementShape, Size(2 * OperateValue + 1, 2 * OperateValue + 1), Point(OperateValue, OperateValue));
    morphologyEx(Image,TempImage, MORPH_BLACKHAT, element);
    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionResize_triggered()
{
    CaseNumber = 13;
    ResizeFlag = (OperateValue>49)?1:0;
    if(ResizeFlag)
        cv::resize(Image,TempImage,Size( Image.cols*(OperateValue-49), Image.rows*(OperateValue-49) ),(0,0),(0,0));
    else
        cv::resize(Image,TempImage,Size( Image.cols/(50-OperateValue), Image.rows/(50-OperateValue) ),(0,0),(0,0));

    cvtColor(TempImage,TempImage,CV_BGR2RGB);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows, TempImage.cols*Image.channels(),  QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);
}

void MainWindow::on_actionGray_triggered()
{
    CaseNumber = -1;
    cvtColor(Image,TempImage,CV_RGB2GRAY);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows,TempImage.cols*TempImage.channels(),  QImage::Format_Grayscale8);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_actionCanny_triggered()
{
    CaseNumber = -1;
    cvtColor(Image,TempImage,CV_BGR2GRAY);
    blur(TempImage,TempImage,Size(3,3));//降噪
    Canny(TempImage,TempImage,0,30,3);
    img = QImage((const unsigned char*)(TempImage.data),TempImage.cols,TempImage.rows,  QImage::Format_Grayscale8);
    ui->label->setPixmap(QPixmap::fromImage(img));

    //namedWindow("Output Image");
    //imshow("Output Image", TempImage);

}
