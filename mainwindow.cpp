#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <stdio.h>
#include "zoomgraphicsview.h"
#include <math.h>
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ImageItem(NULL)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    connect(ui->graphicsView, SIGNAL(mouseCoordChanged(int,int, float)), this, SLOT(updateCoords(int,int, float)));
    connect(ui->graphicsView, SIGNAL(mouseHitPoint(int,int,int)), this, SLOT(hitCircle(int, int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_New_Image_triggered()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, "Open New Image File", tr("/home"), tr("Image Files (*.png *.jpg *.bmp)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

void MainWindow::on_actionExit_triggered()
{
    // check is there's something to save
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "Test", tr("Image Viewer and Inspector\n by GRAM  (C)2017"));
}

void MainWindow::updateCoords(int iX, int iY, float fZoomFactor)
{
    QString szInfo = QString("x = %1, y = %2\nZoom = %3") .arg(iX).arg(iY).arg(fZoomFactor, 0, 'f', 3);
    ui->textBrowser->setText(szInfo);
}


/**
 * private methods
 *
 */
int MainWindow::maybeSave()
{
    return TRUE;
}

int MainWindow::loadFile(QString szFileName)
{
    int iRet = TRUE;
    if (!szFileName.isEmpty())
    {
        image = QImage(szFileName);
        if (image.isNull())
        {
            QMessageBox::information(this, tr("Image Viewer"), tr("Cannot load %1.").arg(szFileName));
            iRet = FALSE;
        }
        else
        {
            // update filename in text label
            ui->lblFileName->setText(szFileName);
            QString szFileInfo;
            szFileInfo = QString("Image size: x = %1  y = %2").arg(image.width()).arg(image.height());

            ui->lblFileInfo->setText(szFileInfo);

            dirtyPixmap(&image);



            scene.clear();
            scene.setSceneRect(0, 0, image.width(), image.height());
            ImageItem = scene.addPixmap(QPixmap::fromImage(image));
            scene.update();

            ui->graphicsView->resetZoom();

        }
    }
    return iRet;
}

int MainWindow::dirtyPixmap(QImage *pixMap)
{
    if(!pixMap)
    {
        return FALSE;
    }

    int iType = pixMap->depth();

    for(int i = 0; i < 720; i++)
    {
        pixMap->setPixel(100 + 40*cos(i/180.0*3.1415*0.5), 100 + 40*sin(i/180.0*3.1415*0.5), 0xFF0000);
    }

    scene.update();
    return TRUE;
}


void MainWindow::hitCircle(int iX, int iY, int iAction)
{
    //QGraphicsPixmapItem *item =  ui->graphicsView->itemAt(iX, iY);
    if(!image.isNull())
    {

        for(int i = 0; i < 720; i++)
        {
            image.setPixel(iX + 40*cos(i/180.0*3.1415*0.5), iY + 40*sin(i/180.0*3.1415*0.5), 0xFF0000);
        }

        ImageItem->setPixmap(QPixmap::fromImage(image));
        scene.update();
    }
    else
        return;
}

void MainWindow::on_actionZoom_Reset_triggered()
{
    ui->graphicsView->resetZoom();
}
