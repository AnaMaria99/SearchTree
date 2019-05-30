#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

//Numărul maxim de noduri frunză care pot fi vizitate într-unbuget datSe dă un arbore binar și un număr întreg b
// reprezentând bugetul. Tema constă în găsirea numărului maxim de noduri frunză care pot fi vizitate în bugetul dat.
// Costul de vizitare a unui nod frunză este egal cu nivelul nodului frunză.Notă: Rădăcina arborelui este la nivelul 1

using namespace std;

struct Node {
    int data;
    struct Node *left, *right;
};

vector <int> lista;


//Functia creaza radacina
Node* addNode(int x) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = x;
    temp->left = temp->right = NULL;
    return temp;
}


//Functia returneaza frunzele si nivelul pe care se afla ele
void getLeafNodes(Node *root, vector<int> *v, int height)
{
    if (!root)
        return;

    if (!root->left && !root->right) {
        v->push_back(height);
        return;
    }

    if (root->left)
        getLeafNodes(root->left, v, height+1);

    if (root->right)
        getLeafNodes(root->right, v, height+1);
}


//Functia insereaza un nod nou
Node* insert(int x, struct Node* t)
{
    if(t == NULL)
    {
        t = addNode(x);
    }
    else if(x < t->data)
        t->left = insert(x, t->left);
    else if(x >=t->data)
        t->right = insert(x, t->right);
    return t;
}


//Afiseaza arborele inordine, pentru a ne asigura ca a creat arborele corect
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout<<root->data;
        inorder(root->right);
    }
}

//Functia citeste nodurile din fisier
void NewList(){
    int nr=0;
    ifstream fin;
    fin.open("/home/ana-maria/Desktop/SD/TemaProiect/data.in");
    while(!fin.eof()){
        fin >> nr;
        lista.push_back(nr);
    }
}

void Run(){
    NewList();
    struct Node *root = NULL;
    root = insert(lista[0], root);
    for (int k = 1; k < lista.size(); k++) {
        int x= lista[k];
        insert(x, root);
    }
    int b = 0;
    cout<<"Care este bugetul Dumneavoastra?"<<endl;
    cin>>b;

    vector<int> leafNodes;
    getLeafNodes(root, &leafNodes, 1);
    sort(leafNodes.begin(), leafNodes.end());
    int i;
    for (i = 0; i < leafNodes.size(); i++) {
        if (b >= leafNodes[i]) {
            b -= leafNodes[i];
        } else break;
    }
    cout<<"Arborele inordine este: ";
    inorder(root);
    cout<<endl;
    cout<<"Maxim puteti vizita:  "<<i<<" frunze";

}


int main() {

    Run();
    return 0;
    }
