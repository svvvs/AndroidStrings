#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QDirIterator>
#include <QThread>

#include "androidstring.h"
#include "androidstringmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int parserRun();

private slots:
    void on_parseButton_clicked();
    void on_sourceButton_clicked();
    void on_excludeButton_clicked();
    void on_overlayButton_clicked();
    void on_exportButton_clicked();

    void handleResults(const int &result);

private:
    Ui::MainWindow *ui;

    void selectDirectory(QLineEdit *line);
    void updateTreeWidget();
    QDirIterator *newDirIterator(QDir &source);
    void updateList(QList<AndroidString*> *list,
                    QLineEdit *source, QLineEdit *exclude = NULL);
    void overloadList();
    void updateUI(const bool enable);

    QList<AndroidString*> mList;
    AndroidStringModel *mModel;
};

class ParseThread : public QThread
{
    Q_OBJECT

public:
    ParseThread(MainWindow *win);
    void run();

private:
    MainWindow *mMainWindow;

signals:
    void resultReady(const int &result);
};

#endif // MAINWINDOW_H
