#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "converter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTopChanged();
    void onBottomChanged();
    void updateCurrentTab();

private:
    Ui::MainWindow *ui;
    void setupLogic();
    void doConvert(bool topToBottom);
};
#endif
