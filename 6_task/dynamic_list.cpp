#include "dynamic_list.h"
#include <stdexcept>

DynamicList::DynamicList(){
    qDebug() << "Создан контейнер DynamicList";
}

void DynamicList::push_back(std::unique_ptr<Figure> figure) {
    auto new_node = std::make_unique<Node>(std::move(figure));
    if (!tail) {
        // Если список пустой, делаем новый узел головой и хвостом
        head = std::move(new_node);
        tail = head.get();
    } else {
        // Добавляем элемент в конец и обновляем хвост
        tail->next = std::move(new_node);
        tail = tail->next.get();
    }
    ++size_;
}

void DynamicList::erase(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    if (index == 0) {
        // Удаляем первый элемент
        head = std::move(head->next);
        if (!head) {
            tail = nullptr; // Если список стал пустым, обновляем хвост
        }
    } else {
        // Достаём предыдущий узел и обновляем ссылки
        Node* prev = GetNode(index - 1);
        prev->next = std::move(prev->next->next);
        if (!prev->next) {
            tail = prev; // Если удаляли последний элемент, обновляем хвост
        }
    }
    --size_;
}

Figure* DynamicList::Get(size_t index) const {
    Node* node = GetNode(index);
    return node ? node->figure.get() : nullptr;
}

void DynamicList::Iterate(const ActionType action, const size_t index, const int dx, const int dy) {
    Node* current = head.get();
    size_t counter{};
    while (current) {
        if (counter == index){
            switch (action) {
            case ActionType::MOVE:
                current->figure->MoveTo(dx, dy);
                break;
            case ActionType::SHOW:
                current->figure->Show();
                break;
            case ActionType::HIDE:
                current->figure->SetVisible(!current->figure->GetVisible());
                current->figure->Show();
                break;
            case ActionType::ERASE:
                current->figure->RemoveFromScene();
                erase(index);
                break;
            case ActionType::CLEAR:
                current->figure.reset();
                break;
            }
            break;
        }
        current = current->next.get();
        ++counter;
    }
}

void DynamicList::Iterate(const ActionType action, const int dx, const int dy) {
    Node* current = head.get();
    while (current) {
        switch (action) {
        case ActionType::MOVE:
            current->figure->MoveTo(dx, dy);
            break;
        case ActionType::SHOW:
            current->figure->Show();
            break;
        case ActionType::HIDE:
            current->figure->SetVisible(!current->figure->GetVisible());
            current->figure->Show();
            break;
        case ActionType::ERASE:
            current->figure->RemoveFromScene();
            current->figure.reset();
            break;
        case ActionType::CLEAR:
            current->figure.reset();
            break;
        }
        current = current->next.get();
    }
}

size_t DynamicList::size() const {
    return size_;
}

bool DynamicList::empty() const {
    return size_ == 0;
}

Figure& DynamicList::at(size_t index) {
    Node* node = GetNode(index);
    if (!node) {
        throw std::out_of_range("Index out of range");
    }
    return *node->figure;
}

const Figure& DynamicList::at(size_t index) const {
    Node* node = GetNode(index);
    if (!node) {
        throw std::out_of_range("Index out of range");
    }
    return *node->figure;
}

DynamicList::~DynamicList() {
    while (head) {
        head = std::move(head->next);
    }
    // Все узлы автоматически уничтожатся благодаря умным указателям
}

Node* DynamicList::GetNode(size_t index) const {
    if (index >= size_) {
        return nullptr;
    }
    Node* current = head.get();
    for (size_t i = 0; i < index; ++i) {
        current = current->next.get();
    }
    return current;
}
