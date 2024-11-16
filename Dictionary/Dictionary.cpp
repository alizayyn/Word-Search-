#include<iostream>
#include<list>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

template <class T>
class BST;
class specialized_BST;
class Occurance_of_Words;



template <class T>
class BST
{
	class Bnode
	{
		friend class BST;
		T data;
		Bnode* left;
		Bnode* right;
	public:
		Bnode()
		{
			left = NULL;
			right = NULL;
		}
		Bnode(const T d, Bnode* l, Bnode* r)
		{
			data = d;
			left = l;
			right = r;
		}
		Bnode(const Bnode& rhs)
		{
			data = rhs.data;
			left = rhs.left;
			right = rhs.right;
		}
		~Bnode() {};
	};

	Bnode* root;
public:
	BST()
	{
		root = nullptr;
	}
	BST(const BST& T)
	{
		copyAll(T.root, root);
	}
	void copyAll(Bnode* rhs, Bnode*& lhs)
	{
		if (rhs)
		{
			lhs = new Bnode(rhs->data, nullptr, nullptr);
			copyAll(rhs->left, lhs->left);
			copyAll(rhs->right, lhs->right);
		}
	}

	/*BST& operator=(BST& rhs)
	{
		destroyAll(root);
		copyAll(rhs.root, root);
		return *this;
	}*/


	void Insert(T d)
	{
		Insert(root, d);
	}

	void Insert(Bnode*& r, T d)
	{
		if (!r)
		{
			r = new Bnode(d, nullptr, nullptr);
		}
		else if (d < r->data)
		{
			Insert(r->left, d);
		}
		else if (d > r->data)
		{
			Insert(r->right, d);
		}

	}

	void Print()
	{
		if (root)
			printSorted(root);
	}

	void printSorted(Bnode* r)
	{
		if (r)
		{
			printSorted(r->left);
			cout << r->data << " ";
			printSorted(r->right);
		}
	}

	Bnode* FindMax(Bnode* r)
	{
		if (r->right == NULL)
		{
			return r;
		}
		else
			return FindMax(r->right);
	}

	bool Search(T d)
	{
		return Search(root, d);
	}

	bool Search(Bnode* r, const T d)
	{
		if (!r)
		{
			return false;
		}
		if (r->data == d)
		{
			return true;
		}
		else if (d < r->data)
		{
			return Search(r->left, d);
		}
		else if (d > r->data)
		{
			return Search(r->right, d);
		}
	}
	void Remove(T d)
	{
		Remove(root, d);
	}

	void Remove(Bnode*& r, T d)
	{
		if (r)
		{
			if (d == r->data)
			{
				Bnode* temp = nullptr;
				if (!r->left && !r->right)
				{
					delete r;
					r = NULL;
				}
				else if (r->left && !r->right)
				{
					temp = r->left;
					delete r;
					r = temp;
				}
				else if (!r->left && r->right)
				{
					temp = r->right;
					delete r;
					r = temp;
				}
				else if (r->left && r->right)
				{
					temp = findMax(r->left);
					T m = temp->data;
					r->data = m;
					Remove(r->left, m);
				}
			}
			else if (d < r->data)
			{
				Remove(r->left, d);
			}
			else
			{
				Remove(r->right, d);
			}
		}
	}

	//Function to read the stop words from file and Make it a BST

	void ReadStopWords(string FileName)
	{
		ifstream fin(FileName);
		string temp;
		if (fin.is_open())
		{
			while (!fin.eof())
			{
				getline(fin, temp, '\n');//to read till end of line
				if (temp[0] != '#')   //to skip any comments
				{
					Insert(temp);   //Making A BST of the Stop words
				}
			}
		}
		else
		{
			cout << "FILE IS NOT OPEN";
		}
	}



	~BST()
	{
		destroyAll(root);
	}
	void destroyAll(Bnode*& r)
	{
		if (r)
		{
			destroyAll(r->left);
			destroyAll(r->right);
			delete r;
		}
	}
};

class Occurance_of_Words
{
	int chapterNo;
	int PageNo;
	int LineNo;
public:
	Occurance_of_Words(int c = 0, int p = 0, int l = 1)
	{
		chapterNo = c;
		PageNo = p;
		LineNo = l;
	}

	bool operator==(Occurance_of_Words& rhs)
	{

		return LineNo == rhs.LineNo;
	}

