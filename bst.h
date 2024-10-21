#ifndef BST_H_
#define BST_H_

#include"renderermanager.h"
#include<thread>


template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;
    SDL_Renderer * rend;
    numberDrawer *num;
    int lvl;
    int pos;

	TreeNode<T>* succesor();

public:
	TreeNode(T, int, int, SDL_Renderer*, numberDrawer*);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	bool add(T, int= 1, int =1);
	bool find(T);
	void removeChilds();
    void DrawNode(SDL_Renderer*, numberDrawer);

	friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val, int lev, int ps, SDL_Renderer * ren, numberDrawer *nd) : value(val) , lvl(lev), pos(ps), left(NULL), right(NULL) {
    rend = ren;
    num = nd;
}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) : value(val), left(le), right(ri) {}

template <class T>
bool TreeNode<T>::add(T val, int lv , int ps) {
    BSTDrawUnder(rend, lvl, pos, val, *num);
    SDL_RenderPresent(rend);
    std::this_thread::sleep_for<int64_t, std::milli>(std::chrono::milliseconds(90));
    BSTEraseUnder(rend, lvl, pos, *num);
    SDL_Event windowEvent;


    if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT){
                return false;
            }

	if(val < value){
		if(left == NULL){
			TreeNode<T> *newnode = new TreeNode(val, lv +1 , ps*2 -1, rend, num);
			if(newnode == NULL) throw;

			left = newnode;

		}else{
			return left->add(val, lv +1 , ps*2 -1);
		}
	}else{
		if(right == NULL){
			TreeNode<T> *newnode = new TreeNode(val, lv +1 , ps*2, rend, num);
			if(newnode == NULL) throw;

			right = newnode;
			
		}else{
			return right->add(val, lv +1 , ps*2);
		}
	}
    return true;
}

template <class T>
bool TreeNode<T>::find(T val) {
	if(val == value) return true;
	if(right == NULL && left == NULL)
		return false;
	if(val < value){
		return left->find(val);
	}else{
		return right->find(val);
	}
}

template <class T>
TreeNode<T>* TreeNode<T>::succesor() {
	if(right == NULL) return this;
	else return right->succesor();
}


template <class T>
void TreeNode<T>::removeChilds() {
	if(left != NULL){
		left->removeChilds();
	}
	TreeNode<T> *victim = left;
	left = NULL;

	delete [] victim;

	if(right !=NULL){
		right->removeChilds();
	}
	victim = right;
	right = NULL;

	delete [] victim;
}

template <class T>
void TreeNode<T>::DrawNode(SDL_Renderer *renderer, numberDrawer nd){
    BSTDrawAt(renderer, lvl, pos, value, nd);
    if(left != NULL){
        left->DrawNode(renderer, nd);
    }
    if(right != NULL){
        right->DrawNode(renderer, nd);
    }
}


template <class T>
class BST {
private:
	TreeNode<T> *root;
    SDL_Renderer *renderer;
    numberDrawer *drawer;
    
public:
	BST();
	~BST();
	bool empty() const;
	bool add(T);
	bool find(T) const;
	void removeAll();
    void Draw(SDL_Renderer*);
    void SetRenderer(SDL_Renderer*);
    void SetNumDrawer(numberDrawer*);
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
bool BST<T>::add(T val) {
	if(empty()){
		TreeNode<T> *newnode = new TreeNode(val, 1, 1, renderer, drawer);

		if(newnode == NULL){
			throw;
		}
		root = newnode;
        return true;

	}else{
		return root->add(val);
	}
}


template <class T>
void BST<T>::removeAll() {	
	if(empty()) return;
	root->removeChilds();
	
	TreeNode<T> *victim = root;
	root = NULL;
	delete [] victim;
}

template <class T>
bool BST<T>::find(T val) const {
	return root->find(val);
}

template<class T>
void BST<T>::Draw(SDL_Renderer *renderer){
    root->DrawNode(renderer, *drawer);
}

template<class T>
void BST<T>::SetRenderer(SDL_Renderer* rend){
    renderer = rend;
}
template<class T>
void BST<T>::SetNumDrawer(numberDrawer* nb){
    drawer = nb;
}

bool orderBST(SDL_Renderer *renderer){
    bool runs = true;
    int BSTarray[] = {32, 16, 48, 56, 40, 24, 8, 4, 12, 20, 28, 36, 44, 52, 60, 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 
        63, 61, 59, 57, 55, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1};
    DrawBST(renderer);

    numberDrawer num("Comic Sans MS.ttf");

    BST<int> tree;
    tree.SetNumDrawer(&num);
    tree.SetRenderer(renderer);

    SDL_RenderPresent(renderer);

    for (int i = 0; i < 63; i++){    
        if(!tree.add(BSTarray[i])){
            runs = false;
            break;
        }
        tree.Draw(renderer);
        std::this_thread::sleep_for<int64_t, std::milli>(std::chrono::milliseconds(1000/35));
        SDL_RenderPresent(renderer);
    }

    tree.Draw(renderer);

    return runs;
 
}

#endif
