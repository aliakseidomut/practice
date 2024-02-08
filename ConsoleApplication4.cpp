﻿#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

template<class T>
struct Node {
    T item;
    Node<T>* next;

    Node() : next(nullptr) {}
    Node(const T& value) : item(value), next(nullptr) {}
};

template<class T>
class List {
public:
    Node<T>* head;

    List();
    List(const List& aList);
    ~List();

    void pushBack(T item);
    void printList();
    bool isEmpty();
    void removeLastNode();
    int getLength();
    void insertNode(T item, int index);
    void removeNode(int index);
    T getFirst();
    T getLast();
    T getItem(int index);
    void reverse();
    void fillAscendingSequence(int count);
    void clear();
};

template<class T>
List<T>::List() {
    head = NULL;
}

template<class T>
List<T>::List(const List& aList) {
    if (aList.head == NULL) {
        head = NULL;
    }
    else {
        head = new Node<T>;
        head->item = aList.head->item;

        Node* newNode = head;
        Node* oldNode = aList.head->next;

        while (oldNode != NULL) {
            newNode->next = new Node<T>;
            newNode = newNode->next;
            newNode->item = oldNode->item;
            oldNode = oldNode->next;
        }

        newNode->next = NULL;
    }
}

template<class T>
List<T>::~List() {
    while (head != NULL) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

template<class T>
void List<T>::pushBack(T item) {
    Node<T>* newNode = new Node<T>;
    newNode->item = item;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    }
    else {
        Node<T>* cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
}

template<class T>
void List<T>::printList() {
    Node<T>* cur = head;
    while (cur != NULL) {
        cout << cur->item << " ";
        cur = cur->next;
    }
    cout << endl;
}

template<class T>
bool List<T>::isEmpty() {
    return head == NULL;
}

template<class T>
void List<T>::removeLastNode() {
    if (head == NULL) {
        return;
    }
    else if (head->next == NULL) {
        delete head;
        head = NULL;
    }
    else {
        Node<T>* cur = head;
        while (cur->next->next != NULL) {
            cur = cur->next;
        }
        delete cur->next;
        cur->next = NULL;
    }
}

template<class T>
int List<T>::getLength() {
    int length = 0;
    Node<T>* cur = head;
    while (cur != NULL) {
        length++;
        cur = cur->next;
    }
    return length;
}

template<class T>
void List<T>::insertNode(T item, int index) {
    if (index < 0 || index > getLength()) {
        return;
    }

    Node<T>* newNode = new Node<T>;
    newNode->item = item;

    if (index == 0) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node<T>* cur = head;
        for (int i = 0; i < index - 1; i++) {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
    }
}

template<class T>
void List<T>::removeNode(int index) {
    if (index < 0 || index >= getLength()) {
        return;
    }

    if (index == 0) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    else {
        Node<T>* cur = head;
        for (int i = 0; i < index - 1; i++) {
            cur = cur->next;
        }
        Node<T>* temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
    }
}

template<class T>
T List<T>::getFirst() {
    if (head != NULL) {
        return head->item;
    }
    return 0.0;
}

template<class T>
T List<T>::getLast() {
    if (head == NULL) {
        return 0.0;
    }

    Node<T>* cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }

    return cur->item;
}

template<class T>
T List<T>::getItem(int index) {
    if (index < 0 || index >= getLength()) {
        return 0.0;
    }

    Node<T>* cur = head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }

    return cur->item;
}

template<class T>
void List<T>::reverse() {
    if (head == NULL || head->next == NULL) {
        return;
    }

    Node<T>* prev = NULL;
    Node<T>* cur = head;
    Node<T>* next = NULL;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    head = prev;
}

template<class T>
void List<T>::fillAscendingSequence(int count) {
    clear();

    double currentItem = 0.0;

    for (int i = 0; i < count; i++) {
        pushBack(currentItem);
        currentItem += 1.0;
    }

    cout << "Список успешно заполнен." << endl;
}

template<class T>
void List<T>::clear() {
    Node<T>* current = head;
    while (current != NULL) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }

    head = NULL;
}

template<class T>
void saveListToFile(const List<T>& list, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        Node<T>* current = list.head;

        while (current != NULL) {
            file << current->item << endl;
            current = current->next;
        }

        file.close();

        cout << "Список успешно сохранен в файл." << endl;
    }
    else {
        cout << "Ошибка: не удалось открыть файл для записи." << endl;
    }
}


template<class T>
void loadListFromFile(List<T>& list, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        double item;
        list.clear();

        while (file >> item) {
            list.pushBack(item);
        }

        file.close();

        cout << "Список успешно загружен из файла." << endl;
    }
    else {
        cout << "Ошибка: не удалось открыть файл для чтения." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    List<double> myList;
    int choice;
    double item;
    int index;
    string filename;

    do {
        cout << "========== Меню ==========" << endl;
        cout << "1. Добавить элемент в конец списка" << endl;
        cout << "2. Вывести список на экран" << endl;
        cout << "3. Удалить последний элемент" << endl;
        cout << "4. Получить длину списка" << endl;
        cout << "5. Вставить элемент по индексу" << endl;
        cout << "6. Удалить элемент по индексу" << endl;
        cout << "7. Получить первый элемент" << endl;
        cout << "8. Получить последний элемент" << endl;
        cout << "9. Получить элемент по индексу" << endl;
        cout << "10. Перевернуть список" << endl;
        cout << "11. Сохранить список в файл" << endl;
        cout << "12. Загрузить список из файла" << endl;
        cout << "13. Очистить список" << endl;
        cout << "14. Заполнить список последовательностью неубывающих элементов" << endl;
        cout << "0. Выход" << endl;
        cout << "==========================" << endl;
        cout << "Введите номер операции: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите элемент: ";
            cin >> item;
            myList.pushBack(item);
            cout << "Элемент успешно добавлен в конец списка." << endl;
            break;
        case 2:
            myList.printList();
            break;
        case 3:
            myList.removeLastNode();
            cout << "Последний элемент успешно удален." << endl;
            break;
        case 4:
            cout << "Длина списка: " << myList.getLength() << endl;
            break;
        case 5:
            cout << "Введите элемент: ";
            cin >> item;
            cout << "Введите индекс: ";
            cin >> index;
            myList.insertNode(item, index);
            cout << "Элемент успешно вставлен по указанному индексу." << endl;
            break;
        case 6:
            cout << "Введите индекс: ";
            cin >> index;
            myList.removeNode(index);
            cout << "Элемент успешно удален по указанному индексу." << endl;
            break;
        case 7:
            cout << "Первый элемент: " << myList.getFirst() << endl;
            break;
        case 8:
            cout << "Последний элемент: " << myList.getLast() << endl;
            break;
        case 9:
            cout << "Введите индекс: ";
            cin >> index;
            cout << "Элемент по указанному индексу: " << myList.getItem(index) << endl;
            break;
        case 10:
            myList.reverse();
            cout << "Список успешно перевернут." << endl;
            break;
        case 11:
            cout << "Введите имя файла: ";
            cin >> filename;
            saveListToFile(myList, filename);
            break;
        case 12:
            cout << "Введите имя файла: ";
            cin >> filename;
            loadListFromFile(myList, filename);
            break;
        case 13:
            myList.clear();
            break;
        case 14:
            int n;
            cout << "Введите количество элементов: ";
            cin >> n;
            myList.fillAscendingSequence(n);
        case 0:
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Ошибка: некорректный номер операции." << endl;
            break;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}