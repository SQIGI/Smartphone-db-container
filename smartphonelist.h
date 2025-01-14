#ifndef SMARTPHONELIST_H
#define SMARTPHONELIST_H

#include "Smartphone.h"
#include <vector>

class SmartphoneList {
private:
    std::vector<Smartphone> smartphones; // Контейнер для хранения списка смартфонов

public:
    // Добавление смартфона
    void addSmartphone(const Smartphone& smartphone);

    // Удаление смартфона по индексу
    bool removeSmartphone(int index);

    // Редактирование смартфона по индексу
    bool editSmartphone(int index, const Smartphone& newSmartphone);

    // Получение смартфона по индексу
    Smartphone* getSmartphone(int index) const;

    // Количество смартфонов в списке
    int size() const;

    // Очистка списка
    void clear();
};

#endif // SMARTPHONELIST_H
