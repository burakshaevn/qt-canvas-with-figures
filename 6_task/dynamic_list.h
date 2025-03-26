#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "figure.h"
#include <memory>
#include <functional>

// Узел списка
struct Node {
    std::unique_ptr<Figure> figure;
    std::unique_ptr<Node> next;

    Node(std::unique_ptr<Figure> fig)
        : figure(std::move(fig))
        , next(nullptr)
    {}
};

// Динамический линейный список
class DynamicList {
public:
    DynamicList();
    void push_back(std::unique_ptr<Figure> figure);
    void erase(size_t index);
    Figure* Get(size_t index) const;
    void Iterate(const ActionType action, const size_t index = -1, const int dx = 0, const int dy = 0);
    size_t size() const;
    bool empty() const;
    Figure& at(size_t index);
    const Figure& at(size_t index) const;
    ~DynamicList();

private:
    std::unique_ptr<Node> head = nullptr; // Указатель на начало списка
    Node* tail = nullptr;                // Указатель на конец списка
    size_t size_ = 0;                    // Количество элементов в списке

    Node* GetNode(size_t index) const;
};

#endif // DYNAMIC_LIST_H