	friend ostream& operator<<(ostream& out, Occurance_of_Words& rhs)
	{
		out << "Chapter Number: " << rhs.chapterNo;
		out << "\tPage Number: " << rhs.PageNo;
		out << "\tLine Number: " << rhs.LineNo;
		return out;
	}
	~Occurance_of_Words() {};
};



class specialized_BST
{

private:
	class SNode
	{
		friend class specialized_BST;
	public:
		SNode* s_left;
		SNode* s_right;
		string key;
		list<Occurance_of_Words>occurance;

		SNode()
		{
			s_left = NULL;
			s_right = NULL;
			key = "";
		}
		SNode(string k, SNode* l = NULL, SNode* R = NULL)
		{
			key = k;
			s_left = l;
			s_right = R;
		}
		SNode(string k, list<Occurance_of_Words> word, SNode* le, SNode* r)
		{
			key = k;
			occurance = word;
			s_left = le;
			s_right = r;
		}
		SNode(string k, Occurance_of_Words& word, SNode* le, SNode* r)
		{
			key = k;
			occurance.push_back(word);
			s_left = le;
			s_right = r;
		}
		SNode(const SNode& rhs)
		{
			key = rhs.key;
			s_left = rhs.s_left;
			s_right = rhs.s_right;
			occurance = rhs.occurance;
		}

		~SNode() {};

	};


	SNode* s_root; //root of the specialized bst

public:
	specialized_BST()
	{
		s_root = NULL;
	}
	specialized_BST(specialized_BST& rhs)
	{
		copyAll(s_root, rhs.s_root);
	}
	void copyAll(SNode* r, SNode*& l)
	{
		if (r)
		{
			l = new SNode(r->key, r->occurance, NULL, NULL);
			copyAll(r->s_left, l->s_left);
			copyAll(r->s_right, l->s_right);
		}
	}
	//destructor
	~specialized_BST()
	{
		deleteALL(s_root);
	}
	void deleteALL(SNode*& r)
	{
		if (r)
		{
			deleteALL(r->s_left);
			deleteALL(r->s_right);
			delete r;
		}
	}

	//Wraper Insert
	void Insert(string key, Occurance_of_Words& word) {
		Insert(s_root, key, word);
	}
	void Insert(SNode*& r, string k, Occurance_of_Words& w)
	{
		if (!r)
		{
			r = new SNode(k, w, nullptr, nullptr); //if tree is empty insert at Root Node
		}
		else if (r->key == k)
		{

			list<Occurance_of_Words>::iterator itr;
			bool check = true;
			for (itr = r->occurance.begin(); itr != r->occurance.end(); itr++)
			{
				//check if the line is same then no insertion
				if (*itr == w)
				{
					check = false;
					break;
				}
			}
			if (check)
			{
				r->occurance.push_back(w);
			}
		}
		else if (k > r->key) //left insertion
		{
			Insert(r->s_right, k, w);
		}
		else if (k < r->key) //left insertion
		{
			Insert(r->s_left, k, w);
		}

	}

	//reads file data 
	template<typename P>
	void ReadInputFromFile(string FileName, BST<P>& stop_words)
	{

		string temp;
		ifstream fin(FileName);
		if (fin.is_open())
		{
			int chap = 0;
			int line = 1;
			int page = 0;
			while (!fin.eof())     // while not end of file
			{
				getline(fin, temp, '\n'); //to get full line until the next line
				if (temp[0] == '#' && temp[2] == 'C')// to take chapters input
				{
					int l = temp.length();
					l--;
					chap = temp[l] - 48;

					//these also convert char to int 
					//chap = temp[l] - '0'; 
					//chap = stoi(&temp[l]); 
					//chap = atoi(&temp[l]); 

				}
				else if (temp[0] == '#' && temp[2] == 'P') //to take pages input
				{
					int l = temp.length();
					l--;
					page = temp[l] - 48;

					//these also convert char to int 
					//page = temp[l] - '0';
					//page = stoi(&temp[l]);
					//page = atoi(&temp[l]);

				}

				else if (temp[0] != '#' && temp.length() > 0)
				{
					string words; //stores the words_tokens of the line

					int length = temp.length();
					int j = 0;

					for (int i = 0; i < length; i++)
					{
						if (temp[i] == ' ' || temp[i] == '’' || temp[i] == '.' || temp[i] == ',' || temp[i] == '!' || temp[i] == '?' || temp[i] == ':' || temp[i] == ';')
						{

							words = temp.substr(j, i - j);  // inbuilt function to pick the substring fron the j-th index to the i-j no of characters
							j = i + 1;
							lower_case(words);//as stop words are in lower case
							bool check = stop_words.Search(words);
							if (check == true)
							{
								words.erase();
							}
							if (check == false)
							{
								Occurance_of_Words occoured(chap, page, line);
								Insert(words, occoured); //searched word is inserted in the specialized BST
							}
						}
					}
					line++;
				}

			}
		}
		else
		{
			cout << "\nFILE IS NOT OPEN\n";

		}
	}

