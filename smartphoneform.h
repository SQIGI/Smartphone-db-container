#ifndef SMARTPHONEFORM_H
#define SMARTPHONEFORM_H

#include <QDialog>
#include "Smartphone.h"

namespace Ui {
class SmartphoneForm;
}

class SmartphoneForm : public QDialog {
    Q_OBJECT

public:
    explicit SmartphoneForm(QWidget *parent = nullptr);
    ~SmartphoneForm();

    // Установить значения полей формы
    void setFields(const QString& model, const QString& manufacturer,
                   const QString& os, int memory, double price);

    // Получить данные из формы
    Smartphone getSmartphoneData() const;

    // Проверить валидность данных
    bool isDataValid() const;

private slots:
    // Проверка валидности ввода
    void validateInput();

private:
    Ui::SmartphoneForm *ui;
    bool validData;
};

#endif // SMARTPHONEFORM_H
