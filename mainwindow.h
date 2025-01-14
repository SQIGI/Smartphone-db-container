#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SmartphoneList.h"
#include "SmartphoneForm.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createFile();
    void saveFile();
    void loadFile();
    void mergeFiles();
    void addSmartphone();
    void editSmartphone();
    void deleteSmartphone();
    void searchButtonClicked();
    void showAboutInfo();  // Новый слот для кнопки "О программе"

private:
    Ui::MainWindow *ui;
    SmartphoneList smartphoneList;
    QString currentDatabaseFile;

    void updateTable();
    int getSelectedRowIndex() const;
};

#endif // MAINWINDOW_H
