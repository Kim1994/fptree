#include "stdafx.h"
//#include "ADOconn.h"

typedef struct fptree{
	int key;
	int value;
	struct fptree *son;
	struct fptree *right;
} fptree;

map <int, vector<int>> item;
int min_value = 1750;
map<int, int> firstitem;
vector<int> sort_key;

fptree *root;

void rebuilditem(){
	int max_key, max_value;
	vector<int> sort_value;
	map<int, int>::iterator it_sort;
	while (firstitem.begin() != firstitem.end()){
		max_key = 0, max_value = -1;
		for (it_sort = firstitem.begin(); it_sort != firstitem.end(); it_sort++){
			if (max_value < it_sort->second){
				max_key = it_sort->first;
				max_value = it_sort->second;
			}
		}
		sort_key.push_back(max_key);
		firstitem.erase(max_key);
	}

	vector<int>::iterator it;
	for (it = sort_key.begin(); it != sort_key.end(); it++)
		cout << *it << endl;
	
	vector<int> temp;
	for (int i = 0; i < item.size(); i++){
		vector<int>::iterator it_sort_find = sort_key.begin();
		for (; it_sort_find!=sort_key.end(); it_sort_find++){
			if (find(item[i].begin(), item[i].end(), *it_sort_find) != item[i].end()){
				temp.push_back(*it_sort_find);
			}
		}
		item[i] = temp;
		temp.clear();
		cout << i << endl;
	}
}

void creatfptree(){
	for (int i = 0; i < item.size(); i++){
		cout << i << endl;
		fptree *p = root;
		vector<int>::iterator it_creat;
		for (it_creat = item[i].begin(); it_creat != item[i].end(); it_creat++){
			fptree *p_son = p->son;
			if (p_son == NULL){
				p_son = new fptree;
				p_son->key = *it_creat;
				p_son->right = NULL;
				p_son->son = NULL;
				p_son->value = 1;
				p->son = p_son;
				p = p_son;
			}
			else{
				while (p_son->right != NULL&&p_son->key != *it_creat){
					p_son = p_son->right;
				}
				if (p_son->key == *it_creat){
					p_son->value++;
					p = p->son;
				}
				else if (p_son->right == NULL){
					p_son->right = new fptree;
					p_son->right->key = *it_creat;
					p_son->right->right = NULL;
					p_son->right->son = NULL;
					p_son->right->value = 1;
					p = p_son->right;
				}
			}
		}
	}
}
void first()
{
	map<int, vector<int>>::iterator it;
	for (it = item.begin(); it != item.end(); it++){
		vector<int>::iterator it_value;
		for (it_value = it->second.begin(); it_value != it->second.end(); it_value++)
		{
			firstitem[*it_value] ++;
		}
	}
	map<int, int>::iterator it_L;
	for (it_L = firstitem.begin(); it_L != firstitem.end();)
	{
		if (it_L->second <= min_value){
			firstitem.erase(it_L++);
		}
		else{
			it_L++;
		}
	}
	cout << "first finish" << endl;
}

	

void FileReader(string URL){
	ifstream in("D:\\retail.dat");
	int k = 0;
	if (!in.is_open())
	{
		cout << "not open";
		exit(0);
	}
	string preline;
	while (getline(in, preline))
	{
		istringstream iss(preline);
		int preitem;
		while (iss >> preitem)
		{
			item[k].push_back(preitem);
		}
		k++;
	}
	cout << "file read finish" << endl;
}

void show(){
	queue<fptree*> q;
	q.push(root);
	fptree *end=root;

	fptree *p;
	while (!q.empty())
	{
		p = q.front(); 
		q.pop();
		cout << p->key << ":" << p->value<<"  " ;
		if (end == p){
			cout << endl;
			if (end->son != NULL){
				end = end->son;
				while (end->right != NULL){
					end = end->right;
				}
			}
		}
		p = p->son;
		while (p!=NULL)
		{
			q.push(p);
			p = p->right;
		}
	}
}
void main(){
	root = new fptree;
	root->key = -1;
	root->right = NULL;
	root->son = NULL;
	root->value = -1;
	FileReader("D:\\retail.dat");
	first();
	rebuilditem();
	creatfptree();
	

	show();
	
	
}


