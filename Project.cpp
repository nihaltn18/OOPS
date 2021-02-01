#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
template<typename t>
class node
{
public:
    t data;
    node* left = NULL;
    node* right = NULL;
    node* parent = NULL;
    string color;
};
template<typename t>
class RB_TREE
{
    node<t>* root;
public:
    RB_TREE()
    {
        root=NULL;
    }
    node<t>* GetRoot();
    void InsertNode(t stuff);
    void RB_Insert_Fixup(node<t>* z);
    void RemoveNode(node<t>* parent, node<t>* curr, t stuff);
    void Remove(t stuff);
    void RB_Delete_Fixup(node<t>* z);
    node<t>* TreeSearch(t stuff);
    void LeftRotate(node<t>* x);
    void RightRotate(node<t>* x);
    void PreorderTraversal(node<t>* temp);
    void PostorderTraversal(node<t> *temp);
    void InorderTraversal(node<t> *temp);
    void Insert_postorder(node<t>* temp);
    void Insert_preorder(node<t>* temp);
    void Insert_inorder(node<t>* temp);
};
string str;
template<typename t>
node<t>* RB_TREE<t>::GetRoot()
{
    return root;
}
template<typename t>
void RB_TREE<t>::Insert_postorder(node<t> *temp)
{
    if(!temp)
    return;
    Insert_postorder(temp->left);
    Insert_postorder(temp->right);
    ostringstream st;
    st<<temp->data;
    string s=st.str();
    str=str+"--> "+s+"<"+temp->color+">";
}
template<typename t>
void RB_TREE<t>::Insert_preorder(node<t> *temp)
{
    if(!temp)
    return;
    ostringstream st;
    st<<temp->data;
    string s=st.str();
    str=str+"--> "+s+"<"+temp->color+">";
    Insert_preorder(temp->left);
    Insert_preorder(temp->right);
}
template<typename t>
void RB_TREE<t>::Insert_inorder(node<t> *temp)
{
    if(!temp)
    return;
    Insert_inorder(temp->left);
    ostringstream st;
    st<<temp->data;
    string s=st.str();
    str=str+"--> "+s+"<"+temp->color+">";
    Insert_inorder(temp->right);
}
template<typename t>
void RB_TREE<t>:: InorderTraversal(node<t> *temp)
{
    if(!temp)
    {
        return;
    }
    InorderTraversal(temp->left);
    cout << "--> " << temp->data << "<" << temp->color << ">";
    InorderTraversal(temp->right);
}
template<typename t>
void RB_TREE<t>:: PostorderTraversal(node<t> *temp)
{
    if(!temp)
    {
        return;
    }
    PostorderTraversal(temp->left);
    PostorderTraversal(temp->right);
    cout << "--> " << temp->data << "<" << temp->color << ">";
}
template<typename t>
void RB_TREE<t>:: PreorderTraversal(node<t>* temp)
{
    if(!temp)
    {
        return;
    }
    cout << "--> " << temp->data << "<" << temp->color << ">";
    PreorderTraversal(temp->left);
    PreorderTraversal(temp->right);
}
template<typename t>
void RB_TREE<t>:: RightRotate(node<t>* x)
{
    node<t>* nw_node = new node<t>();
    if(x->left->right)
    {
        nw_node->left = x->left->right;
    }
    nw_node->right = x->right;
    nw_node->data = x->data;
    nw_node->color = x->color;

    x->data = x->left->data;
    x->color = x->left->color;

    x->right = nw_node;
    if(nw_node->left)
    {
        nw_node->left->parent = nw_node;
    }
    if(nw_node->right)
    {
        nw_node->right->parent = nw_node;
    }
    nw_node->parent = x;

    if(x->left->left)
    {
        x->left = x->left->left;
    }
    else
    {
        x->left = nullptr;
    }

    if(x->left)
    {
        x->left->parent = x;
    }
}
template<typename t>
void RB_TREE<t>:: LeftRotate(node<t>* x)
{
    node<t>* nw_node = new node<t>();
    if(x->right->left)
    {
        nw_node->right = x->right->left;
    }
    nw_node->left = x->left;
    nw_node->data = x->data;
    nw_node->color = x->color;
    x->data = x->right->data;

    x->left = nw_node;
    if(nw_node->left)
    {
        nw_node->left->parent = nw_node;
    }
    if(nw_node->right)
    {
        nw_node->right->parent = nw_node;
    }
    nw_node->parent = x;

    if(x->right->right)
    {
        x->right = x->right->right;
    }
    else
    {
        x->right = nullptr;
    }

    if(x->right)
    {
        x->right->parent = x;
    }
}
template<typename t>
node<t>* RB_TREE<t>:: TreeSearch(t stuff)
{
    node<t>* temp = GetRoot();
    if(temp == nullptr)
    {
        return nullptr;
    }
    while(temp)
    {
        if(stuff == temp->data)
        {
            return temp;
        }
        else if(stuff < temp->data)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }
    return nullptr;
}
template<typename t>
void RB_TREE<t>:: RB_Delete_Fixup(node<t>* z)
{
    while(z->data != root->data && z->color == "BLACK")
    {
        //initiating sibbling
        node<t>* sibling = GetRoot();
        //if node to be deleted is to
        //the left of the parent
        if(z->parent->left == z)
        {
            if(z->parent->right)
            {
                //setting up sibbling node
                //for the node to be deleted
                sibling = z->parent->right;
            }
            //if parent of node to be deleted
            //has two children
            if(sibling)
            {
                //CASE -- 1
                if(sibling->color == "RED")
                {
                    sibling->color = "BLACK";
                    z->parent->color = "RED";
                    LeftRotate(z->parent);
                    sibling = z->parent->right;
                }
                //CASE -- 2 if sibbling is leaf
                if(sibling->left == nullptr && sibling->right == nullptr)
                {
                    sibling->color = "RED";
                    z = z->parent;
                }
                //if sibbling is double black
                else if(sibling->left->color == "BLACK" && sibling->right->color == "BLACK")
                {
                    sibling->color = "RED";
                    z = z->parent;
                }
                //CASE -- 3
                else if(sibling->right->color == "BLACK")
                {
                    sibling->left->color = "BLACK";
                    sibling->color = "RED";
                    RightRotate(sibling);
                    sibling = z->parent->right;
                }
                else
                {
                    sibling->color = z->parent->color;
                    z->parent->color = "BLACK";
                    if(sibling->right)
                    {
                        sibling->right->color = "BLACK";
                    }
                    LeftRotate(z->parent);
                    z = root;
                }
            }
        }
        //if node to be deleted
        //is to the right of parent
        else
        {
            //if node to be deleted is to
            //the left of the parent
            if(z->parent->right == z)
            {
                //setting up sibbling
                if(z->parent->left)
                {
                    sibling = z->parent->left;
                }
                //if parent of node to be
                //deleted has two children
                if(sibling)
                {
                    //CASE -- 1
                    if(sibling->color == "RED")
                    {
                        sibling->color = "BLACK";
                        z->parent->color = "RED";
                        RightRotate(z->parent);
                        sibling = z->parent->left;
                    }
                    //CASE -- 2 if sibbling is leaf
                    if(sibling->left == nullptr && sibling->right == nullptr)
                    {
                        sibling->color = "RED";
                        z = z->parent;
                    }
                    //if sibbling is double black
                    else if(sibling->left->color == "BLACK" && sibling->right->color == "BLACK")
                    {
                        sibling->color = "RED";
                        z = z->parent;
                    }
                    //CASE -- 3
                    else if(sibling->left->color == "BLACK")
                    {
                        sibling->right->color = "BLACK";
                        sibling->color = "RED";
                        RightRotate(sibling);
                        sibling = z->parent->left;
                    }
                    else
                    {
                        sibling->color = z->parent->color;
                        z->parent->color = "BLACK";
                        if(sibling->left)
                        {
                            sibling->left->color = "BLACK";
                        }
                        LeftRotate(z->parent);
                        z = root;
                    }
                }
            }

        }
    }
    z->color = "BLACK";
}
template<typename t>
void RB_TREE<t>:: Remove(t stuff)
{
    //going to the required node
    node<t>* temp = root;
    node<t>* parent = temp;
    bool flag = false;
    if(!temp)
    {
        RemoveNode(NULL, NULL, stuff);
    }
    while(temp)
    {
        if(stuff == temp->data)
        {
            flag = true;
            RemoveNode(parent, temp, stuff);
            break;
        }
        else if(stuff < temp->data)
        {
            parent = temp ;
            temp = temp->left;
        }
        else
        {
            parent = temp ;
            temp = temp->right;
        }
    }
    if(!flag)
    {
        cout << "\nElement doesn't exist in the table";
    }
}
template<typename t>
void RB_TREE<t>::RemoveNode(node<t>* parent, node<t>* curr, t stuff)
{
    if(curr == nullptr)
    {
        return;
    }
    if(curr->data == stuff)
    {
        if(curr->left == nullptr && curr->right == nullptr)
        {
            //only if the node to be
            //deleted is root and root is
            //is the only element in the
            //tree
            if(parent->data == curr->data)
            {
                root = nullptr;
            }
            //if the child of the parent
            //is right of parent
            else if(parent->right == curr)
            {
                RB_Delete_Fixup(curr);
                parent->right = nullptr;
            }
            //if child of the parent is
            //is left of parent
            else
            {
                RB_Delete_Fixup(curr);
                parent->left = nullptr;
            }
        }
        //if the node to be deleted has
        //only left child
        else if(curr->left != nullptr && curr->right == nullptr)
        {
            t swap = curr->data;
            curr->data = curr->left->data;
            curr->left->data = swap;
            RemoveNode(curr, curr->right, stuff);
        }
        //if the node to be deleted has
        //only right child
        else if(curr->left == nullptr && curr->right != nullptr)
        {
            t swap = curr->data;
            curr->data = curr->right->data;
            curr->right->data = swap;
            RemoveNode(curr, curr->right, stuff);
        }
        //if the node to be deleted had two children
        else
        {
            bool flag = false;
            node<t>* temp = curr->right;
            while(temp->left)
            {
                flag = true;
                parent = temp;
                temp = temp->left;
            }
            if(!flag)
            {
                parent = curr;
            }
            t swap = curr->data;
            curr->data = temp->data;
            temp->data = swap;
            RemoveNode(parent, temp, swap);
        }
    }
}
template<typename t>
void RB_TREE<t>:: RB_Insert_Fixup(node<t>* z)
{
    //we need to alter the tree only
    // if the parent is red
    while(z->parent->color == "RED")
    {
        node<t>* grandparent = z->parent->parent;
        node<t>* uncle = GetRoot();
        //if new node is to the left
        //of grandparent
        if(z->parent == grandparent->left)
        {
            if(grandparent->right)
            {
                //check if the uncle is not null
                //and assign it to uncle variable
                uncle = grandparent->right;
            }
            //if uncle is red
            if(uncle->color == "RED")
            {
                z->parent->color = "BLACK";
                uncle->color = "BLACK";
                grandparent->color = "RED";
                if(grandparent->data != root->data)
                {
                    z = grandparent;
                }
                else
                {
                    break;
                }
            }
            //if new node is black and inserted to
            //left-right of grandparent
            //we need to do left rotate
            else if(z == grandparent->left->right)
            {
                LeftRotate(z->parent);
            }
            //else if new node is black and inserted
            //to left-left of grandparent
            //we need to do right rotate
            //and also need to recolour
            //and recheck for all preceeding nodes
            else
            {
                z->parent->color = "BLACK";
                grandparent->color = "RED";
                RightRotate(grandparent);
                if(grandparent->data != root->data)
                {
                    z = grandparent;
                }
                else
                {
                    break;
                }
            }
        }
        //if new node is to the right
        //of grandparent
        else
        {
            if(grandparent->left)
            {
                //check if the uncle is not null
                //and assign it to uncle variable
                uncle = grandparent->left;
            }
            //if uncle is red
            if(uncle->color == "RED")
            {
                z->parent->color = "BLACK";
                uncle->color = "BLACK";
                grandparent->color = "RED";
                if(grandparent->data != root->data)
                {
                    z = grandparent;
                }
                else
                {
                    break;
                }
            }
            //if new node is black and is right-left of grand parent
            //we need to do right rotate
            else if(z == grandparent->right->left)
            {
                RightRotate(z->parent);
            }
            //else if new node is black and inserted
            //to right-right of grandparent
            //we need to do left rotate
            //and also need to recolour
            //and recheck for all preceeding nodes
            else
            {
                z->parent->color = "BLACK";
                grandparent->color = "RED";
                LeftRotate(grandparent);
                if(grandparent->data != root->data)
                {
                    z = grandparent;
                }
                else
                {
                    break;
                }
            }
        }
    }
    //finally set color of root to black
    root->color = "BLACK";
}
template<typename t>
void RB_TREE<t>:: InsertNode(t stuff)
{
    //normal bst insertion
    if(root == NULL)
    {
        //rootnode is always black
        root = new node<t>();
        root->data = stuff;
        root->parent = nullptr;
        root->color = "BLACK";
        cout << "Element inserted.\n";
    }
    else
    {
        node<t>* linker = GetRoot();
        node<t>* newnode = new node<t>();
        newnode->data = stuff;
        while(linker != nullptr)
        {
            if(linker->data > stuff)
            {
                if(linker->left == nullptr)
                {
                    linker->left = newnode;
                    newnode->color = "RED";
                    newnode->parent = linker;
                    cout << "Element inserted.\n";
                    break;
                }
                else
                {
                    linker = linker->left;
                }
            }
            else
            {
                if(linker->right == nullptr)
                {
                    linker->right = newnode;
                    newnode->color = "RED";
                    newnode->parent = linker;
                    cout << "Element inserted.\n";
                    break;
                }
                else
                {
                    linker = linker->right;
                }
            }
        }
        //we need to alter the tree
        //according to the conditions
        //of red-black tree
        RB_Insert_Fixup(newnode);
    }
}
void menu()
{
    cout << "\n__________________________________________";
    cout << "\n\n  --HEIGHT BALANCED BINARY SEARCH TREE--";
    cout << "\n          --(Red-Black-Tree)--";
    cout << "\n__________________________________________";
    cout << "\n\n1. Insert elements into the tree.";
    cout << "\n2. Search for an element.";
    cout << "\n3. Remove an element from the tree.";
    cout << "\n4. PRE-ORDER Tree-Walk.";
    cout << "\n5. POST-ORDER Tree-Walk.";
    cout << "\n6. IN-ORDER Tree-Walk.";
    cout << "\n7. to change the tree.";
    cout << "\n8. to insert the present tree into a .txt file.";
    cout << "\n9. Exit.";
    cout << "\n__________________________________________";
    cout << "\nYour Choice -- \n";
}
template<typename t>
void subq(RB_TREE<t> *current)
{
    int sub_option, i;
    while(1)
    {
        menu() ;
        cin>>sub_option;
        if(sub_option==1)
        {
            cout<<"enter the element that you want to insert\nand enter '-1' when you want to stop inserting\n";
            while(1)
            {
                t i;
                cin>>i;
                if(i==-1)
                {
                    break;
                }
                else
                {
                    current->InsertNode(i);
                }
            }
        }
        else if(sub_option==2)
        {
            t i;
            cout<<"enter the element that you want to search for\n";
            cin>>i;
            if(current->TreeSearch(i))
            {
                cout<<"given element is present in the tree\n";
            }
            else
            {
                cout<<"given element is not present in the tree\n";
            }
        }
        else if(sub_option==3)
        {
            t i;
            cout<<"enter the element that you want to delete\n";
            cin>>i;
            current->Remove(i) ;
        }
        else if(sub_option==4)
        {
            current->PreorderTraversal(current->GetRoot()) ;
        }
        else if(sub_option==5)
        {
            current->PostorderTraversal(current->GetRoot()) ;
        }
        else if(sub_option==6)
        {
            current->InorderTraversal(current->GetRoot()) ;
        }
        else if(sub_option==7)
        {
            return;
        }
        else if(sub_option==8)
        {
            int i;
            cout<<"1.postorder\n2.preorder\n3.inorder\n";
            cin>>i;
            if(i==1)
            {
                str="";
                current->Insert_postorder(current->GetRoot());
                cout<<"enter the name of the file in which you want to save the tree\n";
                string s;
                cin>>s;
                ofstream myfile(s,ios::app);
                myfile<<str;
                str="";
                myfile.close();
                cout<<"file with the given name is created with all the current tree elements in postorder format\n";
            }
            else if (i==2)
            {
                str="";
                current->Insert_preorder(current->GetRoot());
                cout<<"enter the name of the file in which you want to save the tree\n";
                string s;
                cin>>s;
                ofstream myfile(s,ios::app);
                myfile<<str;
                str="";
                myfile.close();
                cout<<"file with the given name is created with all the current tree elements in preorder format\n";
            }
            else if(i==3)
            {
                str="";
                current->Insert_inorder(current->GetRoot());
                cout<<"enter the name of the file in which you want to save the tree\n";
                string s;
                cin>>s;
                ofstream myfile(s,ios::app);
                myfile<<str;
                str="";
                myfile.close();
                cout<<"file with the given name is created with all the current tree elements in inorder format\n";
            }
            else
            {
                cout<<"invalid input";
            }
            
        }
        else if(sub_option==9)
        {
            exit(0) ;
        }
        else
        {
            cout<<"enter a valid input\n";
        }
    }
}
int main()
{
    /*
    .InsertNode(input) ;
    .TreeSearch(input) ;
    .Remove(input) ;
    .PreorderTraversal(.GetRoot()) ;
    .postorderTraversal(.GetRoot()) ;
    .InorderTraversal(.GetRoot()) ;
    */
    int option,tree_no=0, i,tree_no2=0;
    RB_TREE<int> *list[100];
    RB_TREE<float> *list2[100];
    RB_TREE<int> current, *temp;
    RB_TREE<float> current2, *temp2;
    while(1)
    {
        cout<<"1.CREATE NEW TREE\n2.USE EXISTING TREE\n3.EXIT\n";
        cin>>option;
        if(option==1)
        {
            cout<<"1.integer tree\n2.float tree\n";
            int k;
            cin>>k;
            if(k==1)
            {
                temp=new RB_TREE<int>();
                list[tree_no]=temp;
                tree_no++;
                cout<<"new tree created with number "<<tree_no<<endl;
            }
            else if(k==2)
            {
                temp2=new RB_TREE<float>();
                list2[tree_no2]=temp2;
                tree_no2++;
                cout<<"new tree created with number "<<tree_no2<<endl;
            }
            else
            {
                cout<<"invalid option\n";
            }
            
        }
        else if(option==2)
        {
            cout<<"1.integer tree\n2.float tree\n";
            int k;
            cin>>k;
            if(k==1)
            {
                cout<<"enter the tree number\n";
                cin>>i;
                if(tree_no>=i)
                {
                    subq(list[i-1]) ;
                }
                else
                    cout<<"tree not found\n";
            }
            else if (k==2)
            {
                cout<<"enter the tree number\n";
                cin>>i;
                if(tree_no2>=i)
                {
                    subq(list2[i-1]) ;
                }
                else
                    cout<<"tree not found\n";
            }
        }
        else if(option==3)
        {
            break;
        }
        else
        {
            cout<<"please enter a valid input\n";
        }
    }
}
