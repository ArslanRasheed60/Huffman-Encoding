#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

class Node
{
public:
	string name;
	int freq;
	Node* left;
	Node* right;
	Node* next;
	int l;
	int r;
	Node()
	{
		name = "";
		freq = 0;
		left = nullptr;
		right = nullptr;
		next = nullptr;
		l = 0;
		r = 0;
	}
	Node(string nam, int freq)
	{
		this->name = nam;
		this->freq = freq;
		left = nullptr;
		right = nullptr;
		next = nullptr;
		l = 0;
		r = 0;
	}
};
class Queue
{
	Node* head;
	Node* tail;
public:
	Queue()
	{
		head = nullptr;
		tail = nullptr;
	}
	bool isFull()
	{
		return false;
	}
	bool isEmpty()
	{
		if (head == nullptr)
			return true;
		else
			return false;
	}
	void insertAtTail(Node* curr)
	{
		Node* n;
		if (curr == nullptr)
		{
			n = new Node("dummy", -1);
		}
		else
		{
			n = curr;
		}

		if (tail == nullptr)
		{
			head = n;
			tail = n;

		}
		else
		{
			tail->next = n;
			tail = n;
		}
	}
	Node* removeFromHead()
	{
		if (head != nullptr)
		{
			Node* curr = head;
			if (head == tail)
			{
				head = nullptr;
				tail = nullptr;
			}
			else
			{
				head = head->next;
			}
			return curr;
		}
	}
public:
	void Enque(Node* n)
	{
		if (!isFull())
		{
			insertAtTail(n);
		}
	}
	Node* Deque()
	{
		if (!isEmpty())
		{
			return removeFromHead();
		}
	}

};

