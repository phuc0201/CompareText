#include <iostream>
#include <string>
#include<fstream>
#include<vector>
#include<time.h>
using namespace std;

struct Node
{
    string data;
    Node* left;
    Node* right;
    int sml;
    int height;
};

// Calculate height
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int _max(int a, int b) {
    return (a > b) ? a : b;
}

// New node creation
Node* newNode(string data) {
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->sml = 1;
    node->height = 1;
    return (node);
}
Node* minValueNode(Node* node)
{
    Node* current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}
// Rotate right
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = _max(height(y->left),
        height(y->right)) +
        1;
    x->height = _max(height(x->left),
        height(x->right)) +
        1;
    return x;
}

// Rotate left
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = _max(height(x->left),
        height(x->right)) +
        1;
    y->height = _max(height(y->left),
        height(y->right)) +
        1;
    return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) -
        height(N->right);
}
bool StopWord(string s)
{
    string f, str;
    vector<string> vct_StopWord;
    ifstream file;
    file.open("stopword.txt", ios::in);
    while (!file.eof())
    {
        file >> f;
        vct_StopWord.push_back(f);
    }
    while (vct_StopWord.size() != 0)
    {
        if (s == vct_StopWord[vct_StopWord.size() - 1])
            return true;

        vct_StopWord.pop_back();
    }
    return false;
}
string NoCapsCharacter(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
    return str;
}
int StringSimilarity(string s1, string s2)
{
    string longString = s1;
    string shortString = s2;
    vector<string> vct1;
    vector<string> vct2;
    int Count = 0;
    if (s1.length() < s2.length())
    {
        longString = s2;
        shortString = s1;
    }
    string temp = "";
    for (int i = 0; i < longString.length(); i++)
    {
        if (longString[i] != ' ')
            temp += longString[i];
        if (longString[i] == ' ' || i == longString.length() - 1)
        {
            vct1.push_back(temp);
            temp = "";
        }
    }
    temp = "";
    for (int i = 0; i < shortString.length(); i++)
    {
        if (shortString[i] != ' ')
            temp += shortString[i];
        if (shortString[i] == ' ' || i == shortString.length() - 1)
        {
            vct2.push_back(temp);
            temp = "";
        }
    }
    vector<string> vct;
    for (int i = 0; i < vct2.size(); i++)
        for (int j = 0; j < vct1.size(); j++)
            if (vct2[i] == vct1[j])
            {
                Count++;
                break;
            }
    if (Count >= vct2.size() * 50 / 100 && vct2.size() >= 20 || Count >= vct2.size() * 60 / 100)
        return 1;
    else
        return 0;
}

