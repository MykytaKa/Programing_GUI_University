#include "widget.h"
#include "consts.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(600, 400);

    radioLayout = new QVBoxLayout(this);

    radioGroup = new QGroupBox(this);
    radioGroup->resize(200, 80);
    radioGroup->move(80, 300);


    leftEdit = new QLineEdit(this);
    leftEdit->resize(50, 20);
    leftEdit->move(205, 150);
    rightEdit = new QLineEdit(this);
    rightEdit->resize(50, 20);
    rightEdit->move(455, 150);
    rightEdit->setReadOnly(true);

    bt1 = new QRadioButton("Length");
    bt2 = new QRadioButton("Weight");
    bt3 = new QRadioButton("Area");

    radioManager= new QButtonGroup(this);
    radioManager->addButton(bt1);
    radioManager->addButton(bt2);
    radioManager->addButton(bt3);

    invertButton = new QCheckBox(this);
    invertButton->resize(20, 20);
    invertButton->move(348, 100);

    convertDirectionText = new QLabel("->", this);
    convertDirectionText->move(290, 150);
    invertText = new QLabel("Invert conversion direction", this);
    invertText->move(200, 100);

    clearButton = new QPushButton("Clear", this);
    clearButton->move(420, 200);
    convertButton = new QPushButton("Convert", this);
    convertButton->move(257, 200);

    textSizeBar = new QProgressBar(this);
    textSizeBar->setTextVisible(false);
    textSizeBar->setValue(1);
    textSizeBar->setRange(1, 10);
    textSizeBar->resize(170, 20);
    textSizeBar->move(420, 280);

    textSizeManager = new QSpinBox(this);
    textSizeManager->setValue(1);
    textSizeManager->setRange(1, 10);
    textSizeManager->move(550, 250);

    leftBox = new QComboBox(this);
    leftBox->resize(120, 20);
    leftBox->move(80, 150);
    rightBox = new QComboBox(this);
    rightBox->resize(120, 20);
    rightBox->move(330, 150);

    radioLayout->addWidget(bt1);
    radioLayout->addWidget(bt2);
    radioLayout->addWidget(bt3);

    radioGroup->setLayout(radioLayout);

    inputEdit = leftEdit;
    inputBox = leftBox;
    outputEdit = rightEdit;
    outputBox = rightBox;

    connect(textSizeManager, SIGNAL(valueChanged(int)), this, SLOT(changeWidgetsSize(int)));
    connect(invertButton, SIGNAL(stateChanged(int)), this, SLOT(changeConvertDirection(int)));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearEdits()));
    connect(radioManager, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(fillBoxes(QAbstractButton*)));
    connect(convertButton, SIGNAL(clicked()), this, SLOT(convertValue()));
}

Widget::~Widget()
{
}

void Widget::changeConvertDirection(int buttonState)
{
    if (buttonState == 2)
    {
        inputEdit = rightEdit;
        inputBox = rightBox;
        outputEdit = leftEdit;
        outputBox = leftBox;
        convertDirectionText->setText("<-");
        leftEdit->setReadOnly(true);
        rightEdit->setReadOnly(false);
    }
    else
    {
        inputEdit = leftEdit;
        inputBox = leftBox;
        outputEdit = rightEdit;
        outputBox = rightBox;
        convertDirectionText->setText("->");
        rightEdit->setReadOnly(true);
        leftEdit->setReadOnly(false);
    }
}

void Widget::clearEdits()
{
    leftEdit->setText("");
    rightEdit->setText("");
    invertButton->setChecked(false);
    convertDirectionText->setText("->");
}

void Widget::fillBoxes(QAbstractButton *button)
{
    leftBox->clear();
    rightBox->clear();
    if(button->text() == "Length")
    {
        leftBox->addItems(lengthArray);
        rightBox->addItems(lengthArray);
    }
    else if(button->text() == "Weight")
    {
        leftBox->addItems(weightArray);
        rightBox->addItems(weightArray);
    }
    else if(button->text() == "Area")
    {
        leftBox->addItems(areaArray);
        rightBox->addItems(areaArray);
    }
}