	//convert the string in to lower case character
	void lower_case(string& s)
	{
		int l = s.length();
		for (int i = 0; i < l; i++)
		{
			s[i] = tolower(s[i]);
		}
	}

	void display()
	{
		print(s_root);
	}
	void print(SNode* r)
	{
		if (r)
		{
			print(r->s_left);
			cout << "Key:" << r->key << endl;
			list<Occurance_of_Words>::iterator itr;
			cout << "Occurences: \n";
			for (itr = r->occurance.begin(); itr != r->occurance.end(); itr++)
			{

				cout << *itr;
				cout << endl;
			}
			cout << endl;
			print(r->s_right);
		}
	}

	void Print()
	{
		if (s_root)
			printSorted(s_root);
	}

	void printSorted(SNode* r)
	{
		if (r)
		{
			printSorted(r->s_left);
			cout << r->key << " ";
			printSorted(r->s_right);
		}
	}


	SNode* FindMax(SNode* r)
	{
		if (r->s_right == NULL)
		{
			return r;
		}
		else
			return FindMax(r->s_right);
	}
	//wrapper function to call in main
	void Remove(string key)
	{
		bool flag;
		flag = Remove(s_root, key);
		if (flag == false)
		{
			cout << "\nWord is not found :( \n\n";
		}
	}
	bool check = false;
	bool Remove(SNode*& r, string k)
	{
		if (r != NULL)
		{

			if (k == r->key)
			{
				SNode* temp = 0;
				if (r->s_left == NULL && r->s_right == NULL)  // if leaf node
				{
					cout << "deleted :)\n";
					delete r;
					r = NULL;
					check = true;
					return true;
				}
				else if (r->s_left && r->s_right == NULL) // no right child
				{
					cout << " deleted :)\n";

					temp = r->s_left;
					delete r;
					r = temp;
					check = true;
					return true;

				}
				else if (r->s_left == NULL && r->s_right)//if no left child  
				{
					cout << " deleted :)\n";

					temp = r->s_right;
					delete r;
					r = temp;
					check = true;
					return true;

				}
				else if (r->s_left && r->s_right) // having both child nodes
				{
					temp = FindMax(r->s_left);
					string s = temp->key;
					r->key = s;
					Remove(r->s_left, s);
				}
			}
			else if (k < r->key)
			{
				Remove(r->s_left, k);
			}
			else if (k > r->key)
			{
				Remove(r->s_right, k);
			}
		}
		if (check == false)
		{
			return false;
		}
	}



	void Insert(string d)
	{
		Insert(s_root, d);
	}

	void Insert(SNode*& r, string d)
	{
		if (!r)
		{
			r = new SNode(d, nullptr, nullptr);
		}
		else if (d < r->key)
		{
			Insert(r->s_left, d);
		}
		else if (d > r->key)
		{
			Insert(r->s_right, d);
		}

	}
	void Insert(SNode& d)
	{
		Insert(s_root, d);
	}

	void Insert(SNode*& r, SNode& d)
	{
		if (!r)
		{
			*r = d;
		}
		else if (d.key < r->key)
		{
			Insert(r->s_left, d);
		}
		else if (d.key > r->key)
		{
			Insert(r->s_right, d);
		}

	}

	void merge(SNode*& cur, vector<SNode> nodes)
	{
		if (nodes.size() == 0)
			cur = nullptr;
		else
		{
			int mid = nodes.size() / 2;

			cur = new SNode();
			cur->key = nodes[mid].key;
			cur->occurance = nodes[mid].occurance;

			vector<SNode> lefSNodes;
			for (int i = 0; i < mid; i++)
			{
				lefSNodes.push_back(nodes[i]);
			}

			vector<SNode> righSNodes;
			for (int i = mid + 1; i < nodes.size(); i++)
			{
				righSNodes.push_back(nodes[i]);
			}

			merge(cur->s_left, lefSNodes);
			merge(cur->s_right, righSNodes);
		}
	}

