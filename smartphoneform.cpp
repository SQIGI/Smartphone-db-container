#include "SmartphoneForm.h"
#include "ui_SmartphoneForm.h"
#include <QDebug> // Для отладочного вывода

SmartphoneForm::SmartphoneForm(QWidget *parent)
    : QDialog(parent), ui(new Ui::SmartphoneForm), validData(false) {
    ui->setupUi(this);

    // Подключение сигналов для проверки данных
    connect(ui->lineEditModel, &QLineEdit::textChanged, this, &SmartphoneForm::validateInput);
    connect(ui->lineEditManufacturer, &QLineEdit::textChanged, this, &SmartphoneForm::validateInput);
    connect(ui->lineEditOS, &QLineEdit::textChanged, this, &SmartphoneForm::validateInput);
    connect(ui->spinBoxMemory, &QSpinBox::valueChanged, this, &SmartphoneForm::validateInput);
    connect(ui->doubleSpinBoxPrice, &QDoubleSpinBox::valueChanged, this, &SmartphoneForm::validateInput);

    // Подключение кнопки "Добавить" к диалогу подтверждения
    connect(ui->pushButton_add, &QPushButton::clicked, this, &QDialog::accept);

    ui->pushButton_add->setEnabled(false);  // Кнопка изначально неактивна
}

SmartphoneForm::~SmartphoneForm() {
    delete ui;
}

void SmartphoneForm::setFields(const QString& model, const QString& manufacturer,
                               const QString& os, int memory, double price) {
    ui->lineEditModel->setText(model);
    ui->lineEditManufacturer->setText(manufacturer);
    ui->lineEditOS->setText(os);
    ui->spinBoxMemory->setValue(memory);
    ui->doubleSpinBoxPrice->setValue(price);
}

Smartphone SmartphoneForm::getSmartphoneData() const {
    // Отладочный вывод для проверки данных перед возвратом
    qDebug() << "Получение данных из формы:";
    qDebug() << "Модель:" << ui->lineEditModel->text();
    qDebug() << "Производитель:" << ui->lineEditManufacturer->text();
    qDebug() << "ОС:" << ui->lineEditOS->text();
    qDebug() << "Память (ГБ):" << ui->spinBoxMemory->value();
    qDebug() << "Цена:" << ui->doubleSpinBoxPrice->value();

    return Smartphone(
        ui->lineEditModel->text().toStdString(),
        ui->lineEditManufacturer->text().toStdString(),
        ui->lineEditOS->text().toStdString(),
        ui->spinBoxMemory->value(),
        ui->doubleSpinBoxPrice->value()
        );
}

bool SmartphoneForm::isDataValid() const {
    return validData;
}

void SmartphoneForm::validateInput() {
    // Проверка каждого поля формы
    bool modelOk = !ui->lineEditModel->text().isEmpty();
    bool manufacturerOk = !ui->lineEditManufacturer->text().isEmpty();
    bool osOk = !ui->lineEditOS->text().isEmpty();
    bool memoryOk = ui->spinBoxMemory->value() > 0;
    bool priceOk = ui->doubleSpinBoxPrice->value() > 0;

    validData = modelOk && manufacturerOk && osOk && memoryOk && priceOk;

    // Отладочный вывод для проверки валидности данных
    qDebug() << "Проверка данных:";
    qDebug() << "Модель:" << modelOk;
    qDebug() << "Производитель:" << manufacturerOk;
    qDebug() << "ОС:" << osOk;
    qDebug() << "Память (ГБ):" << memoryOk;
    qDebug() << "Цена:" << priceOk;
    qDebug() << "Данные валидны:" << validData;

    ui->pushButton_add->setEnabled(validData);
}