void Widget::convertValue()
{
    if(bt1->isChecked())
        outputEdit->setText(QString::number(convertLength(inputBox->currentText(),
                                                          inputEdit->text().toDouble(),
                                                          outputBox->currentText())));
    else if(bt2->isChecked())
        outputEdit->setText(QString::number(convertWeight(inputBox->currentText(),
                                                          inputEdit->text().toDouble(),
                                                          outputBox->currentText())));
    else if(bt3->isChecked())
        outputEdit->setText(QString::number(convertArea(inputBox->currentText(),
                                                          inputEdit->text().toDouble(),
                                                        outputBox->currentText())));
}

void Widget::changeWidgetsSize(int value)
{
    QFont font = leftEdit->font();
    if(value > textSizeBar->value())
    {
        font.setPointSize(font.pointSize()+value);

        leftEdit->resize(leftEdit->width()+value,
                         leftEdit->height()+value);
        leftEdit->setFont(font);
        rightEdit->resize(rightEdit->width()+value,
                         rightEdit->height()+value);
        rightEdit->setFont(font);
        leftBox->resize(leftBox->width()+value,
                        leftBox->height()+value);
        leftBox->setFont(font);
        rightBox->resize(rightBox->width()+value,
                         rightBox->height()+value);
        rightBox->setFont(font);
    }
    else
    {
        font.setPointSize(font.pointSize()-value-1);

        leftEdit->resize(leftEdit->width()-value-1,
                         leftEdit->height()-value-1);
        leftEdit->setFont(font);

        rightEdit->resize(rightEdit->width()-value-1,
                         rightEdit->height()-value-1);
        rightEdit->setFont(font);

        leftBox->resize(leftBox->width()-value-1,
                        leftBox->height()-value-1);
        leftBox->setFont(font);

        rightBox->resize(rightBox->width()-value-1,
                         rightBox->height()-value-1);
        rightBox->setFont(font);
    }
    textSizeBar->setValue(value);
}

double Widget::convertWeight(QString inputCurrency = NULL, double inputValue = 0.0, QString outputCurrency = NULL)
{
    if(inputCurrency == outputCurrency)
        return inputValue;
    if(inputCurrency == "gram")
    {
        if(outputCurrency == "kilogram")
            return inputValue / 1000.0;
        if(outputCurrency == "tonne")
            return inputValue / 1000000.0;
    }
    if(inputCurrency == "kilogram")
    {
        if(outputCurrency == "gram")
            return inputValue * 1000.0;
        if(outputCurrency == "tonne")
            return inputValue / 1000.0;
    }
    if(inputCurrency == "tonne")
    {
        if(outputCurrency == "gram")
            return inputValue * 1000000.0;
        if(outputCurrency == "kilogram")
            return inputValue * 1000.0;
    }
}

double Widget::convertLength(QString inputCurrency = NULL, double inputValue = 0.0, QString outputCurrency = NULL)
{
    if(inputCurrency == outputCurrency)
        return inputValue;
    if(inputCurrency == "cantimetre")
    {
        if(outputCurrency == "metre")
            return inputValue / 100.0;
        if(outputCurrency == "kilometre")
            return inputValue / 100000.0;
    }
    if(inputCurrency == "metre")
    {
        if(outputCurrency == "cantimetre")
            return inputValue * 100.0;
        if(outputCurrency == "kilometre")
            return inputValue / 1000.0;
    }
    if(inputCurrency == "kilometre")
    {
        if(outputCurrency == "cantimetre")
            return inputValue * 100000.0;
        if(outputCurrency == "metre")
            return inputValue * 100.0;
    }
}

double Widget::convertArea(QString inputCurrency = NULL, double inputValue = 0.0, QString outputCurrency = NULL)
{
    if(inputCurrency == outputCurrency)
        return inputValue;
    if(inputCurrency == "square centimetre")
    {
        if(outputCurrency == "square metre")
            return inputValue / 10000.0;
        if(outputCurrency == "hectare")
            return inputValue / 100000000.0;
    }
    if(inputCurrency == "square metre")
    {
        if(outputCurrency == "square centimetre")
            return inputValue * 10000.0;
        if(outputCurrency == "hectare")
            return inputValue / 1000.0;
    }
    if(inputCurrency == "hectare")
    {
        if(outputCurrency == "square centimetre")
            return inputValue * 100000000.0;
        if(outputCurrency == "square metre")
            return inputValue * 10000.0;
    }
}

