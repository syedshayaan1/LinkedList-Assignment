#pragma once
//SYED SHAYAAN HASNAIN AHMAD
//20I-0647
//SECTION A
//DATA STRUCTURES ASSIGNMENT 1

// Please give 1 bonus absolute for using templatized structure / class (along with the full running assignment) 

#include<iostream>
#include<iomanip>
#include <fstream>
#include <cmath>

using namespace std;
//typedef string Elem;


template <typename T>
class Node
{
public:
	T elem; //data element (type string in this case)
	Node* next; //Link (pointer) to the next Node
	Node* prev; //Link (pointer) to the previous Node

public:
	Node() : next(NULL), prev(NULL)
	{}
	Node(T elem) : elem(elem), next(NULL), prev(NULL)
	{}
};

//=========================================================================================

template <typename T>
class TransactionLL
{
public:
	Node<T>* head; 	// pointer to the head of List
	Node<T>* tail; 	// pointer to the tail of List
public:
	TransactionLL(); // empty list constructor
	~TransactionLL(); // destructor to clean up all nodes
	bool empty() const; // is list empty?
	void addBefore(Node<T>* ptr, const T& elem);	 //add a new node before ptr
	void addBack(const T& elem); //add a new node to the back of the list
	void removeFront(); // remove front node from list
	string listReturn(); // returns a list in a form that is suitable to write to a file
	void deleteNode(Node<T>** head_ref, Node<T>* del); //DELETE NODES
	void display() const;	// display all element of the list
};

struct Freq
{
	string itemName;
	int itemFrequency;
};

struct Freq2
{
	string itemName;
	string item2Name;
	int itemFrequency;
};

struct Freq3
{
	string itemName;
	string item2Name;
	string item3Name;
	int itemFrequency;
};

TransactionLL <TransactionLL<string>> tList;
int NumTransactions;
float sprtThreshold;
int minimumFreq;
TransactionLL<Freq> firstItemSet;

//====================================================================================================================
//Read Input
//====================================================================================================================

void readInputFile(char* data)
{
	tList.~TransactionLL();
	string line1, line2, line; //It will hold each line from file to put the data into lists in turn.
	int count = 0; //Used to read the last line correctly as it doesnot have space or line break at the end

	//This function will be used to load the data from input file onto the TransactionLL
	ifstream dataFile(data);
	if (!dataFile)
	{
		//IF THE FILE DOES NOT OPEN
		cout << "Error in opening Data.txt file" << endl;
		exit(0);
	}

	//Get data from first 2 lines
	getline(dataFile, line1); //Support Threshold
	getline(dataFile, line2); //number of transactions

	sprtThreshold = stof(line1);
	NumTransactions = stoi(line2);
	minimumFreq = NumTransactions * sprtThreshold;

	for (int i = 1; i <= NumTransactions; i++) { //Fill transactions List with empty lists according to the number of transactions
		TransactionLL<string> L;
		tList.addBack(L); //Now List has 6 nodes (because 6 transactions), and element/data of each node is a List of items
	}

	//Start reading data from file and putting in the linked list.

	Node<TransactionLL<string>>* currT = tList.head->next; //Node holding L1 is now currT
	TransactionLL<string> currL = currT->elem; //L1 is now currL;

	while (getline(dataFile, line))
	{
		count += 1;
		string item = "";
		for (int i = 0; i <= line.length(); i++) {
			if (i == line.length() && count != 6) { //For all the lines except last
				currL.addBack(item);
				item = "";
			}
			else if (i == line.length() && count == 6) { //For last line
				currL.addBack(item);
				item = "";
			}
			else if (line[i] == ',') {
				currL.addBack(item);
				item = "";
			}
			else {
				item = item + line[i];
			}
		}
		currT = currT->next; //Now currT will hold Node containing L2
		currL = currT->elem; //Now, currL is L2
	}


}

