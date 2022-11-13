#include<iostream>
using namespace std;

template <typename Comparable>
class BinarySearchTree
{
    public:
    BinarySearchTree( ) {root=NULL;}
    BinarySearchTree( const BinarySearchTree & rhs ) {*this=rhs;}
    ~BinarySearchTree( ) {makeEmpty();}

    bool isEmpty( ) const {return (root==NULL);}
    void makeEmpty( ) {makeEmpty(root);}
    
    void insert( const Comparable & x ) {insert(x,root);}
    void remove( const Comparable & x ) {remove(x,root);}
    bool contains( const Comparable & x ) const {return contains(x,root);}
    
    const Comparable & findMin( ) const {return findMin(root)->element;}
    const Comparable & findMax( ) const {return findMax(root)->element;}

    const BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }

	friend ostream &operator<< (ostream& out, const BinarySearchTree& arbre)
	{
		BinaryNode* rootTemp = arbre.root;
		arbre.imprimer(out, rootTemp);
		return out;
	}

    private:

    // Type de noeuds utilisés dans l'arbre
    struct BinaryNode
    {
       Comparable element;
       BinaryNode *left;
       BinaryNode *right;

       BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
         : element( theElement ), left( lt ), right( rt ) { }
    };

    // Pointeur vers la racine de l'arbre.
    BinaryNode *root;

/* 
    Imprimer dans le flux (out), tous les elements de l'arbre en ordre croissant!
    principe : on balaye de gauche à droite, tant qu'il y a des enfants à gauche, ils sont nécessairement plus petits et on doit aller les regarder d'abord.
*/
	void imprimer(ostream& out, BinaryNode * & t) const
	{
        //on verifie que le pointeur est pas nul
        if (t != NULL) {

            // les enfants à gauche sont forcément plus petits
            if (t->left != NULL) {
                imprimer(out, t->left);
            }

            //les enfants à droite sont forcement plus grand, donc avant de les imprimer on imprime le noeud courant
            out << t->element << endl;
            if (t->right != NULL) {
                imprimer(out, t->right);
            }
        }
	}


    // Insére un élément x dans le sous arbre t
    void insert( const Comparable & x, BinaryNode * &t )
    {
        if( t == NULL )
            t = new BinaryNode( x, NULL, NULL );
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // x est déjà dans l'arbre; on ne fait rien
    }

    // Enleve un élément x dans le sous-arbre t
    void remove(const Comparable & x, BinaryNode * & t )
    {
        if( t == NULL )
            return;   // x n'est pas dans l'arbre; on ne fait rien
        if( x < t->element )
            remove( x, t->left );
        else 
             if( t->element < x )
                 remove( x, t->right );
             else 
                  if( t->left != NULL && t->right != NULL ) // Deux enfants
                  {
                      t->element = findMin( t->right )->element;
                      remove( t->element, t->right );
                  }
                  else    // Au plus un enfant
                  {
                       BinaryNode *oldNode = t;
                       t = ( t->left != NULL ) ? t->left : t->right;
                       delete oldNode;
                  }
    }


    // Trouve le plus petit élément dans le sous-arbre  t
    // (méthode récursive)
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if (t == NULL) {
            return t;
        }
        if (t->left == NULL) {
            return t;
        }
        // un enfant a gauche est forcement plus petit
        else {
            return findMin(t->left);
        }
        
    }

    // Trouve le plus grand élément dans le sous-arbre  t
    // (méthode itérative)
    BinaryNode * findMax( BinaryNode *t ) const
    {
        BinaryNode* max = NULL;
        // un enfant qui se truve a droite est forcement plus grand, 
        //donc tant qu'il reste un enfant a droite il y a en fait un element plus grand que le courant
        while (t != NULL) {
            max = t;
            t = t->right;
        }
        return max;
    }


    // Cherche x dans le sous-arbre  t
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if (t == NULL) {
            return false;
        }

        //utilise le principe qu'un enfant a gauche, et respectivement a droite, est plus petit, repsectivement plus grand
        if (x < t->element) {
            return contains(x, t->left);
        }
        if (x > t->element) {
            return contains(x, t->right);
        }

        else {
            return true;
        }
    }

    // Élimine le sous-arbre t
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

    // Retourne une copie du sous-arbre t
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
        return new BinaryNode( t->element, clone( t->left ), clone( t->right ) );
    }
};