class MinHeap
{
	Node** heaparr;
	Node* root;
	int size;
	int index;
public:
	bool static treeflag;
	MinHeap()
	{
		heaparr = nullptr;
		size = 0;
		index = 0;
		root = nullptr;
	}
	MinHeap(int s)
	{
		size = s;
		index = 1;
		heaparr = new Node * [size];
		for (int i = 0; i < size; i++)
		{
			heaparr[i] = nullptr;
		}
		root = nullptr;
	}
	void insert(string nam, int freq)
	{
		Node* n = new Node(nam, freq);

		if (index == size)
		{
			return;
		}

		heaparr[index] = n;

		int temp_totalitem = index;
		index++;

		//maintaing the min heap
			//bubble up
		while (temp_totalitem / 2 != 0)
		{
			if (heaparr[temp_totalitem]->freq < heaparr[temp_totalitem / 2]->freq)
			{
				Node* swap = heaparr[temp_totalitem];
				heaparr[temp_totalitem] = heaparr[temp_totalitem / 2];
				heaparr[temp_totalitem / 2] = swap;
			}
			temp_totalitem = temp_totalitem / 2;
		}
	}
	void insert(Node* n)
	{
		if (index == size)
		{
			return;
		}

		heaparr[index] = n;

		int temp_totalitem = index;
		index++;

		//maintaing the min heap
			//bubble up

		while (temp_totalitem / 2 != 0)
		{
			//if parent is greater than child than swap
			if (heaparr[temp_totalitem]->freq < heaparr[temp_totalitem / 2]->freq)
			{
				Node* swap = heaparr[temp_totalitem];
				heaparr[temp_totalitem] = heaparr[temp_totalitem / 2];
				heaparr[temp_totalitem / 2] = swap;
			}
			temp_totalitem = temp_totalitem / 2;
		}
	}
	Node* getmin()
	{
		/*cout << endl;
		for (int i = 1; i < index; i++)
		{
			cout << heaparr[i]->name << heaparr[i]->freq << " ";
		}
		cout << endl;*/
		Node* min = nullptr;

		int temp = index;
		int t = index - 1;

		//swapping data between root and last leaf node
		/*if (t > 0)
		{
			if (heaparr[1]->freq < heaparr[t]->freq)
			{
				Node* temp = heaparr[1];
				heaparr[1] = heaparr[t];
				heaparr[t] = temp;
			}
			index--;
			min = heaparr[t];
			heaparr[t] = nullptr;
		}*/
		if (t > 0)
		{
			min = heaparr[1];
			heaparr[1] = heaparr[t];
			index--;
			heaparr[t] = nullptr;
		}
		int i = 1;
		//bubble down
		while (i < t && i * 2 < t && i * 2 + 1 < t)
		{
			if (heaparr[i * 2] == nullptr || heaparr[i * 2 + 1] == nullptr)
			{
				break;
			}
			if (heaparr[i] != nullptr && heaparr[i]->freq >= heaparr[i * 2]->freq && heaparr[i]->freq >= heaparr[i * 2 + 1]->freq && heaparr[i * 2]->freq >= heaparr[i * 2 + 1]->freq)
			{
				Node* temp = heaparr[i];
				heaparr[i] = heaparr[i * 2 + 1];
				heaparr[i * 2 + 1] = temp;

				i = i * 2 + 1;
			}
			else if (heaparr[i] != nullptr && heaparr[i]->freq >= heaparr[i * 2]->freq && heaparr[i]->freq >= heaparr[i * 2 + 1]->freq && heaparr[i * 2]->freq < heaparr[i * 2 + 1]->freq)
			{
				Node* temp = heaparr[i];
				heaparr[i] = heaparr[i * 2];
				heaparr[i * 2] = temp;

				i = i * 2;
			}
			else
				break;
		}

		if (i * 2 < t)
		{
			if (heaparr[i] != nullptr && heaparr[i * 2] != nullptr && heaparr[i]->freq > heaparr[i * 2]->freq)
			{
				Node* temp = heaparr[i];
				heaparr[i] = heaparr[i * 2];
				heaparr[i * 2] = temp;
			}
		}
		return min;
	}
	bool check_node_one()
	{
		if (index == 2)
			return true;
		else
			return false;
	}
	void menu()
	{
		while (!check_node_one())
		{
			Node* leftC = getmin();
			Node* rightC = getmin();

			Node* parent = new Node(leftC->name + rightC->name, leftC->freq + rightC->freq);
			parent->left = leftC;
			parent->right = rightC;

			insert(parent);
		}

		root = getmin();
	}
	//assigning 0's to the left side and 1's to the right 
	void assigning_0_1(Node* curr)
	{
		if (curr->left == nullptr)
			return;
		else
		{
			curr->l = 0;
			assigning_0_1(curr->left);
		}

		if (curr->right == nullptr)
			return;
		else
		{
			curr->r = 1;
			assigning_0_1(curr->right);
		}
	}
	void assigning_0_1()
	{
		Node* curr = root;
		assigning_0_1(curr);
	}
	void LVR(Node* curr, char ch, string& binary)
	{
		if (curr->left == nullptr && curr->right == nullptr)
		{
			//cout << curr->name;
			return;
		}
		bool flagleft = false;
		bool flagright = false;

		if (curr->left != nullptr)
		{
			for (int i = 0; i < curr->left->name.length(); i++)
			{
				if (ch == curr->left->name[i])
				{
					string ch;
					ch.push_back(curr->l + 48);
					binary = binary + ch;
					//cout << curr->l;
					flagleft = true;
				}
			}
		}

		if (flagleft)
		{
			LVR(curr->left, ch, binary);
		}

		if (curr->right != nullptr)
		{
			for (int i = 0; i < curr->right->name.length(); i++)
			{
				if (ch == curr->right->name[i])
				{
					string ch;
					ch.push_back(curr->r + 48);
					binary = binary + ch;
					//cout << curr->r;
					flagright = true;
				}
			}
		}

		if (flagright)
			LVR(curr->right, ch, binary);
	}
	void LVR(char ch, string& binary)
	{
		Node* curr = root;
		LVR(curr, ch, binary);
	}

