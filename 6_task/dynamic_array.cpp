#include "dynamic_array.h"

DynamicArray::DynamicArray(){
    qDebug() << "Создан контейнер DynamicArray";
}

void DynamicArray::push_back(std::unique_ptr<Figure> figure) {
    if (size_ >= capacity_) {
        Resize(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = std::move(figure);
}

void DynamicArray::erase(int index) {
    if (index < 0 || index >= size_) return;
    data_[index].reset();
    for (size_t i = index; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
}

Figure* DynamicArray::Get(int index) const {
    if (index < 0 || index >= size_) return nullptr;
    return data_[index].get();
}

void DynamicArray::Iterate(const ActionType action, const size_t index, const int dx, const int dy) {
    for (size_t i = 0; i < size_; ++i) {
        switch (action) {
        case ActionType::MOVE:
            data_[i]->MoveTo(dx, dy);
            break;
        // case ActionType::SHOW:
        //     data_[i]->Show();
        //     break;
        case ActionType::HIDE:
            data_[i]->SetVisible(!data_[i]->GetVisible());
            data_[i]->Show();
            break;
        case ActionType::CLEAR:
            data_[i].reset();
            break;
        }
    }
}

size_t DynamicArray::size() const {
    return size_;
}

bool DynamicArray::empty() const {
    return size_ == 0;
}

Figure& DynamicArray::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return *data_[index];
}

const Figure& DynamicArray::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return *data_[index];
}

DynamicArray::~DynamicArray() {
    Iterate(ActionType::CLEAR);
    delete[] data_;
}

void DynamicArray::Resize(size_t new_capacity) {
    auto new_data = new std::unique_ptr<Figure>[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}
