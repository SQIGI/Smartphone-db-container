#ifndef SMARTPHONE_H
#define SMARTPHONE_H

#include <string>

class Smartphone {
private:
    std::string model;          // Модель смартфона
    std::string manufacturer;   // Производитель
    std::string os;             // Операционная система
    int memory;                 // Объём памяти (ГБ)
    double price;               // Цена устройства

public:
    // Конструктор
    Smartphone(const std::string& model = "", const std::string& manufacturer = "",
               const std::string& os = "", int memory = 0, double price = 0.0);

    // Геттеры
    std::string getModel() const;
    std::string getManufacturer() const;
    std::string getOS() const;
    int getMemory() const;
    double getPrice() const;

    // Сеттеры
    void setModel(const std::string& model);
    void setManufacturer(const std::string& manufacturer);
    void setOS(const std::string& os);
    void setMemory(int memory);
    void setPrice(double price);
};

#endif // SMARTPHONE_H