	int measureheight()
	{
		Node* curr = root;
		int height = 0;
		Queue q1;

		if (curr != nullptr)
		{
			q1.Enque(curr);
			height = 1;
			q1.Enque(nullptr);		//storing -1 after 1 level;
		}

		while (!q1.isEmpty())
		{
			curr = q1.Deque();
			if (curr->left != nullptr)
			{
				q1.Enque(curr->left);
			}
			if (curr->right != nullptr)
			{
				q1.Enque(curr->right);
			}
			if (curr->freq == -1)
			{
				height++;
				if (!q1.isEmpty())
				{
					q1.Enque(curr);
				}
			}
		}
		height--;
		//cout << endl << height;
		return height;
	}
	int makeCompleteFullTree()
	{
		Node* curr = root;
		int height = measureheight();
		int temp = height;

		Queue q1;

		if (curr != nullptr)
		{
			q1.Enque(curr);
			q1.Enque(nullptr);		//storing -1 after 1 level;
		}

		while (!q1.isEmpty() && height > 0)
		{
			curr = q1.Deque();
			//left condition storage
			if (curr->left != nullptr)
			{
				q1.Enque(curr->left);
			}
			else
			{
				Node* n = new Node("useless", -2);
				curr->left = n;
				q1.Enque(curr->left);
			}
			//right condition storage
			if (curr->right != nullptr)
			{
				q1.Enque(curr->right);
			}
			else
			{
				Node* n = new Node("useless", -2);
				curr->right = n;
				q1.Enque(curr->right);
			}

			//checking null after each level
			if (curr->freq == -1)
			{
				height--;
				if (!q1.isEmpty())
				{
					q1.Enque(curr);
				}
			}
		}

		return temp;
	}

	void convertSpacetoTeldaCharac(string& dat)
	{
		int len = dat.length();
		for (int i = 0; i < len; i++)
		{
			if (dat[i] == ' ')
			{
				dat[i] = '~';
			}
			else if (dat[i] == '\n')
			{
				dat[i] = '`';
			}
		}
	}
	void convertTeldaCharacToSpace(string& dat)
	{
		int len = dat.length();
		for (int i = 0; i < len; i++)
		{
			if (dat[i] == '~')
			{
				dat[i] = ' ';
			}
			else if (dat[i] == '`')
			{
				dat[i] = '\n';
			}
		}
	}

	void storeTreeInFile(int zerocount,int* arr)
	{
		int height = makeCompleteFullTree();
		//cout << endl << height;
		int count = 0;

		ofstream fout;
		fout.open("tree.txt");

		for (int i = 0; i < 500; i++)
		{
			if (arr[i] == 0)
			{
				fout << arr[i] << " ";
				break;
			}
			else
				fout << arr[i] << " ";
		}

		fout << endl;

		fout << height << endl;
		fout << zerocount << endl;

		Queue q1;

		Node* curr = root;

		if (curr != nullptr)
		{
			count++;
			q1.Enque(curr);
			q1.Enque(nullptr);
		}

		while (!q1.isEmpty() && height > 0)
		{
			curr = q1.Deque();

			if (curr->left != nullptr)
			{
				q1.Enque(curr->left);
			}

			if (curr->right != nullptr)
			{
				q1.Enque(curr->right);
			}

			if (curr->freq != -1)
			{
				string nam = curr->name;
				convertSpacetoTeldaCharac(nam);
				fout << nam;
				fout << " ";
				fout << curr->freq;
				fout << "\t";
				count++;
			}
			else
			{
				fout << endl;
				height--;
				if (!q1.isEmpty())
				{
					q1.Enque(curr);
				}
			}
		}
		fout.close();
		//cout << endl << count;
	}
	string writeBinaryToOriginalDataIterative(Node* curr, string& update, string bindata, int& i)
	{
		while (i < bindata.length())
		{
			if (curr != nullptr)
			{
				if (curr->left == nullptr && curr->right == nullptr)
				{
					update.push_back(curr->name[0]);
					curr = root;
				}
				else if (curr->l == bindata[i] - 48)
				{
					
					i++;
					curr = curr->left;
				}

				else if (curr->r == bindata[i] - 48)
				{
					
					i++;
					curr = curr->right;
				}

			}
		}
		return update;
	}
	/*string writeBinaryToOriginalData(Node* curr, string& update, string bindata, int& i)
	{
		if (curr->left == nullptr && curr->right == nullptr)
		{
			update.push_back(curr->name[0]);
			curr = root;
			if (i == bindata.length())
				return update;
		}

		if (curr->l == bindata[i] - 48)
		{
			i++;
			return writeBinaryToOriginalData(curr->left, update, bindata, i);
		}
		if (curr->r == bindata[i] - 48)
		{
			i++;
			return writeBinaryToOriginalData(curr->right, update, bindata, i);
		}
	}*/
	string writeBinaryToOriginalData(string bindata)
	{
		Node* curr = root;
		string latestnewdata = "";
		int i = 0;
		return writeBinaryToOriginalDataIterative(curr, latestnewdata, bindata, i);
	}

