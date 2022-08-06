#include <bits/stdc++.h>
using namespace std;

#define INF 1000000007

struct Node {
	int data; // contains the key
	int degree; // number of children 
	Node* parent; // pointer to parent
	Node* leftmostChild; // pointer to the leftmost child
	Node* rightSibling; // pointer to the right sibling

	Node(int data, int degree) {
		this->data = data;
		this->degree = degree;
	}
};

typedef Node* NodePointer;

class BinomialHeap {
private:
	// head points to the root of the leftmost binomial tree
	NodePointer head;

public:
	BinomialHeap() {
		head = nullptr;
	}

	NodePointer getHead() {
		return this->head;
	}

	void setHead(NodePointer head) {
		this->head = head;
	}
	
	void MergeTrees(NodePointer, NodePointer); //DONE
	NodePointer FindMax(); //DONE
	NodePointer ExtractMax();
	void IncreaseKey(int, int); //Done
	void Unionize(BinomialHeap); //DONE
	void Insert(int); //DONE
	void PrintHeap(); //DONE
};

int main() {
    freopen("BinomialHeap.txt", "r", stdin);

    string INPUTSTRING;
    BinomialHeap heap;

    while (!cin.eof()) {
        cin >> INPUTSTRING;

        if (INPUTSTRING == "FIN") {
            NodePointer node = heap.FindMax();
			cout << "FindMax returned " << node->data << "\n";
        } else if (INPUTSTRING == "EXT") {
            NodePointer node = heap.ExtractMax();
			cout << "ExtractMax returned " << node->data << "\n";
        } else if (INPUTSTRING == "INS") {
			int data;
            cin >> data;
            heap.Insert(data);
        } else if (INPUTSTRING == "INC") {
            int prevKey, newKey;
			cin >> prevKey >> newKey;
			heap.IncreaseKey(prevKey, newKey);
			cout << "Increased " << prevKey;
			cout << ". The updated value is " << newKey; 
			cout << ".\n";
        } else if (INPUTSTRING == "PRI") {
            cout << "Printing Binomial Heap...\n";
            cout << "_________________________";
            heap.PrintHeap();
            cout << "_________________________\n";
        } else {
            break;
        }
    } 

    return 0;
}

//Class functions
NodePointer BinomialHeap::FindMax() {
	int max = -INF;
	NodePointer currPtr = head;
	NodePointer maxPtr = nullptr;

	while (currPtr != nullptr) {
		if (currPtr->data > max) {
			max = currPtr->data;
			maxPtr = currPtr;
		}
		currPtr = currPtr->rightSibling;
	}

	return maxPtr;
}

NodePointer BinomialHeap::ExtractMax() {
	NodePointer maxPtr = BinomialHeap::FindMax();
	NodePointer deleteNode, next, deleteMinusOne;
	// return maxPtr;
	next = head;
	while (true) {
		if (next->rightSibling->data == maxPtr->data) {
			next->rightSibling = next->rightSibling->rightSibling;
			deleteNode = next->rightSibling;
			deleteMinusOne = next;
			break;
		}
		next = next->rightSibling;
	}
	deleteMinusOne->rightSibling = deleteNode->rightSibling;

	next = deleteNode->leftmostChild;
	vector<NodePointer> nodesWithoutRoot;
	while (next != nullptr) {
		nodesWithoutRoot.push_back(next);
		next = next->rightSibling;
	}

	for (int i=nodesWithoutRoot.size()-1; i>-1; i--) {
		cout << "forloop1\n";
		BinomialHeap heap;
		heap.setHead(nodesWithoutRoot[i]);
		this->Unionize(heap);
		cout << "forloop2\n";
	}
	
	return maxPtr;
}

void BinomialHeap::IncreaseKey(int prevKey, int newKey) {
	NodePointer current = head, key, next;
	bool isFound = false;

	queue<NodePointer> q;
	q.push(current);

	while (!q.empty()) {
		NodePointer p = q.front();
		q.pop();
		int currentData = p->data;
		if (currentData == prevKey) {
			key = p;
			break;
		} else if (currentData < prevKey) {
			current = current->rightSibling;
			q.push(current);
		} else {
			NodePointer temp = p->leftmostChild;

			while (temp != nullptr) {
				q.push(temp);
				temp = temp->rightSibling;
			}
		}
	}

	//
	key->data = newKey;
	
	if (key->leftmostChild==nullptr || newKey > key->leftmostChild->data) { 
		//possible heapify up
		next = key->parent;
	
		while (next!=nullptr && next->data < key->data) {
			int t = next->data;
			key->data = next->data;
			next->data = t;
			key = next;
			key->data = newKey;
			next = next->parent;
		}
	} else {
		//possible heapify down
		next = key->leftmostChild;

		while (next!=nullptr && next->data > key->data) {
			int t = next->data;
			key->data = next->data;
			next->data = t;
			key = next;
			key->data = newKey;
			next = next->leftmostChild;
		}
	}
}