	//In order traversal left root right
	void Merge(specialized_BST& st1, specialized_BST& st2)
	{
		vector<SNode>l1;
		vector<SNode>l2;
		storeValuesInlist(st1.s_root, l1);
		storeValuesInlist(st2.s_root, l2);

		vector<SNode>l3;

		auto i = l1.begin();
		auto j = l2.begin();
		while (i != l1.end() && j != l2.end())
		{
			if (i->key == j->key)
			{
				for (auto it = j->occurance.begin(); it != j->occurance.end(); ++it)
				{
					i->occurance.push_back(*it);
				}

				l3.push_back(*i);
				++i;
				++j;
			}
			else if (i->key < j->key)
			{
				l3.push_back(*i);
				++i;
			}
			else
			{
				l3.push_back(*j);
				++j;
			}
		}

		// add the remaining nodes from the allNodes array
		while (i != l1.end())
		{
			l3.push_back(*i);
			i++;
		}

		// add the remaining nodes from the otherNodes array
		while (j != l2.end())
		{
			l3.push_back(*j);
			j++;
		}

		deleteALL(s_root);

		merge(s_root, l3);
	}





	//stores the values of tree in list
	void storeValuesInlist(SNode* r, vector<SNode>& l)
	{
		if (r != NULL)
		{
			storeValuesInlist(r->s_left, l);
			l.push_back(*r);
			storeValuesInlist(r->s_right, l);
		}
	}
	void storeValuesInlist(SNode* r, list<string>& l)
	{
		if (r != NULL)
		{
			storeValuesInlist(r->s_left, l);
			l.push_back(r->key);
			storeValuesInlist(r->s_right, l);
		}
	}

	void find_common_words(specialized_BST& st2)
	{
		list<string>l1;
		list<string>l2;
		//common
		list<string>l3;

		storeValuesInlist(s_root, l1);
		storeValuesInlist(st2.s_root, l2);
		list<string>::iterator itr1;
		list<string>::iterator itr2;
		bool check = false;
		for (itr1 = l1.begin(); itr1 != l1.end(); itr1++)
		{
			for (itr2 = l2.begin(); itr2 != l2.end(); itr2++)
			{
				if (*itr1 == *itr2)
				{
					l3.push_back(*itr1);
					//check = true;
					//break;
				}
				//if (check == true)
				//break;
			}
		}
		itr1 = l3.begin();
		cout << "Common words: ";
		for (itr1; itr1 != l3.end(); itr1++)
		{
			cout << *itr1 << endl;
		}
		cout << endl;

	}



	bool Search(string k)
	{
		SNode* temp = Search(s_root, k);
		if (temp != 0)
		{
			cout << "Key:" << temp->key << endl;
			list<Occurance_of_Words>::iterator itr;  //to get the information oor the occurances of the key
			cout << "Occurences : \n";
			for (itr = temp->occurance.begin(); itr != temp->occurance.end(); itr++)
			{
				cout << *itr;
				cout << endl;
			}
			cout << endl;
			return true;
		}
		else
		{
			cout << "The key does not exist.\n";
			return false;
		}
	}
	SNode* Search(SNode* r, string k)
	{
		if (r == NULL)
		{
			return 0;
		}
		if (r->key == k)
		{
			return r;
		}
		else if (r->key < k)
		{
			return Search(r->s_right, k);
		}
		else
		{
			return Search(r->s_left, k);
		}
	}
};




int main()
{
	//q1: inputing stop words in a bst 
	BST<string> stopWords;
	stopWords.ReadStopWords("stop.txt");

	//q2: creat a speacialized bst class
	specialized_BST input;

	//q3: populate specialized bst
	input.ReadInputFromFile("Input.txt", stopWords);

	//q4:
	//displaying all occurances of bst
	input.display();
	cout << "\n\n\n";

	//q5: searching in a specialized bst
	string search_word;
	cout << "Enter the word you want to search: ";
	cin >> search_word;
	input.Search(search_word);

	//q6: deleting a word and its occurances form bst
	string delete_word;
	cout << "Enter the word you want to delete: ";
	cin >> delete_word;
	input.Remove(delete_word);


	//q7: Merging two specialized BSTs

	specialized_BST b1;
	specialized_BST b2;
	specialized_BST b3;

	//this file is empty
	BST<string> dummystop_Words;
	dummystop_Words.ReadStopWords("data.txt");
	b1.ReadInputFromFile("Input.txt", dummystop_Words);
	b2.ReadInputFromFile("Input.txt", dummystop_Words);
	b3.Merge(b1, b2); //not merging the occurances 
	b3.display();

	//q8: Finding common words in two specialized BSTs

	b1.find_common_words(b2);


	system("pause");
	return 0;
}