Node* insertNode(Node* node, string data)
{
    // Find the correct postion and insert the node
    if (node == NULL)
        return newNode(data);
    else if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + _max(height(node->left),
        height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (data < node->left->data) {
            return rightRotate(node);
        }
        else if (data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (data > node->right->data) {
            return leftRotate(node);
        }
        else if (data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

Node* FindNode(Node* root, string value)
{
    Node* temp = root;
    while (temp != nullptr)
    {
        if (temp->data == value)
            break;
        else if (temp->data < value)
            temp = temp->right;
        else if (temp->data > value)
            temp = temp->left;
    }
    if (temp == nullptr)
        return nullptr;
    else
        return temp;
}
void Find_Node(Node* root, string value)
{
    Node* temp = root;
    while (temp != nullptr)
    {
        if (temp->data==value)        
            break;
        else if (temp->data < value)
            temp = temp->right;
        else if (temp->data > value)
            temp = temp->left;
    }
}
Node* deleteNode(Node* root, string data)
{

    // STEP 1: PERFORM STANDARD BST DELETE 
    if (root == NULL)
        return root;

    // If the data to be deleted is smaller 
    // than the root's data, then it lies
    // in left subtree 
    if (data < root->data)
        root->left = deleteNode(root->left, data);

    // If the data to be deleted is greater 
    // than the root's data, then it lies 
    // in right subtree 
    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    // if data is same as root's data, then 
    // This is the node to be deleted 
    else
    {
        // node with only one child or no child 
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            Node* temp = root->left ?
                root->left :
                root->right;

            // No child case 
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case 
                *root = *temp; // Copy the contents of 
                               // the non-empty child 
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's 
            // data to this node 
            root->data = temp->data;

            // Delete the inorder successor 
            root->right = deleteNode(root->right,
                temp->data);
        }
    }

    // If the tree had only one node
    // then return 
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left),
        height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF 
    // THIS NODE (to check whether this 
    // node became unbalanced) 
    int balance = getBalanceFactor(root);

    // If this node becomes unbalanced, 
    // then there are 4 cases 

    // Left Left Case 
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case 
    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case 
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case 
    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
bool CheckIfExist(string str, vector<string> &vct, Node*& root)
{
    if (vct.size() == 0)
        return false;
    int i;
    for (i = 0; i < vct.size(); i++)
    {
        if (StringSimilarity(str, vct[i]) == 1)
        {
            Node* temp = FindNode(root, vct[i]);
            if (str.length() > vct[i].length())
            {
                root = deleteNode(root, temp->data);
                root = insertNode(root, str);
                FindNode(root, str)->sml++;
                vct[i] = str;
            }
            return true;
        }
    }
    return false;
}
double Result(Node* Parent1, Node* Parent2, vector<string> vct)
{
    int sum = 0,j=0;
    int u = 0, v = 0;
    vector<int> vct_f1;
    vector<int> vct_f2;
    for (int i = 0; i < vct.size(); i++)
    {
        if (FindNode(Parent1, vct[i]) == nullptr)
            vct_f1.push_back(0);
        else if (FindNode(Parent1, vct[i]) != nullptr)
            vct_f1.push_back(FindNode(Parent1, vct[i])->sml);

        if (FindNode(Parent2, vct[i]) == nullptr)
            vct_f2.push_back(0);
        else if (FindNode(Parent2, vct[i]) != nullptr)
            vct_f2.push_back(FindNode(Parent2, vct[i])->sml);
    }
    for (int i = 0; i < vct_f1.size(); i++)
    {
        sum += (vct_f1[i] * vct_f2[i]);
        u += (vct_f1[i] * vct_f1[i]);
        v += (vct_f2[i] * vct_f2[i]);
    }
    cout << "\n";
    for (int i = 0; i < vct_f1.size(); i++)
    {
        cout << vct_f1[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < vct_f1.size(); i++)
    {
        cout << vct_f2[i] << " ";
    }
    cout << "\n";
    double T = (double)sum / (sqrt(u) * sqrt(v));
    return T;
}
void DocFile(Node*& root,vector<string> &vct_datatree, string name)
{
    double min = 1000, max = -1, mean=0;
    clock_t start, end;
    int Count = 0;
    string f;
    int t = 1;
    ifstream file;
    file.open(name, ios::in);
    string str = "";
    while (!file.eof())
    {
        file >> f;     
        if (!StopWord(NoCapsCharacter(f)))
        { 
            str += NoCapsCharacter(f);
            if (f[f.length() - 1] != '.')
                str += " ";
            if (f[f.length() - 1] == '.')
            {                           
                str.pop_back();
                if (!CheckIfExist(str, vct_datatree, root))
                {
                    Count++;
                    vct_datatree.push_back(str);
                }
                start = clock();
                root = insertNode(root, str);
                end = clock();
                str = "";           
                double time = (double)(end - start) / CLOCKS_PER_SEC;
                mean += time;
                if (min > time)
                    min = time;
                else if (max < time)
                    max = time;
                
                if (Count == t*100)
                {
                    cout << "\nSo cau insert: " << Count << "\n"; 
                    cout <<"Tong thoi gian: " << (double)mean<< "\n";
                    cout << "Thoi gian trung binh: " << (double)mean/(t*100)*1000 << "(ms)" << "\n";
                    t++;
                }
                if (Count == 1000)
                    break;

            }
        }       
    }
}
int check_rong(string namefile)
{
    ifstream file;
    file.open(namefile, ios::in);
    string f;
    string str = "";
    while (!file.eof())
    {
        file >> f;
        str += f;
        if (str != "")
            return 1;
        str = "";
    }
    return 0;
}
void NhapTenFile(string& NameFile)
{
    ifstream file;
    do
    {
        cout << "\nNhap ten file ban muon so sanh: \n";
        cin >> NameFile;
        file.open(NameFile, ios::in);
        if (!file.is_open() || check_rong(NameFile) == 0)
            cout << "\nKhong hop le!\nVUI LONG NHAP LAI!\n";
    } while (!file.is_open() || check_rong(NameFile) == 0);
}
void Print(Node* root)
{
    if (root == nullptr)
        return;
    cout << root->data<<"\n";

    Print(root->left);
    Print(root->right);
}
int main()
{
    double mean=0;
    vector<int> vct;
    clock_t start, end;
    double t=0;
    int k = 1;
    vector<string> vct_tree1;
    vector<string> vct_tree2;
    string namef1="data2.txt";// file chứa hơn 1000 câu
    Node* rootf1 = NULL;
    Node* rootf2 = NULL;
    cout << "================== THOI GIAN THUC THI KHI INSERT CAU ==================\n";
    DocFile(rootf1,vct_tree1,"data2.txt");
    cout << "\n================== THOI GIAN THUC THI KHI FINDNODE CAU ==================\n\n";
    double time = 0;
    for (int i = 0; i < vct_tree1.size(); i++)
    {
        start = clock();
        Find_Node(rootf1, vct_tree1[i]);
        end = clock();
        time += (double)(end - start) / (CLOCKS_PER_SEC);
        if (i == k * 100 - 1)
        {
            cout <<"Thoi gian tim "<< i+1<<" cau : " << time << "\n";
            cout << "Thoi gian trung binh: " << time / (i + 1) * 1000 << "(ms)\n\n";
            k++;
        }
    }
    cout << "\n================== THOI GIAN THUC THI KHI DELETE CAU ==================\n\n";
    time=0;
    k = 1;
    for (int i = 0; i < vct_tree1.size(); i++)
    {
        start = clock();      
        deleteNode(rootf1,vct_tree1[i]);
        end = clock();
        time+= (double)(end - start) / (CLOCKS_PER_SEC);
        if (i == k * 100-1)
        {
            cout << "Thoi gian xoa " << i + 1 << " cau : " << time << "\n";
            cout << "Thoi gian trung binh: " << time / (i + 1) * 1000 << "(ms)\n\n";
            k++;
        }
    }
    
    return 0;
}