void BinomialHeap::MergeTrees(NodePointer newParent, NodePointer newChild) {
	newChild->parent = newParent;
	newChild->rightSibling = newParent->leftmostChild;
	newParent->leftmostChild = newChild;
	newParent->degree += 1;
}

void BinomialHeap::Unionize(BinomialHeap binomialheap) {
    if (head == nullptr) {
        head = binomialheap.getHead();
        return;
    }

	NodePointer amarHeap = head;
	NodePointer onnoHeap = binomialheap.getHead();
	NodePointer themPointer = nullptr;
    NodePointer headPointer = nullptr;

	if (amarHeap->degree <  onnoHeap->degree) {
		headPointer = amarHeap;
		amarHeap = amarHeap->rightSibling;
	} else if (amarHeap->degree > onnoHeap->degree) {
		headPointer = onnoHeap;
		onnoHeap = onnoHeap->rightSibling;
	} else {
        if (amarHeap->data > onnoHeap->data) {
			BinomialHeap::MergeTrees(amarHeap, onnoHeap);
			this->setHead(amarHeap);
        } else {
			BinomialHeap::MergeTrees(onnoHeap, amarHeap);
			this->setHead(onnoHeap);
        }
		return;
	}

	themPointer = headPointer;

	while (amarHeap!=nullptr && onnoHeap!=nullptr) {		
		if (amarHeap->degree <  onnoHeap->degree) {
			themPointer->rightSibling = amarHeap;
			amarHeap = amarHeap->rightSibling;
			themPointer = themPointer->rightSibling;
		} else if (amarHeap->degree > onnoHeap->degree) {
			themPointer->rightSibling = onnoHeap;
			onnoHeap = onnoHeap->rightSibling;
			themPointer = themPointer->rightSibling;
		} else {

		}
	}

	NodePointer temp = headPointer, next;

	if (amarHeap!=nullptr) {
		themPointer->rightSibling = amarHeap;
		amarHeap = amarHeap->rightSibling;
		themPointer = themPointer->rightSibling;
	}

	if (onnoHeap!=nullptr) {
		themPointer->rightSibling = onnoHeap;
		onnoHeap = onnoHeap->rightSibling;
		themPointer = themPointer->rightSibling;
	}

	while (temp != nullptr) {
		next = temp->rightSibling;
		if (next != nullptr && temp->degree==next->degree) {
			temp->rightSibling = next->rightSibling;
			if (next->data > temp->data) {
				BinomialHeap::MergeTrees(next, temp);
			} else {
				BinomialHeap::MergeTrees(temp, next);
			}
		} else {
			temp = next;
		}
	}

	setHead(headPointer);
}
	
void BinomialHeap::Insert(int data) {
	BinomialHeap heap;
	NodePointer node = new Node(data, 0);
	node->parent = nullptr;
	node->leftmostChild = nullptr;
	node->rightSibling = nullptr;
	heap.setHead(node);
	this->Unionize(heap); 
    cout << "Inserted " << data << "\n";
}

void BinomialHeap::PrintHeap() {
	NodePointer current = head;

	while (current != nullptr) {
		cout << "\nBinomial Tree, B" << current->degree << "";
		int levelCount=0, prevLevel=0;

		queue< pair<NodePointer, int> > q;
		q.push({current, levelCount});

		while (!q.empty()) {
			NodePointer p = q.front().first;
			int newLevel = q.front().second;
			if (newLevel==0) {
				cout << "\nLevel " << newLevel << " : " << p->data;
			} else if (prevLevel == newLevel) {
				cout << " " << p->data;
			} else {
				cout << "\nLevel " << newLevel << " : " << p->data;
				prevLevel = newLevel;
			}
			q.pop();


			if (p->leftmostChild != nullptr) {
				NodePointer tempPtr = p->leftmostChild;
				levelCount++;
				while (tempPtr != nullptr) {
					q.push({tempPtr, levelCount});
					tempPtr = tempPtr->rightSibling;
				}
			} 
		}

		current = current->rightSibling;
	}
	cout << "\n";
}

