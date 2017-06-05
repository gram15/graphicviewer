#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgraphicsscene.h>

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
    void on_actionOpen_New_Image_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionZoom_Reset_triggered();



    void updateCoords(int iX, int iY, float fZoomFactor);
    void hitCircle(int iX, int iY, int iAction);


private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    QImage image;
    QGraphicsPixmapItem *ImageItem;


private: //methods
    int maybeSave();
    int loadFile(QString szFileName);

    int dirtyPixmap(QImage *pixMap);
};

#endif // MAINWINDOW_H
