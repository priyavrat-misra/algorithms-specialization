#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
private:
	Node* root = nullptr;
	Node* push(int& val, Node* root) {
		if (!root)
			return new Node(val);
		else if (val <= root -> val)
			root -> left = push(val, root -> left);
		else
			root -> right = push(val, root -> right);
		
		return root;
	}

	Node* pop(int& val, Node* root) {
		if (!root)
			return nullptr;
		else if (val < root -> val)
			root -> left = pop(val, root -> left);
		else if (val > root -> val)
			root -> right = pop(val, root -> right);
		else { // found node to delete
			if (!root -> left && !root -> right) { // Case 1: No child 
				delete root;
				return nullptr;
			} else if (!root -> left) { // Case 2: One child (right)
				Node* t = root;
				root = root -> right;
				delete t;
			} else if (!root -> right) { // Case 2: One child (left)
				Node* t = root;
				root = root -> left;
				delete t;
			} else { // Case 3: Two children
				Node* t = findMin(root -> right);
				root -> val = t -> val;
				root -> right = pop(t -> val, root -> right);
			}
		}
		return root;
	}

	Node* find(int& val, Node* root) {
		if (!root)
			return nullptr;
		else if (val < root -> val)
			return find(val, root -> left);
		else if (val > root -> val)
			return find(val, root -> right);
		else
			return root;
	}

	Node* findMin(Node* root) {
		if (!root -> left)
			return root;

		return findMin(root -> left);
	}

	Node* findMax(Node* root) {
		if (!root -> right)
			return root;

		return findMax(root -> right);
	}

	Node* getPredecessor(Node* node) {
		if (!node)
			return nullptr;
		else if (node -> left) // Case 1 : left subtree exists
			return findMax(node -> left);
		else {  // Case 2: no left subtree
			// return nearest ancestor for which
			// current node would be in right subtree
			// (nearest ancestor with value
			// less than current node)
			Node* ancestor = this -> root;
			Node* predecessor = nullptr;
			while (ancestor != node) {
				if (node -> val >= ancestor -> val)
					predecessor = ancestor,
					ancestor = ancestor -> right;
				else
					ancestor = ancestor -> left;
			}
			return predecessor;
		}
	}

	Node* getSuccessor(Node* node) {
		if (!node)
			return nullptr;
		else if (node -> right) // Case 1: right subtree exists
			return findMin(node -> right);
		else {  // Case 2: no right subtree
			// return nearest ancestor for which
			// current node would be in left subtree
			// (nearest ancestor with value
			// greater than current code)
			Node* ancestor = this -> root;
			Node* successor = nullptr;
			while (ancestor != node) {
				if (node -> val <= ancestor -> val)
					successor = ancestor,
					ancestor = ancestor -> left;
				else
					ancestor = ancestor -> right;
			}
			return successor;
		}
	}

	void preOrder(Node* root) {
		if (root) {
			cout << " " << root -> val;
			preOrder(root -> left);
			preOrder(root -> right);
		}
	}

	void inOrder(Node* root) {
		if (root) {
			inOrder(root -> left);
			cout << " " << root -> val;
			inOrder(root -> right);
		}
	}

	void postOrder(Node* root) {
		if (root) {
			postOrder(root -> left);
			postOrder(root -> right);
			cout << " " << root -> val;
		}
	}

	void levelOrder() {
		queue<Node*> q;
		q.push(this -> root);
		while (!q.empty()) {
			Node* f = q.front();
			q.pop();
			cout << " " << f -> val;
			if (f -> left)
				q.push(f -> left);
			if (f -> right)
				q.push(f -> right);
		}
	}

	void deleteBST(Node* root) { // post order traversal
		if (root) {
			deleteBST(root -> left);
			deleteBST(root -> right);
			delete root;
		}
	}
public:
	BST() {}
	BST(vector<int> values) {
		for (int& val : values)
			insertNode(val);
	}

	void insertNode(int val) {
		if (!root)
			this -> root = new Node(val);
		else
			push(val, this -> root);
	}

	void deleteNode(int val) {
		this -> root = pop(val, this -> root);
	}

	bool search(int val) {
		return find(val, this -> root);
	}

	int min() {
		if (!root)
			return -1;
		return findMin(root) -> val;
	}

	int max() {
		if (!root)
			return -1;
		return findMax(root) -> val;
	}

	int successor(int val) {
		Node* s = getSuccessor(find(val, this -> root));
		if (s)
			return s -> val;
		else
			return -1;
	}

	int predecessor(int val) {
		Node* p = getPredecessor(find(val, this -> root));
		if (p)
			return p -> val;
		else
			return -1;
	}

	void print() {
		if (!root)
			return;

		cout << "Pre-Order\t:";
		preOrder(this -> root);
		cout << endl << "In-Order\t:";
		inOrder(this -> root);
		cout << endl << "Post-Order\t:";
		postOrder(this -> root);
		cout << endl << "Level-Order\t:";
		levelOrder();
		cout << endl;
	}

	~BST() {
		if (root)
			deleteBST(root);
	}
};

int main() {
	BST bst({15, 10, 20, 8, 12, 17, 25, 6, 11, 16, 27, 6, 7, 28, 15});
	cout << "Min\t\t: " << bst.min() << endl;
	cout << "Max\t\t: " << bst.max() << endl;
	bst.print();

	cout << "Predecessor(15)\t: " << bst.predecessor(15) << endl;
	cout << "Successor(15)\t: " << bst.successor(15) << endl;

	cout << endl;
	cout << "Search(6)\t: " << bst.search(6) << endl;
	cout << "Predecessor(6)\t: " << bst.predecessor(6) << endl;
	cout << "Successor(6)\t: " << bst.successor(6) << endl;
	bst.deleteNode(6);
	cout << "Delete(6)" << endl;
	cout << "Search(6)\t: " << bst.search(6) << endl;
	cout << "Predecessor(6)\t: " << bst.predecessor(6) << endl;
	cout << "Successor(6)\t: " << bst.successor(6) << endl;

	cout << endl;
	cout << "Search(10)\t: " << bst.search(10) << endl;
	bst.deleteNode(10);
	cout << "Delete(10)" << endl;
	cout << "Search(10)\t: " << bst.search(10) << endl;
	bst.print();

	cout << endl;
	bst.deleteNode(15);
	cout << "Delete(15)" << endl;
	bst.deleteNode(30);
	bst.print();

}