//====================================================================================================================
//Remove Punctuation
//====================================================================================================================
void removePunctuationMarks() {

	Node<TransactionLL<string>>* currT = tList.head->next; //Node holding L1 is now currT
	TransactionLL<string> currL = currT->elem; //L1 is now currL;
	Node<string>* curr = currL.head; //curr is now the head node of L1 

	for (int i = 1; i <= NumTransactions; i++) {

		curr = currL.head->next;

		while (curr != currL.tail) {
			string elem = curr->elem;
			string e = "";

			for (int i = 0; i < elem.length(); i++) {
				if ((elem[i] >= 'A' && elem[i] <= 'Z') || (elem[i] >= 'a' && elem[i] <= 'z')) {
					e = e + elem[i];
				}
			}
			curr->elem = e;
			curr = curr->next;
		}
		currT = currT->next;
		currL = currT->elem;
	}
}
//====================================================================================================================
//Convert Upper to Lower
//====================================================================================================================
void convertUpperToLowerCase() {

	Node<TransactionLL<string>>* currT = tList.head->next; //Node holding L1 is now currT
	TransactionLL<string> currL = currT->elem; //L1 is now currL;
	Node<string>* curr = currL.head; //curr is now the head node of L1 

	for (int i = 1; i <= NumTransactions; i++) {

		curr = currL.head->next;

		while (curr != currL.tail) {
			string elem = curr->elem;
			string e = "";

			for (int i = 0; i < elem.length(); i++) {
				if ((elem[i] >= 'A' && elem[i] <= 'Z')) {
					elem[i] = elem[i] + 32;
					e = e + elem[i];
				}
				else {
					e = e + elem[i];
				}
			}
			curr->elem = e;
			curr = curr->next;
		}
		currT = currT->next;
		currL = currT->elem;
	}
}
//====================================================================================================================
//Writing List to File
//====================================================================================================================

void writingTransactionLLToFile(char* outputFilePath) {
	string line;
	int count = 0;

	ofstream outputFile(outputFilePath);
	if (!outputFile)
	{
		//IF THE FILE DOES NOT OPEN
		cout << "Error in opening Data.txt file" << endl;
		exit(0);
	}

	Node<TransactionLL<string>>* currT = tList.head->next; //Node holding L1 is now currT
	TransactionLL<string> currL = currT->elem; //L1 is now currL;

	while (currT != tList.tail) {
		count += 1;
		if (count != NumTransactions) {
			line = currL.listReturn();
			outputFile << line << endl;
		}
		else {
			line = currL.listReturn();
			outputFile << line;
		}
		currT = currT->next;
		currL = currT->elem;
	}
	outputFile.close();
}
//====================================================================================================================
//Generate First Item Set
//====================================================================================================================