	void makeoriginaltree(int height)
	{
		Node* curr = root;
		//Node* prev = root;
		//int h = height;

		//h = pow(2, h-1);
		//h--;

		Queue q1;

		if (curr != nullptr)
		{
			q1.Enque(curr);
			
			//q1.Enque(nullptr);		//storing -1 after 1 level;
		}

		while (!q1.isEmpty())//&& height > 0)
		{
			curr = q1.Deque();
			//left condition removal
			if (curr != nullptr)
			{
				if (curr->left != nullptr)
				{
					if (curr->left->freq != -2)
					{
						q1.Enque(curr->left);
					}
					else
					{
						q1.Enque(curr->left);
						curr->left = nullptr;
					}
				}

				//right condition removal
				if (curr->right != nullptr)
				{
					if (curr->right->freq != -2)
					{
						q1.Enque(curr->right);
					}
					else
					{
						q1.Enque(curr->right);
						curr->right = nullptr;
					}
				}
				
				if(curr->freq == -2)
					delete curr;
			}
		}

		assigning_0_1();
	}
	void getTreeFromfile(int& zerocount, int* & arr)
	{
		int temp_height = 0;

		ifstream fin;
		fin.open("tree.txt");
		if (!fin)
		{
			cout << endl << "Sorry! File of Tree does not exits. So decompression does not possible ";
			treeflag = true;
		}
		else
		{

			int var = 0,index = 0;
			fin >> var;

			while (var != 0)
			{
				arr[index] = var;
				index++;
				fin >> var;
			}

			int height;
			int jerocount;
			fin >> height;
			temp_height = height;
			fin >> jerocount;
			zerocount = jerocount;
			Node* curr = nullptr;

			string base1;
			fin >> base1;
			convertTeldaCharacToSpace(base1);
			int freq1;
			fin >> freq1;

			Node* n = new Node(base1, freq1);
			Node* temp = n;


			Queue q1;
			q1.Enque(n);
			q1.Enque(nullptr);

			while (height > 0)
			{
				curr = q1.Deque();

				if (curr->freq != -1)
				{

					//cout << curr->name << " ";
					//cout << curr->freq << "\t";

					//left side handle
					fin >> base1;
					convertTeldaCharacToSpace(base1);
					fin >> freq1;
					Node* n1 = new Node(base1, freq1);
					curr->left = n1;
					q1.Enque(curr->left);

					//right side handle
					fin >> base1;
					convertTeldaCharacToSpace(base1);
					fin >> freq1;
					Node* n2 = new Node(base1, freq1);
					curr->right = n2;
					q1.Enque(curr->right);

				}
				else
				{	
					height--;
					q1.Enque(curr);
				}
			}
			root = temp;
		}
		fin.close();

		if (temp_height != 0)
		{
			makeoriginaltree(temp_height);
		}
	}

	~MinHeap()
	{
		Queue q1;

		//deallcation of heap array
		if (heaparr != nullptr)
		{
			delete[]heaparr;
			heaparr = nullptr;
		}

		//deallalocation of root
		if (root != nullptr)
		{
			q1.Enque(root);
			q1.Enque(nullptr);		//storing -1 after 1 level;
		}

		while (!q1.isEmpty())
		{
			root = q1.Deque();
			if (root->left != nullptr)
			{
				q1.Enque(root->left);
			}
			if (root->right != nullptr)
			{
				q1.Enque(root->right);
			}
			if (root->freq == -1)
			{
				if (!q1.isEmpty())
				{
					q1.Enque(root);
				}
			}
			else
			{
				delete root;
				//cout << "\nDestructor called: ";
			}
		}

	}
};

bool MinHeap::treeflag = false;