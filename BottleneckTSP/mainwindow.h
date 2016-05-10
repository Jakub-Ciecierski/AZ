#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include "oglwidget.h"

/*namespace Ui {
class MainWindow;
}*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *centralWidget;
    QMenu *fileMenu;
    QAction *openFile;
    QFileDialog *fileDialog;
    OglWidget *oglWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *oglWidgetLayout;

    void setupLayout();
    void setupMenuBar();

private slots:
    void openFileDialog();
};

#endif // MAINWINDOW_H
