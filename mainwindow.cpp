#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"Модель", "Производитель", "ОС", "Память (ГБ)", "Цена"});

    connect(ui->actionCreateFile, &QAction::triggered, this, &MainWindow::createFile);
    connect(ui->actionSaveFile, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionLoadFile, &QAction::triggered, this, &MainWindow::loadFile);
    connect(ui->actionMergeFiles, &QAction::triggered, this, &MainWindow::mergeFiles);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addSmartphone);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::editSmartphone);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteSmartphone);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchButtonClicked);
    connect(ui->aboutButton, &QPushButton::clicked, this, &MainWindow::showAboutInfo);  // Связь для кнопки "О программе"
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createFile() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Создать файл базы данных"), "", tr("Database Files (*.db);;All Files (*)"));
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            currentDatabaseFile = filename;
            QMessageBox::information(this, tr("Успех"), tr("Файл базы данных успешно создан."));
            file.close();
        } else {
            QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка при создании файла базы данных."));
        }
    }
}

void MainWindow::saveFile() {
    if (currentDatabaseFile.isEmpty()) {
        currentDatabaseFile = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Database Files (*.db);;All Files (*)"));
        if (currentDatabaseFile.isEmpty()) return;
    }

    QFile file(currentDatabaseFile);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << smartphoneList.size();
        for (int i = 0; i < smartphoneList.size(); ++i) {
            const Smartphone* smartphone = smartphoneList.getSmartphone(i);
            out << QString::fromStdString(smartphone->getModel())
                << QString::fromStdString(smartphone->getManufacturer())
                << QString::fromStdString(smartphone->getOS())
                << smartphone->getMemory()
                << smartphone->getPrice();
        }
        file.close();
        QMessageBox::information(this, tr("Успех"), tr("Данные успешно сохранены."));
    } else {
        QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка при сохранении данных."));
    }
}

void MainWindow::loadFile() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Загрузить файл базы данных"), "", tr("Database Files (*.db);;All Files (*)"));
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            int size;
            in >> size;
            smartphoneList.clear();
            for (int i = 0; i < size; ++i) {
                QString model, manufacturer, os;
                int memory;
                double price;
                in >> model >> manufacturer >> os >> memory >> price;
                smartphoneList.addSmartphone(Smartphone(model.toStdString(), manufacturer.toStdString(), os.toStdString(), memory, price));
            }
            file.close();
            updateTable();
            currentDatabaseFile = filename;
            QMessageBox::information(this, tr("Успех"), tr("Файл базы данных успешно загружен."));
        } else {
            QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка при загрузке файла базы данных."));
        }
    }
}

void MainWindow::mergeFiles() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Выберите файл для объединения"), "", tr("Database Files (*.db);;All Files (*)"));
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            int size;
            in >> size;
            for (int i = 0; i < size; ++i) {
                QString model, manufacturer, os;
                int memory;
                double price;
                in >> model >> manufacturer >> os >> memory >> price;
                smartphoneList.addSmartphone(Smartphone(model.toStdString(), manufacturer.toStdString(), os.toStdString(), memory, price));
            }
            file.close();
            updateTable();
            QMessageBox::information(this, tr("Успех"), tr("Данные успешно объединены."));
        } else {
            QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка при объединении данных."));
        }
    }
}

void MainWindow::addSmartphone() {
    SmartphoneForm form(this);
    if (form.exec() == QDialog::Accepted) {
        Smartphone newSmartphone = form.getSmartphoneData();
        smartphoneList.addSmartphone(newSmartphone);
        updateTable();
    }
}

void MainWindow::editSmartphone() {
    int selectedRow = getSelectedRowIndex();
    if (selectedRow == -1) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не выбрана строка для редактирования."));
        return;
    }

    Smartphone* smartphone = smartphoneList.getSmartphone(selectedRow);
    SmartphoneForm form(this);
    form.setFields(QString::fromStdString(smartphone->getModel()),
                   QString::fromStdString(smartphone->getManufacturer()),
                   QString::fromStdString(smartphone->getOS()),
                   smartphone->getMemory(),
                   smartphone->getPrice());

    if (form.exec() == QDialog::Accepted) {
        Smartphone updatedSmartphone = form.getSmartphoneData();
        smartphoneList.editSmartphone(selectedRow, updatedSmartphone);
        updateTable();
    }
}

void MainWindow::deleteSmartphone() {
    int selectedRow = getSelectedRowIndex();
    if (selectedRow == -1) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не выбрана строка для удаления."));
        return;
    }

    smartphoneList.removeSmartphone(selectedRow);
    updateTable();
}

void MainWindow::updateTable() {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(smartphoneList.size());

    for (int i = 0; i < smartphoneList.size(); ++i) {
        const Smartphone* smartphone = smartphoneList.getSmartphone(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(smartphone->getModel())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(smartphone->getManufacturer())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(smartphone->getOS())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(smartphone->getMemory())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(smartphone->getPrice(), 'f', 2)));
    }
}

void MainWindow::searchButtonClicked() {
    QString searchText = ui->searchEdit->text().trimmed();
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, tr("Поиск"), tr("Введите текст для поиска."));
        return;
    }

    ui->tableWidget->clearSelection();
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        bool match = false;
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive)) {
                match = true;
                item->setSelected(true);
            }
        }
        if (match) {
            ui->tableWidget->scrollToItem(ui->tableWidget->item(row, 0));
            break;
        }
    }
}

void MainWindow::showAboutInfo() {
    QMessageBox::information(this, tr("О программе"), tr("Приложение для управления базой данных смартфонов.\nВерсия: 1.0\nАвтор: Студент ИКПИ-35 Тетеркин Георгий"));
}

int MainWindow::getSelectedRowIndex() const {
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        return -1;
    }
    return selectedItems.first()->row();
}
