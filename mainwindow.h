#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include "BigInt.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void calculate();

private:
    QLineEdit *input1;
    QLineEdit *input2;
    QComboBox *operation;
    QPushButton *calcButton;
    QLineEdit *resultDisplay;
};

#endif