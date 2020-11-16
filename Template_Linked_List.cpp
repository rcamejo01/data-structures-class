#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "support.h"

using namespace std;

template <class A>
struct node {
	A data;
	node<A> *next;

	node() {
		next = NULL;
	}
};

template <class B>
class linkedlist {
private:
	node<B> *head, *tail;
	int count;

public:
	linkedlist();
	~linkedlist();

	void setHead(node<B> *value) { head = value; }
	B *getHead() { return head; }

	bool isEmpty() { return (head==NULL) ? true : false; };

	bool contains(B&);
	int addAtHead(B&);
	int addAtTail(B&);

	int insert(B &data, int(*compare)(const B&, const B&));
	void insertionSort(int(*compare)(const B&, const B&));

	void clear();
	template <class C>
	friend ostream& operator<<(ostream&, const linkedlist<C>&);
};

template <class B>
linkedlist<B>::linkedlist() {
	head = NULL;
	tail = NULL;
	count = 0;
}

template <class B>
linkedlist<B>::~linkedlist() {
	clear();
}

template <class B>
bool linkedlist<B>::contains(B& val) {
	node<B> *current = head;
	while(current != NULL) 
	{
		if(current->data == val)
			return true; //value has been found-- no need for repitition, so no insertion
		current = current->next;
	}
	return false; //the whole list has been compared with value-- found no repitition
}

template <class B>
int linkedlist<B>::addAtHead(B &data) {
		node<B> *n;
		n = new node<B>();
		bool a = contains(data);
		if (a==true) return count;
		else if(a==false) 
		{
		n->data = data;
		if (isEmpty()) {
		head = n;
		tail = n;
		} 
		else { 
		n->next = head;
		head = n;
		}
	count++;
	return count;
		}
}

template <class B>
int linkedlist<B>::addAtTail(B &data) {
	node<B> *n;
	n = new node<B>();
	bool a = contains(data);
	if(a==true) return count;
	else if(a==false)
	{
	n->data = data;
	if (isEmpty()) {
		head = n;
		tail = n;
	} else { 
		tail->next = n;
		tail = n;
	}
	count++;
	return count;
	}
}

template <class B>
ostream& operator<<(ostream &out, const linkedlist<B> &t) {
	node<B> *temp = t.head;
	while(temp!=NULL) {
		out << temp->data << endl;
		temp = temp->next;
	}
	return out;
}

// compare function with template
template <class B>
int compare(const B &a, const B &b) {
	int ret = 0;
	if (a<b) ret = -1;
	else if (a>b) ret = 1;
	return ret;
}

template <class B>
int linkedlist<B>::insert(B &data, int(*compare)(const B&, const B&)) {
	if (isEmpty()) return addAtHead(data);
	else {
		if (compare(data,head->data)<=0) return addAtHead(data);
		else if (compare(data,tail->data)>=0) return addAtTail(data);
		else {
			bool a = contains(data);
			if(a==true) return count;
			else {
			node<B> *n = new node<B>;
			n->data=data;
			node<B> *temp1, *temp2;
			temp1=head;
			temp2=NULL;
			while(compare(data,temp1->data)>0) {
				temp2=temp1;
				temp1=temp1->next;
			}
			n->next=temp1;
			temp2->next=n;
			count++;
			return count;
			}
		}
	}
}

//insertion sort routine for linked list
//takes in compare function as a parameter
template<class B>
void linkedlist<B>::insertionSort(int(*compare)(const B&,const B&)) {
	linkedlist<B> *templist = new linkedlist<B>;
	node<B> *current = head;
	while(current != NULL) 
	{
		templist->insert(current->data,compare); 
		current=current->next;
	}
	head=templist->head;
}

template <class B>
void linkedlist<B>::clear() {
	node<B> *temp = head;
	while(head!=NULL) {
		head = head->next;
		temp->next = NULL;
		delete temp;
		temp = head;
	}
	head = NULL;
	tail = NULL;
	count = 0;
}

//Load either of the text files provided into an array of C++ strings
void countWords(string arr[], string filename)
{
	fstream file;
	file.open(filename);
	string word;
	int count = 0;
	while(!file.eof() && file >> word)
	{
		for(int i=0, l = word.size();i<l;i++)
			{
				if(ispunct(word[i])) //used to find punctuation
				{
					word.erase(i--,1); //must decrement the size of the string after deleted
					l=word.size(); //assigns new size
				}
				for(int j=0; j<word.size();j++) 
					word[j]=tolower(word[j]);//makes all words lowercase
			}
		arr[count]=word;
		count++;
	}
	cout << "There are " << count << " words in the array" << endl;
	file.close();
}

//adding the words from array into a list and sorting
void wordList(string filename)
{
	fstream file;
	file.open(filename);
	int count = 0;
	string words[80000];
	countWords(words,filename);
	while(file>>words[count]) { count++; }
	linkedlist<string> word;
	double start = getCPUTime();
	for(int i=0; i<count;i++)
	{
		word.addAtHead(words[i]);
	}

	word.insertionSort(compare);
	double end = getCPUTime();
	cout << word;
	cout << "The time it takes to add each string to list and sort: " << end-start << " seconds" << endl;
}

//create new list and sort 
void newList(string filename)
{
	fstream file;
	file.open(filename);
	int count=0;
	string words[80000];
	while(file>>words[count]) { count++; }
	linkedlist<string> word;
	double start = getCPUTime();
	for(int i=0;i<count;i++)
		word.insert(words[i],compare);
	double end = getCPUTime();
	cout << word;
	cout << "The time it takes to create new list and insert the words into it: " << end-start << " seconds" << endl;
}

void main(){
	/*
	//use the idata.txt file to create and print a list of integers (at least 1000)
	fstream file1;
	file1.open("idata.txt");

	int value;
	linkedlist<int> list1;

	if(file1.is_open())
	{
		int count=0;
		while(file1>>value && count<=1000)
		{
			list1.addAtHead(value); 
			//list1.addAtTail(value); 
			//list1.insert(value,compare);
		
			count++;
		}
	}       
	double start = getCPUTime();
	list1.insertionSort(compare);
	double end = getCPUTime();
	double time1 = end-start;
	cout << time1;
	cout<< list1;

	//use the simple text file, tdata.txt, provided to create and print a list of strings
	fstream file2;
	file2.open("tdata.txt");
	string word;
	linkedlist<string> list2;
	if(file2.is_open())
	{
		int count = 0;
		while(file2>>word && count < 40)
		{
			for(int i=0, l = word.size();i<l;i++)
			{
				if(ispunct(word[i])) //used to find punctuation
				{
					word.erase(i--,1); //must decrement the size of the string after deleted
					l=word.size(); //assigns new size
				}
				for(int j=0; j<word.size();j++) 
					word[j]=tolower(word[j]);//makes all words lowercase
			}
			list2.addAtHead(word); 
			//list2.addAtTail(word); 
			//list2.insert(word,compare);
			count++;
		}
	}
	double start2 = getCPUTime();
	list2.insertionSort(compare);
	double end2 = getCPUTime();
	double time2 = end2-start2;
	cout << time2;
	cout<<list2;

	*/

	newList("paradiselost.txt");
	//wordList("paradiselost.txt");
	
}