void generateFirstItemSet(char* LL_frequency)
{
	bool alreadyExist = false;

	Node<TransactionLL<string>>* currT = tList.head->next; //Node holding L1 is now currT
	TransactionLL<string> currL = currT->elem; //L1 is now currL;

	Node<string>* curr = currL.head;
	Node<Freq>* currF = firstItemSet.head;

	//====================================================================================
	//Set all the unique items and their frequencies in firstItemList

	while (currT != tList.tail) {

		while (curr != currL.tail->prev) {
			curr = curr->next;

			if (firstItemSet.empty())
			{
				Freq tempItems;
				tempItems.itemName = curr->elem;
				tempItems.itemFrequency = 1;
				firstItemSet.addBack(tempItems);
			}
			else
			{
				currF = firstItemSet.head->next;
				alreadyExist = false;

				while (currF != firstItemSet.tail) {

					if (currF->elem.itemName == curr->elem)
					{
						currF->elem.itemFrequency += 1;
						alreadyExist = true;
					}
					currF = currF->next;
				}

				if (!alreadyExist)
				{
					Freq tempItems;
					tempItems.itemName = curr->elem;
					tempItems.itemFrequency = 1;
					firstItemSet.addBack(tempItems);
				}
			}
		}
		currT = currT->next;
		currL = currT->elem;
		curr = currL.head;
	}
	//====================================================================================
	//Remove low freq nodes from TRANSACTIONS LIST tList

	currT = tList.head->next;
	currL = currT->elem;
	curr = currL.head;
	currF = firstItemSet.head->next;
	Node<string>* temp = new Node<string>;

	while (currT != tList.tail) {

		while (curr != currL.tail)
		{
			curr = curr->next;
			currF = firstItemSet.head->next;

			while (currF != firstItemSet.tail) {

				if (currF->elem.itemName == curr->elem)
				{
					if (currF->elem.itemFrequency < minimumFreq)
					{
						temp = curr;
						curr = temp->next;
						currL.deleteNode(&currL.head, temp);

						currF->elem.itemFrequency = currF->elem.itemFrequency - 1;
					}
				}
				currF = currF->next;
			}
		}

		currT = currT->next;
		currL = currT->elem;
		curr = currL.head;
	}
	//====================================================================================
	//Remove low freq nodes from FIRST ITEMS LIST

	Node<Freq>* temp1;

	currF = firstItemSet.head->next;

	while (currF != firstItemSet.tail) {

		if (currF->elem.itemFrequency == 0) {
			temp1 = currF;
			currF = temp1->next;
			firstItemSet.deleteNode(&firstItemSet.head, temp1);
		}
		else
		{
			currF = currF->next;
		}
	}
	//====================================================================================
	//copy firstItemSet list to another which will be sorted and printed
	TransactionLL<Freq> printFirstItems;

	currF = firstItemSet.head->next;
	while (currF != firstItemSet.tail) {
		printFirstItems.addBack(currF->elem);
		currF = currF->next;
	}

	//====================================================================================
	//Bubble Sort the new list to print:	

	int swapped;
	Node<Freq>* ptr1 = new Node<Freq>;
	Node<Freq>* lptr = NULL;

	do
	{
		swapped = 0;
		ptr1 = printFirstItems.head->next;
		while (ptr1->next != printFirstItems.tail)
		{
			if (ptr1->elem.itemFrequency < ptr1->next->elem.itemFrequency)
			{
				Freq tmpStruct = ptr1->elem;
				ptr1->elem = ptr1->next->elem;
				ptr1->next->elem = tmpStruct;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;

	} while (swapped);

	//====================================================================================
	//File output

	ofstream item1_output(LL_frequency);

	if (!item1_output)
	{
		//IF THE FILE DOES NOT OPEN
		cout << "Error in opening Data.txt file" << endl;
		exit(0);
	}

	currF = printFirstItems.head->next;

	while (currF != printFirstItems.tail) {
		if (currF != printFirstItems.tail->prev)
		{
			item1_output << currF->elem.itemName << "(" << to_string(currF->elem.itemFrequency) << ")" << endl;
		}
		else
		{
			item1_output << currF->elem.itemName << "(" << to_string(currF->elem.itemFrequency) << ")";
		}
		currF = currF->next;
	}

	item1_output.close();
}

//====================================================================================================================
//Generate Second Item Set
//====================================================================================================================

void generateSecondItemSet(char* frequency_output_file)
{
	//Make secondIemSet list using FirstItemSet

	TransactionLL<Freq2> secondItemSet;

	Node<Freq>* currF = firstItemSet.head->next;
	Node<Freq>* currFN = currF->next;

	while (currF != firstItemSet.tail->prev)
	{
		while (currFN != firstItemSet.tail)
		{
			Freq2 tempItems;
			tempItems.itemName = currF->elem.itemName;
			tempItems.item2Name = currFN->elem.itemName;
			tempItems.itemFrequency = 0;
			secondItemSet.addBack(tempItems);
			currFN = currFN->next;
		}
		currF = currF->next;
		currFN = currF->next;
	}
	//====================================================================================
	//Add correct frequencies

	Node<TransactionLL<string>>* currT = tList.head->next;
	TransactionLL<string> currL = currT->elem;
	Node<string>* curr = currL.head;
	Node<Freq2>* currF2 = secondItemSet.head->next;

	while (currF2 != secondItemSet.tail)
	{
		currT = tList.head->next;
		currL = currT->elem;
		curr = currL.head;

		while (currT != tList.tail) {

			bool item1Found = false;
			bool item2Found = false;

			while (curr != currL.tail)
			{
				curr = curr->next;

				if (curr->elem == currF2->elem.itemName)
				{
					item1Found = true;
				}
				else if (curr->elem == currF2->elem.item2Name)
				{
					item2Found = true;
				}

				if (item1Found && item2Found)
				{
					currF2->elem.itemFrequency += 1;
					item1Found = false;
					item2Found = false;
				}
			}
			currT = currT->next;
			currL = currT->elem;
			curr = currL.head;
		}
		currF2 = currF2->next;
	}
	//====================================================================================
	//Remove low freq nodes from SECOND ITEMS LIST

	Node<Freq2>* tmp = new Node<Freq2>;

	currF2 = secondItemSet.head->next;

	while (currF2 != secondItemSet.tail) {

		if (currF2->elem.itemFrequency < minimumFreq) {
			tmp = currF2;
			currF2 = tmp->next;
			secondItemSet.deleteNode(&secondItemSet.head, tmp);
		}
		else
		{
			currF2 = currF2->next;
		}
	}

	//====================================================================================
	//Bubble Sort the list to print:

	int swapped;
	Node<Freq2>* ptr1 = new Node<Freq2>;
	Node<Freq2>* lptr = NULL;

	do
	{
		swapped = 0;
		ptr1 = secondItemSet.head->next;
		while (ptr1->next != secondItemSet.tail)
		{
			if (ptr1->elem.itemFrequency < ptr1->next->elem.itemFrequency)
			{
				Freq2 tmpStruct = ptr1->elem;
				ptr1->elem = ptr1->next->elem;
				ptr1->next->elem = tmpStruct;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;

	} while (swapped);

	//====================================================================================
	//File Output
	ofstream item2_output(frequency_output_file);

	if (!item2_output)
	{
		//IF THE FILE DOES NOT OPEN
		cout << "Error in opening Data.txt file" << endl;
		exit(0);
	}

	currF2 = secondItemSet.head->next;

	while (currF2 != secondItemSet.tail) {
		if (currF2 != secondItemSet.tail->prev)
		{
			item2_output << currF2->elem.itemName << "," << currF2->elem.item2Name << "(" << to_string(currF2->elem.itemFrequency) << ")" << endl;
		}
		else //For last line, don't add endl
		{
			item2_output << currF2->elem.itemName << "," << currF2->elem.item2Name << "(" << to_string(currF2->elem.itemFrequency) << ")";
		}
		currF2 = currF2->next;
	}
	item2_output.close();
}

//====================================================================================================================
//Generate Third Item Set
//====================================================================================================================

void generateThirdItemSet(char* frequency_output_file)
{
	//Make thirdItemSet list using FirstItemSet

	TransactionLL<Freq3> thirdItemSet;

	Node<Freq>* currF = firstItemSet.head->next;
	Node<Freq>* currFN = currF->next;
	Node<Freq>* currFNN = currFN->next;

	while (currF != firstItemSet.tail->prev->prev)
	{
		while (currFN != firstItemSet.tail->prev)
		{
			while (currFNN != firstItemSet.tail)
			{
				Freq3 tempItems;
				tempItems.itemName = currF->elem.itemName;
				tempItems.item2Name = currFN->elem.itemName;
				tempItems.item3Name = currFNN->elem.itemName;
				tempItems.itemFrequency = 0;
				thirdItemSet.addBack(tempItems);

				currFNN = currFNN->next;
			}
			currFN = currFN->next;
			currFNN = currFN->next;
		}
		currF = currF->next;
		currFN = currF->next;
		currFNN = currFN->next;
	}
	//====================================================================================
	//Add correct frequencies

	Node<TransactionLL<string>>* currT = tList.head->next;
	TransactionLL<string> currL = currT->elem;
	Node<string>* curr = currL.head;
	Node<Freq3>* currF3 = thirdItemSet.head->next;

	while (currF3 != thirdItemSet.tail)
	{
		currT = tList.head->next;
		currL = currT->elem;
		curr = currL.head;

		while (currT != tList.tail) {

			bool item1Found = false;
			bool item2Found = false;
			bool item3Found = false;

			while (curr != currL.tail)
			{
				curr = curr->next;

				if (curr->elem == currF3->elem.itemName)
				{
					item1Found = true;
				}
				else if (curr->elem == currF3->elem.item2Name)
				{
					item2Found = true;
				}
				else if (curr->elem == currF3->elem.item3Name)
				{
					item3Found = true;
				}

				if (item1Found && item2Found && item3Found)
				{
					currF3->elem.itemFrequency += 1;
					item1Found = false;
					item2Found = false;
					item3Found = false;
				}

			}
			currT = currT->next;
			currL = currT->elem;
			curr = currL.head;
		}
		currF3 = currF3->next;
	}

	//====================================================================================
	//Remove low freq nodes from SECOND ITEMS LIST

	Node<Freq3>* tmp = new Node<Freq3>;

	currF3 = thirdItemSet.head->next;

	while (currF3 != thirdItemSet.tail) {

		if (currF3->elem.itemFrequency < minimumFreq) {
			tmp = currF3;
			currF3 = tmp->next;
			thirdItemSet.deleteNode(&thirdItemSet.head, tmp);
		}
		else
		{
			currF3 = currF3->next;
		}
	}

	//====================================================================================
	//Bubble Sort third item list:	

	int swapped;
	Node<Freq3>* ptr1 = new Node<Freq3>;
	Node<Freq3>* lptr = NULL;

	do
	{
		swapped = 0;
		ptr1 = thirdItemSet.head->next;
		while (ptr1->next != thirdItemSet.tail)
		{
			if (ptr1->elem.itemFrequency < ptr1->next->elem.itemFrequency)
			{
				Freq3 tmpStruct = ptr1->elem;
				ptr1->elem = ptr1->next->elem;
				ptr1->next->elem = tmpStruct;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;

	} while (swapped);

	//====================================================================================
	//File Output
	ofstream item3_output(frequency_output_file);

	if (!item3_output)
	{
		//IF THE FILE DOES NOT OPEN
		cout << "Error in opening Data.txt file" << endl;
		exit(0);
	}

	currF3 = thirdItemSet.head->next;

	while (currF3 != thirdItemSet.tail) {
		if (currF3 != thirdItemSet.tail->prev)
		{
			item3_output << currF3->elem.itemName << "," << currF3->elem.item2Name << "," << currF3->elem.item3Name << "(" << to_string(currF3->elem.itemFrequency) << ")" << endl;
		}
		else //For last line, don't add endl
		{
			item3_output << currF3->elem.itemName << "," << currF3->elem.item2Name << "," << currF3->elem.item3Name << "(" << to_string(currF3->elem.itemFrequency) << ")";
		}
		currF3 = currF3->next;
	}
	item3_output.close();
}

//====================================================================================================================
//Main
//====================================================================================================================
/*
int main()
{
	char* filename = "data.txt";
	readInputFile(filename);
	removePunctuationMarks();
	convertUpperToLowerCase();
	generateFirstItemSet("output2.txt");
	writingTransactionLLToFile("output.txt");
	generateSecondItemSet("output3.txt");
	generateThirdItemSet("output4.txt");

	return EXIT_SUCCESS;
}

*/


//====================================================================================================================
//Linked List Methods
//====================================================================================================================

template <typename T>
TransactionLL<T>::TransactionLL()
{
	this->head = new Node<T>();
	this->tail = new Node<T>();
	this->head->next = tail;
	this->tail->prev = head;
}
//============================================================
template <typename T>
TransactionLL<T>::~TransactionLL() // destructor to clean up all nodes
{
	while (!empty())
		removeFront();
}
//============================================================
template <typename T>
bool TransactionLL<T>::empty() const // is list empty?
{
	return this->head->next == tail;
}
//============================================================

template <typename T>
void TransactionLL<T>::addBefore(Node<T>* ptr, const T& elem)
{
	Node<T>* tmp = new Node<T>(elem);
	tmp->next = ptr;
	tmp->prev = ptr->prev;
	ptr->prev->next = tmp;
	ptr->prev = tmp;
}

//============================================================
template <typename T>
void TransactionLL<T>::removeFront() // remove front item from list
{
	if (!empty())
	{
		Node<T>* tmp = this->head->next;
		this->head->next = tmp->next;
		tmp->next->prev = head;
		delete tmp;
	}
}
//============================================================
template <typename T>
void TransactionLL<T>::addBack(const T& elem) // add to Back of the list
{
	addBefore(this->tail, elem);
}
//============================================================

template <typename T>
string TransactionLL<T>::listReturn()
{
	Node<string>* tmp = head->next;
	string list = "";
	if (!empty())
	{
		while (tmp != tail)
		{
			if (tmp == tail->prev)
			{
				list = list + tmp->elem;
			}
			else
			{
				list = list + tmp->elem + ',';
			}

			tmp = tmp->next;
		}
	}
	else
	{
		list = "";
	}
	return list;
}


template <typename T>
void TransactionLL<T>::deleteNode(Node<T>** head_ref, Node<T>* del)
{

	if (*head_ref == NULL || del == NULL)
	{
		return;
	}

	if (*head_ref == del)
	{
		*head_ref = del->next;
	}

	if (del->next != NULL)
	{
		del->next->prev = del->prev;
	}

	if (del->prev != NULL)
	{
		del->prev->next = del->next;
	}

	free(del);
}

//=============================================================================================================================================================

template <typename T>
void TransactionLL<T>::display() const
{
	Node<T>* curr = head;
	while (curr != NULL)
	{
		cout << "+------";
		curr = curr->next;
	}
	cout << "+" << endl << "|";
	curr = head;
	while (curr != NULL)
	{
		if (curr == head)		cout << " Head |";
		else if (curr == tail)	cout << " Tail |";
		else 					cout << setw(5) << curr->elem.itemName << "," << curr->elem.item2Name << "," << curr->elem.item3Name << "," << curr->elem.itemFrequency << " |";

		curr = curr->next;
	}
	curr = head;
	cout << endl;
	while (curr != NULL)
	{
		cout << "+------";
		curr = curr->next;
	}
	cout << "+" << endl;
}
