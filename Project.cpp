#include <iostream>
using namespace std;
class node
{
public:
    int data;
    node* left = NULL;
    node* right = NULL;
    node* parent = NULL;
    string color;
};
class RB_TREE:protected node
{
    node* root;
public:
    RB_TREE()
    {
        root=NULL;
    }
    node* GetRoot();
    void InsertNode(int stuff);
    void RB_Insert_Fixup(node* z);
    void RemoveNode(node* parent, node* curr, int stuff);
    void Remove(int stuff);
    void RB_Delete_Fixup(node* z);
    node* TreeSearch(int stuff);
    void LeftRotate(node* x);
    void RightRotate(node* x);
    void PreorderTraversal(node* temp);
    void PostorderTraversal(node *temp);
    void InorderTraversal(node *temp);

};
node* RB_TREE::GetRoot()
{
    return root;
}
void RB_TREE:: InorderTraversal(node *temp)
{
    if(!temp)
    {
        return;
    }
    InorderTraversal(temp->left);
    cout << "--> " << temp->data << "<" << temp->color << ">";
    InorderTraversal(temp->right);
}
void RB_TREE:: PostorderTraversal(node *temp)
{
    if(!temp)
    {
        return;
    }
    PostorderTraversal(temp->left);
    PostorderTraversal(temp->right);
    cout << "--> " << temp->data << "<" << temp->color << ">";
}
void RB_TREE:: PreorderTraversal(node* temp)
{
    if(!temp)
    {
        return;
    }
    cout << "--> " << temp->data << "<" << temp->color << ">";
    PreorderTraversal(temp->left);
    PreorderTraversal(temp->right);
}
void RB_TREE:: RightRotate(node* x)
{
    node* nw_node = new node();
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
void RB_TREE:: LeftRotate(node* x)
{
    node* nw_node = new node();
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
node* RB_TREE:: TreeSearch(int stuff)
{
    node* temp = GetRoot();
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
void RB_TREE:: RB_Delete_Fixup(node* z)
{
    while(z->data != root->data && z->color == "BLACK")
    {
        //initiating sibbling
        node* sibling = GetRoot();
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
void RB_TREE:: Remove(int stuff)
{
    //going to the required node
    node* temp = root;
    node* parent = temp;
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
void RB_TREE:: RemoveNode(node* parent, node* curr, int stuff)
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
            int swap = curr->data;
            curr->data = curr->left->data;
            curr->left->data = swap;
            RemoveNode(curr, curr->right, stuff);
        }
        //if the node to be deleted has
        //only right child
        else if(curr->left == nullptr && curr->right != nullptr)
        {
            int swap = curr->data;
            curr->data = curr->right->data;
            curr->right->data = swap;
            RemoveNode(curr, curr->right, stuff);
        }
        //if the node to be deleted had two children
        else
        {
            bool flag = false;
            node* temp = curr->right;
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
            int swap = curr->data;
            curr->data = temp->data;
            temp->data = swap;
            RemoveNode(parent, temp, swap);
        }
    }
}
void RB_TREE:: RB_Insert_Fixup(node* z)
{
    //we need to alter the tree only
    // if the parent is red
    while(z->parent->color == "RED")
    {
        node* grandparent = z->parent->parent;
        node* uncle = GetRoot();
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
void RB_TREE:: InsertNode(int stuff)
{
    //normal bst insertion
    if(root == NULL)
    {
        //rootnode is always black
        root = new node();
        root->data = stuff;
        root->parent = nullptr;
        root->color = "BLACK";
        cout << "Element inserted.\n";
    }
    else
    {
        node* linker = GetRoot();
        node* newnode = new node();
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
    cout << "\n8. Exit.";
    cout << "\n__________________________________________";
    cout << "\nYour Choice -- \n";
}
void subq(RB_TREE *current)
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
    int option,tree_no=0, i;
    RB_TREE *list[100];
    RB_TREE current, *temp;
    while(1)
    {
        cout<<"1.CREATE NEW TREE\n2.USE EXISTING TREE\n3.EXIT\n";
        cin>>option;
        if(option==1)
        {
            temp=new RB_TREE() ;
            list[tree_no]=temp;
            tree_no++;
            cout<<"new tree created with number "<<tree_no<<endl;
        }
        else if(option==2)
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
