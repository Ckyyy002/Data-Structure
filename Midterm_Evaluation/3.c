#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id, jumlah_warisan, bernyawa; 
    char nama[30];
    struct Node *left, *right;
} Node;

Node *create(int id, char nama[], int jumlah_warisan) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->nama, nama);
    newNode->jumlah_warisan = jumlah_warisan;
    newNode->bernyawa = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *push(Node *root, int id, char nama[], int jumlah_warisan, int ortu_id, char anak_mana) {
    Node *parent = NULL;
    int front = 0, rear = 0;
    Node *queue[100];
    queue[rear++] = root;
    
    while (front < rear) {
        Node *current = queue[front++];
        
        if (current->id == ortu_id) {
            parent = current;
            break;
        }
        
        if (current->left != NULL) queue[rear++] = current->left;
        if (current->right != NULL) queue[rear++] = current->right;
    }
    
    if (anak_mana == 'L' || anak_mana == 'l') {
        if (parent->left == NULL) {
            parent->left = create(id, nama, jumlah_warisan);
        } 
    } 
    else if (anak_mana == 'R' || anak_mana == 'r') {
        if (parent->right == NULL) {
            parent->right = create(id, nama, jumlah_warisan);
        }
    }
    
    return root;
}

void print(Node *root, int space) {
    if (root == NULL) {
        return;
    }

    space += 5;
    print(root->right, space);
    
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d|%s|%d.000.000|%s\n", root->id, root->nama, root->jumlah_warisan, root->bernyawa ? "Hidup" : "Mati");
    print(root->left, space);
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("ID: %d, Nama: %s, Warisan: %d.000.000, Status: %s\n", root->id, root->nama, root->jumlah_warisan, root->bernyawa ? "Hidup" : "Mati");
        inorder(root->right);
    }
}

Node *find(Node *root, int id) {
    if (root == NULL) {
        return NULL;
    }
    
    if (root->id == id) {
        return root;
    }
    
    Node *leftResult = NULL;
    if (root->left != NULL) {
        leftResult = find(root->left, id);
    }
    
    if (leftResult != NULL) {
        return leftResult;
    }
    
    if (root->right != NULL) {
        return find(root->right, id);
    }
    
    return NULL;
}

void bagi(Node *node, int jumlah_warisan) {
    if (node->bernyawa) {
        node->jumlah_warisan += jumlah_warisan;
    } 
}

void sim_mati(Node *root, int id) {
    Node *node = find(root, id);
    if (node == NULL || !node->bernyawa) {
        return;
    }
    
    node->bernyawa = 0;
    printf("%s (ID: %d) telah meninggal\n", node->nama, node->id);
    int total = node->jumlah_warisan;
    node->jumlah_warisan = 0;
    int anakHidup = 0;
    Node *anakHidupPtr = NULL;
    
    if (node->left != NULL && node->left->bernyawa) {
        anakHidup++;
        anakHidupPtr = node->left;
    }
    if (node->right != NULL && node->right->bernyawa) {
        anakHidup++;
        anakHidupPtr = node->right;
    }
    
    if (anakHidup == 1) {
        bagi(anakHidupPtr, total);
    } 
    else {
        if (node->left != NULL) {
            bagi(node->left, total * 6 / 10);
        }
        if (node->right != NULL) {
            bagi(node->right, total * 4 / 10);
        }
    }
}

void menu() {
    printf("1. Tambah Anggota Keluarga\n");
    printf("2. Tampilkan Pohon Keluarga\n");
    printf("3. Tampilkan Daftar Keluarga (Inorder)\n");
    printf("4. Simulasikan Kematian\n");
    printf("5. Keluar\n");
    printf("Pilih menu: ");
}

int main() {
    Node *root = NULL;
    int choice, id, ortu_id, jumlah_warisan;
    char nama[30], anak_mana;
    int next_id = 1;
    
    while (1) {
        menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Masukkan nama anggota keluarga: ");
                scanf(" %[^\n]s", nama);
                printf("Masukkan jumlah warisan: ");
                scanf("%d", &jumlah_warisan);
                
                if (root == NULL) {
                    root = create(next_id++, nama, jumlah_warisan);
                    printf("Anggota keluarga %s telah ditambahkan sebagai root dengan ID %d.\n", nama, next_id-1);
                } 
                else {
                    printf("Masukkan ID parent: ");
                    scanf("%d", &ortu_id);
                    printf("Masukkan tipe anak (L untuk kiri, R untuk kanan): ");
                    scanf(" %c", &anak_mana);
                    root = push(root, next_id++, nama, jumlah_warisan, ortu_id, anak_mana);
                    printf("Anggota keluarga %s telah ditambahkan dengan ID %d.\n", nama, next_id-1);
                }
                break;
            case 2:
                print(root, 0);
                printf("\n");
                break;
            case 3:
                inorder(root);
                break;
            case 4:
                printf("Masukkan ID anggota keluarga yang meninggal: ");
                scanf("%d", &id);
                sim_mati(root, id);
                break;
            default:
                printf("Program selesai.\n");
                exit(0);
        }
    }
    
    return 0;
}
