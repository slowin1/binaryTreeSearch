#include <iostream>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


using namespace std;

class BST{
    struct Node{
        int key;
        Node *left = nullptr , *right = nullptr;
        Node(int key) : key(key){}
    } *root = nullptr;


    bool contains(Node *n, int key ) const{
        if(!n)
            return false;
        if(key == n->key)
            return true;
        if(key < n -> key)
            return  contains(n->left, key);
        else
            return contains(n-> right, key);
    }


    void insert(Node *&n, int key){
        if(!n){
            n  = new Node(key);
            return;
        }
        if(key == n->key)
            return;
        if (key < n->key)
            insert(n->left, key);
        else
            insert(n->right, key);

    }

    void DFSInOrder(Node *n) const{
        if(!n) return;
        DFSInOrder(n->left);
        cout << n->key << " ";
        DFSInOrder(n->right);
    }
    void DFSPreOrder(Node *n) const{
        if(!n) return;
        cout << n->key << " ";
        DFSPreOrder(n->left);
        DFSPreOrder(n->right);
    }

    void DFSPostOrder(Node *n) const {
        if(!n) return;
        DFSPostOrder(n->left);
        DFSPostOrder(n->right);
        cout << n->key << " ";
    }
    void BFS(Node* n) const {
        if (!n) return;
        queue<Node*> q;
        q.push(n);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << current->key << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    int getMin(Node* n) const {
        if (!n) return 0;          // дерево пустое
        while (n->left)            // идём влево до конца
        n = n->left;
        return n->key;
    }

    int getMax(Node* n) const {
        if (!n) return 0;          // дерево пустое
        while (n->right)           // идём вправо до конца
        n = n->right;
        return n->key;
     }

    Node* Delete(Node* n, int key) {
        if (!n) return nullptr;

        if (key < n->key) {
            n->left = Delete(n->left, key);
        } else if (key > n->key) {
            n->right = Delete(n->right, key);
        } else {
            // Случай 1: нет детей
            if (!n->left && !n->right) {
                delete n;
                return nullptr;
            }
            // Случай 2: только правый ребёнок
            if (!n->left) {
                Node* temp = n->right;
                delete n;
                return temp;
            }
            // Случай 3: только левый ребёнок
            if (!n->right) {
                Node* temp = n->left;
                delete n;
                return temp;
            }

            // Случай 4: два ребёнка
            // Найти минимальный элемент в правом поддереве
            Node* minRight = n->right;
            while (minRight->left)
                minRight = minRight->left;

            n->key = minRight->key; // заменить значение
            n->right = Delete(n->right, minRight->key); // удалить продублированный узел
        }


        return n;
    }

    int height(Node *n) const{
        if(n == nullptr) return -1;
        return 1 + max(height(n->left), height(n->right));
    }

    bool save(Node* n, ofstream& file) const {
        if (!n) return true;
        file << n->key << " ";
        save(n->left, file);
        save(n->right, file);
        return true;
    }

    void clear(Node* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }


    public :

    ~BST() {
        clear(root);
    }

    bool contains(int key) const {
        return contains(root, key);
    }

    void insert(int key){
        insert(root, key);
    }

    void DFSInOrder() const{
        DFSInOrder(root);
        cout << endl;
    }
    void DFSPreOrder() const{
        DFSPreOrder(root);
        cout << endl;
    }
    void DFSPostOrder() const{
        DFSPostOrder(root);
        cout << endl;
    }
    void BFS() const {
        BFS(root);
        cout << endl;
    }
    int getMin() const {
        return getMin(root);   // передаём корень и возвращаем значение
    }

    int getMax() const {
        return getMax(root);   // то же самое для max
    }
    void Delete(int key) {
        root = Delete(root, key);
    }
    int height() const {
        return height(root);
    }

    bool saveToFile(const string& filename = "BinaryTree.txt") const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return false;
        }

        system("./openFile.sh");
        return save(root, file);
    }

    bool loadFromFile(const string& filename = "BinaryTree.txt") {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return false;
        }

        root = nullptr; // очищаем текущее дерево
        int value;
        cout << "Загружаемые значения из файла:\n";
        while (file >> value) {
            cout << value << " ";
            insert(value);
        }
        cout << endl;

        system("./openFile.sh");

        return true;
    }

};

int main (){
    BST Tree;
    int n ;
    cout << "Сколько чисел вы хотите  вставить в дерево ? " << endl;
    cin >> n ;

    cout << "Введите "  << n << " целых чисел " << endl;
    for (int i = 0 ; i < n ; ++i){
        int value ;
        cin >> value;
        Tree.insert(value);
    }

 while (true) {
        cout << "\nВведите номер программы:" << endl;
        cout << "1. Поиск элемента" << endl;
        cout << "2. Обход в Глубину (DFS)" << endl;
        cout << "3. Обход в Ширину (BFS)" << endl;
        cout << "4. Минимальный элемент  " << endl;
        cout << "5. Максимальный элемент" << endl;
        cout << "6. Удаление элемента " << endl;
        cout << "7. Высота дерева" << endl;
        cout << "8. Сохранение в файл" << endl;
        cout << "9. Чтение файла" << endl;
        cout << "0. Выход" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Выход из программы." << endl;
                return 0;

            case 1: {
                cout << "Введите число для поиска: ";
                int key;
                cin >> key;
                if (Tree.contains(key)) {
                    cout << "Число найдено в дереве." << endl;
                } else {
                    cout << "Число не найдено в дереве." << endl;
                }
                break;
            }

            case 2: {
                cout << "Обход в глубину (InOrder): ";
                Tree.DFSInOrder();

                cout << "Обход в глубину (PreOrder): ";
                Tree.DFSPreOrder();

                cout << "Обход в глубину (PostOrder): ";
                Tree.DFSPostOrder();
                break;
            }

            case 3: {
                cout << "Обход в ширину (BFS): ";
                Tree.BFS();
                break;
            }
            case 4: {
                cout << "Минимальний элемент : " << Tree.getMin();
            }
            case 5: {
                cout << "Максимальный элемент : " << Tree.getMax();
            }
            case 6: {
                cout << "Введите число которое будем удалять" << endl;
                int delkey;
                cin >> delkey;
                Tree.Delete(delkey);
                cout << "Обход после удаления (InOrder): ";
                Tree.DFSInOrder();
                break;
            }
            case 7: {
                cout << "Высота дерева = " << Tree.height() << endl;
                    break;
            }
            case 8 : {
                cout << "Загрузка в файл " << endl;
                Tree.saveToFile();
                    break;
            }
            case 9 : {
                cout << "Чтение файла " << endl;
                Tree.loadFromFile();
                    break;
            }
            default:
                cout << "Неверный выбор. Повторите попытку." << endl;
        }
    }

    return 0;

}
