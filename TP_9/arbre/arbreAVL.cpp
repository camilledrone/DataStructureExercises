#include<iostream>
#include <algorithm>
using namespace std;

template <typename Comparable>
class AVLTree
{
    public:
    AVLTree( ) {root=NULL;}
    AVLTree( const AVLTree & rhs ) {*this=rhs;}
    ~AVLTree( ) {makeEmpty();}

    bool isEmpty( ) const {return (root==NULL);}
    void makeEmpty( ) {makeEmpty(root);}
    
    void insert( const Comparable & x ) {insert(x,root, root);}

    const AVLTree & operator=( const AVLTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }

	friend ostream &operator<< (ostream& out, const AVLTree& arbre)
	{
        BinaryNode* rootTemp = arbre.root;
        out << "\nTYPE\t" << "PARENT\t" << "NOEUD\t" << "HAUTEUR\t" << endl;
        out << "____\t______\t_____\t_______" << endl;
        arbre.print(out, rootTemp, "R");
        return out;
	}

    private:

    // Type of nodes used in the tree
    struct BinaryNode
    {
       Comparable element;
       int height;
       BinaryNode *parent; // if the node is the root then its parent is itself
       BinaryNode *left;
       BinaryNode *right;

       BinaryNode( const Comparable & theElement, int hght, BinaryNode *pt, BinaryNode *lt, BinaryNode *rt )
         : element( theElement ), height(hght), parent(pt), left( lt ), right( rt ) { }
    };

    // Pointer to the tree root.
    BinaryNode *root;

/* 
    x
*/
	void print(ostream& out, BinaryNode * & t, string type) const
	{
        //on verifie que le pointeur est pas nul
        if (t != NULL) {

            if (t->parent == NULL) {
                out << type << "\t" << "- \t" << t->element << "\t" << t->height << endl;
            }
            else {
                out << type << "\t" << t->parent->element << "\t" << t->element << "\t" << t->height << endl;
            }

            if (t->left != NULL) {
                print(out, t->left, "G");
            }

            if (t->right != NULL) {
                print(out, t->right, "D");
            }
        }
	}

    // return the height of a node
    int getHeight(BinaryNode*& t)
    {
        if (t == NULL) {
            return -1;
        }
        else {
            return t->height;
        }
    }

    void actualizeHeight(BinaryNode*& t)
    {
        if (t->left == NULL && t->right == NULL) {
            t->height = 0;
        }
        else
        {
            if (t->left != NULL) {
                actualizeHeight(t->left);
            }

            if (t->right != NULL) {
                actualizeHeight(t->right);
            }
        }
        t->height = (std::max(getHeight(t->left), getHeight(t->right))) + 1;
    }

    /*
    * Function to perform a simple rotation to the right to balance an unbalance of a tree to the left (case #1)
    * The unbalance is at node t
    * - the left child of t becomes the new parent and adopts t, as t>t->left, t becomes the right child of the new parent
    * - the old right child of the new parent becomes the left child of t
    * - the new parent must be attached to the old parent of t
    */
    void rotationSimpleRight(BinaryNode*& t, BinaryNode*& greatParent)
    {

        cout << "rotation Simple Droite sur " << t->element << endl;

        BinaryNode* newParent = t->left;
        if (newParent->right != NULL) {
            newParent->right->parent = t;
        }
        t->left = newParent->right;
        newParent->right = t;
        t->parent = newParent;


        //we must remember to attach to the parent
        //if t is the root, the parent is the node itself
        //you have to see if you attach to the grandparent by the right or the left
        if (greatParent != t) {
            newParent->parent = greatParent;
            if (newParent->element < greatParent->element) {
                greatParent->left = newParent;
            }
            else {
                greatParent->right = newParent;
            }
            
        }
        else {
            this->root = newParent;
            newParent->parent = newParent;
            greatParent = newParent;
        }
        actualizeHeight(newParent);
    };


    /*
    * Function to perform a simple rotation to the left to re-balance a tree unbalance to the right (case #4)
    * The unbalance is at node t
    * - the right child of t becomes the new parent and adopts t, as t>t->left, t becomes the left child of the new parent
    * - the old left child of the new parent becomes the right child of t
    * - the new parent must be attached to the old parent of t
    */
    void rotationSimpleLeft(BinaryNode*& t, BinaryNode*& greatParent)
    {
        cout << "rotation Simple Gauche sur " << t->element << endl;
        BinaryNode* newParent = t->right;
        if (newParent->left != NULL) {
            newParent->left->parent = t;
        }
        t->right = newParent->left;
        newParent->left = t;
        t->parent = newParent;

        //we must remember to attach to the parent
        //if t is the root, the parent is the node itself
        //you have to see if you attach to the grandparent by the right or the left
        if (greatParent != t) {
            newParent->parent = greatParent;
            if (newParent->element < greatParent->element) {
                greatParent->left = newParent;
            }
            else {
                greatParent->right = newParent;
            }
        }
        else {
            this->root = newParent;
            newParent->parent = newParent;
            greatParent = newParent;
        }
        actualizeHeight(newParent);
    };


