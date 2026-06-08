#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    input1 = new QLineEdit(this);
    input1->setPlaceholderText("Enter number");

    operation = new QComboBox(this);
    operation->addItem("+");
    operation->addItem("-");
    operation->addItem("*");

    input2 = new QLineEdit(this);
    input2->setPlaceholderText("Enter another number");

    calcButton = new QPushButton("Calculate", this);

    resultDisplay = new QLineEdit(this);
    resultDisplay->setReadOnly(true);
    resultDisplay->setPlaceholderText("Result");

    layout->addWidget(input1);
    layout->addWidget(operation);
    layout->addWidget(input2);
    layout->addWidget(calcButton);
    layout->addWidget(resultDisplay);

    setCentralWidget(centralWidget);
    setWindowTitle("BigInt Calculator");
    resize(400, 250);

    connect(calcButton, &QPushButton::clicked, this, &MainWindow::calculate);
}

void MainWindow::calculate()
{
    try
    {

        std::string str1 = input1->text().toStdString();
        std::string str2 = input2->text().toStdString();

        if (str1.empty() || str2.empty())
            return;

        BigInt num1(str1);
        BigInt num2(str2);
        BigInt result;

        QString op = operation->currentText();
        if (op == "+")
        {
            result = num1 + num2;
        }
        else if (op == "-")
        {
            result = num1 - num2;
        }
        else if (op == "*")
        {
            result = num1 * num2;
        }

        std::stringstream ss;
        ss << result;

        resultDisplay->setText(QString::fromStdString(ss.str()));
    }
    catch (const std::invalid_argument &)
    {

        QMessageBox::critical(this, "Err", "Wrong input format.Numbers only");
    }
}