#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include "oglwidget.h"
#include <string>
#include <sstream>
#include <vector>
#include <locale.h>
/*namespace Ui {
class MainWindow;
}*/

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openUSAMap();
private:
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }


    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    QWidget *centralWidget;
    QMenu *fileMenu;
    QAction *openFile;
    QFileDialog *fileDialog;
    OglWidget *oglWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *oglWidgetLayout;

    void setupLayout();
    void setupMenuBar();

    void openGraphFile(QString path);

private slots:
    void openFileDialog();
};

#endif // MAINWINDOW_H
