/*
 * bst.h
 *
 * Paulina Almada Martinez (A01710029)
 * 9/10/2023
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

template <class T> class Node;

template <class T> class BST;

/* FUNCIONES NODE */
template<class T>
class Node {
    private:
        T value;
        Node<T> *left, *right;

    public:
        Node(T);
        Node(T, Node<T>*, Node<T>*);
        void add(T);
        void preorder(stringstream&) const;
        void inorder(stringstream&) const;
        void postorder(stringstream&) const;
        void levelorder(stringstream&);
        int height(Node<T>* node);
        void ancestors(T, stringstream&) const;
        int whatlevelamI(T, const Node<T>*, int) const;
        void removeChilds();

        friend class BST<T>; 
};

//Constructores
template<class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template<class T>
Node<T>::Node(T val, Node<T>* left, Node<T>* right) : value(val), left(left), right(right) {}

/* FUNCIONES AUXILIARES */

template<class T>
void Node<T>::add(T val){
    if(val < value){
        if(left != 0){
            left->add(val);
        } else{
            left = new Node<T>(val);
        }
    } else if(val > value){
        if(right != 0){
            right->add(val);
        } else{
            right = new Node<T>(val);
        }
    }
}

template<class T>
void Node<T>::preorder(stringstream& aux) const{
    aux << value;
    if(left != 0){
        aux << " ";
        left->preorder(aux);
    }
    if(right != 0){
        aux << " ";
        right->preorder(aux);
    }
}

template<class T>
void Node<T>::inorder(stringstream& aux) const{
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template<class T>
void Node<T>::postorder(stringstream& aux) const{
    if(left != 0){
        left->postorder(aux);
    }

    if(right != 0){
        right->postorder(aux);
    }
	
    if (aux.tellp() != 1) {
		aux << " ";
	}
    aux << value;
}

template<class T>
void Node<T>::levelorder(stringstream& aux){
    queue<Node<T>*> auxQueue;

    auxQueue.push(this);

    while(!auxQueue.empty()){
        Node<T>* current = auxQueue.front();
        auxQueue.pop();

        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << current->value;

        if (current->left != 0) {
            auxQueue.push(current->left);
        }

        if (current->right != 0) {
            auxQueue.push(current->right);
        }
    }
}

template<class T>
int Node<T>::height(Node<T>* node){
    if(node == 0){
        return 0; //árbol está vacío
    }

    int left = height(node->left);
    int right = height(node->right);

    return max(left, right) + 1;
}

template<class T>
void Node<T>::ancestors(T val, stringstream& aux) const{
    if(value == val){
		return;
	} else if(val < value){
        if(left != 0){
             if (aux.tellp() != 1) {
                aux << " ";
        }
        aux << value;
        left->ancestors(val, aux);
        } else{
            aux.str("");
            aux << "[";
            return;
        }
	} else if(val > value){
        if(right != 0){
            if (aux.tellp() != 1) {
                aux << " ";
        }
        aux << value;
        right->ancestors(val, aux);
        } else {
            aux.str("");
            aux << "[";
            return;
        }
	}   
}

template<class T>
int Node<T>::whatlevelamI(T val, const Node<T>* current, int level) const{
    if(current == 0){
        return 0; //valor no se encuentra en el árbol
    }

    if(val == current->value){
        return level+1;
    }

    if(val < current->value){
        return whatlevelamI(val, current->left, level+1);
    }

    return whatlevelamI(val, current->right, level+1);
}

template<class T>
void Node<T>::removeChilds(){
    if(left != 0){
        left->removeChilds();
        delete left;
        left = 0;
    } else if(right != 0){
        right->removeChilds();
        delete right;
        right = 0;
    }
}

/* FUNCIONES BST */
template<class T>
class BST{
    private:
        Node<T>* root;

    public:
        BST();
        ~BST();
        bool empty() const;
        void add(T);
        string visit() const;
        int height() const;
        string ancestors(T) const;
        int whatlevelamI(T) const;
        void removeAll();
};

//Constructor
template<class T>
BST<T>::BST() : root(0) {}

//Destructor
template<class T>
BST<T>::~BST(){
    removeAll();
}

/* FUNCIONES AUXILIARES */
template<class T>
bool BST<T>::empty() const{
    return (root != 0);
}

template<class T>
void BST<T>::add(T val){
    if(root == 0){
        root = new Node<T>(val);
    } else{
        root->add(val);
    }
}

/* FUNCIONES DE LA TAREA */

template<class T>
string BST<T>::visit() const{
	stringstream aux, aux2, aux3, aux4;
    
    aux << "[";
    root->preorder(aux);
    aux << "]" <<endl;

    aux2 << "[";
    root->inorder(aux2);
    aux2 << "]" << endl;

    aux3 << "[";
    root->postorder(aux3);
    aux3 << "]" << endl;

	aux4 << "[";
	root->levelorder(aux4);
	aux4 << "]";

    aux << aux2.str() << aux3.str() << aux4.str(); 
    return aux.str();
}

template<class T>
int BST<T>::height() const{
    if(root != 0){
        return root->height(root);
    }
    return 0; //árbol está vacío
}

template<class T>
string BST<T>::ancestors(T val) const{
    stringstream aux;
    aux << "[";
    if(root != 0){
        root->ancestors(val, aux);
    }
    aux << "]";
    return aux.str();
}

template<class T>
int BST<T>::whatlevelamI(T val) const{
    return root->whatlevelamI(val, root, 0);
}

template<class T>
void BST<T>::removeAll(){
	if(!empty()){
		root->removeChilds();
		delete root;
		root = 0;
	}
}

#endif /* BST_H_ */
