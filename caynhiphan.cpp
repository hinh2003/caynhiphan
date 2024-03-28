#include <iostream>
#include <cstdlib> // Thêm thư viện này để sử dụng hàm rand()

using namespace std;

// Định nghĩa cấu trúc của một nút trong cây nhị phân
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Hàm để tạo một nút mới
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Hàm để thêm một nút vào cây nhị phân
Node* insert(Node* root, int data) {
    // Nếu cây rỗng, tạo nút mới và trả về
    if (root == NULL) {
        return createNode(data);
    }

    // Nếu không, đi xuống cây để tìm vị trí thích hợp cho nút mới
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    // Trả về nút gốc sau khi thêm nút mới
    return root;
}

// Hàm để tìm nút có giá trị nhỏ nhất trong cây
Node* minValueNode(Node* node) {
    Node* current = node;
    // Lặp qua cây để tìm nút có giá trị nhỏ nhất
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Hàm để xóa một nút khỏi cây
Node* deleteNode(Node* root, int key) {
    // Nếu cây rỗng, trả về
    if (root == NULL) {
        return root;
    }

    // Tìm nút cần xóa
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Nếu nút cần xóa có 0 hoặc 1 con
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Nếu nút có 2 con, tìm nút kế tiếp có giá trị nhỏ nhất (nút gốc của cây con phải)
        Node* temp = minValueNode(root->right);
        // Sao chép dữ liệu của nút kế tiếp vào nút hiện tại
        root->data = temp->data;
        // Xóa nút kế tiếp
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
// Hàm để in thứ tự trung của cây nhị phân
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}
// Hàm để giải phóng bộ nhớ của cây
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}
// Hàm để tìm một phần tử trong cây nhị phân
bool search(Node* root, int key) {
    // Nếu cây rỗng hoặc không thấy key, trả về false
    if (root == NULL) {
        return false;
    }
    // Nếu key là giá trị của nút hiện tại, trả về true
    if (root->data == key) {
        return true;
    }
    // Nếu key nhỏ hơn giá trị của nút hiện tại, tìm kiếm ở cây con bên trái
    if (key < root->data) {
        return search(root->left, key);
    }
    // Nếu key lớn hơn giá trị của nút hiện tại, tìm kiếm ở cây con bên phải
    return search(root->right, key);
}

int main() {
    Node* root = NULL;
    int choice, data;
       // h = 6 => 2^6-1 = 63
    for (int i = 1; i <= 63; ++i) {
        int random = rand()% 100 +1; // sinh so tu 0 den 99
        root = insert(root, random);
    }


    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Them phan tu\n";
        cout << "2. Xoa phan tu\n";
        cout << "3. In cay nhi phan\n";
        cout << "4. Thoat\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Nhap gia tri phan tu muon them: ";
                cin >> data;
                root = insert(root, data);
                cout << "Da them " << data << " vao cay.\n";
                break;
            case 2:
                cout << "Nhap gia tri phan tu muon xoa: ";
                cin >> data;
                if(search(root,data))
                {
                root = deleteNode(root, data);
                cout << "Da xoa " << data << " khoi cay.\n";
                }
                else{
                cout<<"Phan tu khong co trong cay \n";
                }

                break;
            case 3:
                cout << "Cay nhi phan:\n";
                inorder(root);
                cout << endl;
                break;
            case 4:
                // Giải phóng bộ nhớ trước khi thoát
                freeTree(root);
                cout << "\nNhan Enter de tiep tuc...";
                getchar(); // Xóa bộ nhớ đệm
                getchar(); // Dừng màn hình
                exit(0);

            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }
        if (choice != 3){
        // In cây sau mỗi thao tác
        cout << "Cay sau khi thao tac:  ";
        inorder(root);
        cout << endl;
        }
     
    }

    return 0;
}