    /*
    * Function to perform a double rotation to the right to balance a tree unbalance to the left (case #2)
    * The unbalance is at node t
    * - single left rotation on the right child of t
    * - simple right rotation on t
    * - the new parent must be attached to the old parent of t
    */
    void rotationDoubleRight(BinaryNode*& t, BinaryNode*& greatParent)
    {
        cout << "rotation Double Droite sur " << t->element << endl;
        BinaryNode* temp = t;
        BinaryNode* k3 = t;
        BinaryNode* k2 = t->left;
        BinaryNode* k1 = k2->right;

        //rotation simple left
        if (k1->left != NULL) {
            k1->left->parent = k2;
        }
        k2->right = k1->left;
        k1->left = k2;
        k2->parent = k1;
        k1->parent = k3;
        k3->left = k1;

        //rotation simple right
        if (k1->right != NULL) {
            k1->right->parent = k3;
        }
        k3->left = k1->right;
        k3->parent = k1;
        k1->right = k3;

        t = k1;
        //we must remember to attach to the parent
        //if t (k3) is the root, the parent is the node itself
        if (greatParent != temp) {
            k1->parent = greatParent;

            if (k1->element < greatParent->element) {
                greatParent->left = k1;
            }
            else {
                greatParent->right = k1;
            }
        }
        else {
            this->root = k1;
            k1->parent = k1;
            greatParent = k1;
        }

        actualizeHeight(k1);
        
    };


    /*
    * Function to perform a double rotation to the left to re-balance a tree unbalance to the right (case #3)
    * The unbalance is at node t
    * - single right rotation on the right child of t
    * - simple left rotation on t
    * - the new parent must be attached to the old parent of t
    */
    void rotationDoubleLeft(BinaryNode*& t, BinaryNode*& greatParent)
    {

        cout << "rotation Double Gauche sur " << t->element << endl;

        BinaryNode* temp = t;
        BinaryNode* k3 = t;
        BinaryNode* k2 = t->right;
        BinaryNode* k1 = k2->left;

        //rotation simple right
        if (k1->right != NULL) {
            k1->right->parent = k2;
        }
        k2->left = k1->right;
        k1->right = k2;
        k2->parent = k1;
        k1->parent = k3;
        k3->right = k1;

        //rotation simple right
        if (k1->left != NULL) {
            k1->left->parent = k3;
        }
        k3->right = k1->left;
        k3->parent = k1;
        k1->left = k3;

        t = k1;
        //we must remember to attach to the parent
        //if t (k3) is the root, the parent is the node itself
        if (greatParent != temp) {
            k1->parent = greatParent;
            if (k1->element < greatParent->element) {
                greatParent->left = k1;
            }
            else {
                greatParent->right = k1;
            }
        }
        else {
            this->root = k1;
            k1->parent = k1;
            greatParent = k1;
        }

        actualizeHeight(k1);
 
    };


    // Insert an element x in the sub-tree t
    void insert( const Comparable & x, BinaryNode * &t, BinaryNode*& parent)
    {
        if (t == NULL)
        {
            cout << "Insertion de : " << x << endl;
            t = new BinaryNode(x, 0, parent, NULL, NULL);
        }
            
        else if (x < t->element)
        {
            //insertion at left
            insert( x, t->left, t );
            
            if (abs(getHeight(t->left) - getHeight(t->right)) == 2) //unbalance
            {
                if (x < t->left->element)
                {
                    rotationSimpleRight(t, parent);
                }
                else {
                    rotationDoubleRight(t, parent);
                }
            }
        }
            
        else if (t->element < x)
        {
            //insertion at right
            insert(x, t->right, t);
            
            if (abs(getHeight(t->left) - getHeight(t->right)) == 2) //unbalance
            {
                if (x > t->right->element)
                {
                    rotationSimpleLeft(t, parent);
                }
                else {
                    rotationDoubleLeft(t, parent);
                }
            }
        }
            
        else
            ;  
        actualizeHeight(t);
    }


    // Eliminates the sub-tree t
    void makeEmpty( BinaryNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    // Returns a copy of the subtree t
    BinaryNode* clone(BinaryNode* t) const
    {
        if (t == NULL)
            return NULL;
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }
};
