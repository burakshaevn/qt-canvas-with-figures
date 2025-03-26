#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "figure.h"
#include <memory>

class DynamicArray {
public:
    DynamicArray();
    void push_back(std::unique_ptr<Figure> figure);
    void erase(int index);
    Figure* Get(int index) const;
    void Iterate(const ActionType action, const size_t index, const int dx = 0, const int dy = 0);
    void Iterate(const ActionType action, const int dx = 0, const int dy = 0);
    size_t size() const;
    bool empty() const;
    Figure& at(size_t index);
    const Figure& at(size_t index) const;
    ~DynamicArray();

private:
    // Динамический массив. Указатель на него не обычный «сырой», а «умный».
    // То есть, выполняет роль «деструктора» (освобождает занимаемые ресурсы)
    std::unique_ptr<Figure>* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void Resize(size_t new_capacity);
};


#endif // DYNAMIC_ARRAY_H
