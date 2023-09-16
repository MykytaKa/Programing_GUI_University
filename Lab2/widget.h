#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QProgressBar>
#include <QGroupBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void changeConvertDirection(int buttonState);
    void clearEdits();
    void fillBoxes(QAbstractButton *button);
    void convertValue();
    void changeWidgetsSize(int size);

private:
    QCheckBox *invertButton;
    QLabel *convertDirectionText, *invertText;
    QLineEdit *leftEdit, *rightEdit, *inputEdit, *outputEdit;
    QPushButton *clearButton, *convertButton;
    QProgressBar *textSizeBar;
    QSpinBox *textSizeManager;
    QComboBox *leftBox, *rightBox, *inputBox, *outputBox;
    QGroupBox *radioGroup;
    QButtonGroup *radioManager;
    QVBoxLayout *radioLayout;
    QRadioButton *bt1, *bt2, *bt3;
    double convertWeight(QString inputCurrency, double inputValue, QString outputCurrency);
    double convertLength(QString inputCurrency, double inputValue, QString outputCurrency);
    double convertArea(QString inputCurrency, double inputValue, QString outputCurrency);
};
#endif // WIDGET_H
