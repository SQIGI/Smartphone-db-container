#include "Smartphone.h"

// Конструктор
Smartphone::Smartphone(const std::string& model, const std::string& manufacturer,
                       const std::string& os, int memory, double price)
    : model(model), manufacturer(manufacturer), os(os), memory(memory), price(price) {}

// Геттеры
std::string Smartphone::getModel() const { return model; }
std::string Smartphone::getManufacturer() const { return manufacturer; }
std::string Smartphone::getOS() const { return os; }
int Smartphone::getMemory() const { return memory; }
double Smartphone::getPrice() const { return price; }

// Сеттеры
void Smartphone::setModel(const std::string& model) { this->model = model; }
void Smartphone::setManufacturer(const std::string& manufacturer) { this->manufacturer = manufacturer; }
void Smartphone::setOS(const std::string& os) { this->os = os; }
void Smartphone::setMemory(int memory) { this->memory = memory; }
void Smartphone::setPrice(double price) { this->price = price; }
