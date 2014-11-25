//
//  hashtable.cpp
//  Lab3.260.Rodman
//
//  Created by Nathan Rodman on 5/24/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#include "hashtable.h"
#include "data.h"


void hashTable::initializeTable()
{
	table = new node*[capacity];
    
	int i;
	for(i=0; i<capacity; i++)
		table[i] = NULL;
}

hashTable::hashTable(): capacity(DEFAULT_CAPACITY), size(0)
{
    initializeTable();
}

hashTable::hashTable(const hashTable & aTable): capacity(aTable.capacity), size(aTable.size)
{
    table = new node*[capacity];
   
	int i;
	for(i=0; i<capacity; i++)
	{
		if (aTable.table[i] == NULL)
			table[i] = NULL;
		else
		{
			table[i] = new node(aTable.table[i]->item);
            
			node * srcNode = aTable.table[i]->next;
			node * destNode = table[i];
			while(srcNode)
			{
				destNode->next = new node(srcNode->item);
				destNode = destNode->next;
				srcNode = srcNode->next;
			}
			destNode->next = NULL;
		}
	}
}

hashTable::hashTable(const char * fileName): capacity(DEFAULT_CAPACITY), size(0)
{
    ifstream inFile;
    data aData;
    char tempTicker[100];
    char tempName[100];
    char tempDate[100];
    float value, ytd;
    
    initializeTable();
    
    inFile.open(fileName);
    if(!inFile)
    {
        cerr << "Error, unable to open file named \"" << fileName << "\"" << endl;
        exit(2);
    }
    
    inFile.get(tempTicker, 100, ';');
    while(!inFile.eof())
    {
        inFile.ignore(100, ';');
        inFile.get(tempName, 100, ';');
        inFile.ignore(100, ';');
        inFile >> value;
        inFile.ignore(100, ';');
        inFile.get(tempDate, 100, ';');
        inFile.ignore(100, ';');
        inFile >> ytd;
        inFile.ignore(100, '\n');
        
        aData.setTicker(tempTicker);
        aData.setName(tempName);
        aData.setValue(value);
        aData.setDate(tempDate);
        aData.setYtd(ytd);
        
        insert(aData);
        
        inFile.get(tempTicker, 100, ';');
        
    }
    inFile.close();
}

void hashTable::destroyTable ()
{

	int i;
	for(i=0; i<capacity; i++)
	{
		node * head = table[i];
		node * curr;
		while(head)
		{
			curr = head->next;
			head->next = NULL;
			delete head;
			head = curr;
		}
	}
    
	delete [] table;
}

hashTable::~hashTable()
{
    destroyTable();
}

void hashTable::writeOut(char * fileName)
{
    ofstream out;
    out.open(fileName);
    
    int i;
	char ticker[100];
	char name[100];
    char date[100];

	node * curr;
	for(i=0; i<capacity; i++)
	{
		for(curr = table[i]; curr; curr = curr->next)
		{
			curr->item.getTicker(ticker);
			curr->item.getName (name);
            curr->item.getDate(date);
			out << ticker << ';' << name << ';' << curr->item.getValue() << ';' << date << ';' << curr->item.getYtd() << '\n';
		}
	}
	out.close ();
}

int hashTable::calculateIndex (char * key)const
{
	char * c = key;
	int total = 0;
	while(*c)
	{
		total += *c;
		c++;
	}
    
	return total%capacity;
}

bool hashTable::retrieve (char * key, data & aData)const
{

	int index = calculateIndex(key);

	node * curr = table[index];
	char ticker[100];
	while (curr)
	{
		curr->item.getTicker(ticker);
		if(strcmp(key, ticker) == 0)
		{
			aData = curr->item;
			return true;
		}
		else
			curr = curr->next;
	}
    
	return false;
}

void hashTable::insert (const data& aData)
{
	char key[100];
    char compare[100];
	aData.getTicker(key);
	int index = calculateIndex(key);

	node * newNode = new node(aData);
    
    if (table[index] == nullptr)
    {
        newNode->next = table[index];
        table[index] = newNode;
    }
    else
    {
        node * curr = nullptr;
        for(curr = table[index]; curr; curr = curr->next)
        {
            curr->item.getTicker(compare);
            if (strcmp(compare, key) > 0)
            {
                newNode->next = curr->next;
                curr->next = newNode;
            }
            
        }
    }
    
	size++;
}

bool hashTable::remove (char * key)
{
	int index = calculateIndex(key);
    
	
	node * curr = table[index];
	node * prev = NULL;
	char ticker[100];
	while (curr)
	{
		curr->item.getTicker(ticker);
		if(strcmp(key, ticker) == 0)
		{
			//find match and remove the node
			if(!prev)
				table[index] = curr->next;
			else
				prev->next = curr->next;
            
			curr->next = NULL;
			delete curr;
			size--;
			return true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return false;
}

void hashTable::display (void)const
{
	int i;
	node * curr;
    
	cout << "Data in the table: " << endl << endl;
	for(i=0; i<capacity; i++)
	{
		for(curr = table[i]; curr; curr = curr->next)
        {
			cout << '\t';
            curr->item.print();
            cout << endl;
        }
	}
}

int hashTable::getSize (void) const
{
	return size;
}

void hashTable::monitor()
{
    for (int i = 0; i < capacity; i++)
    {
        cout << "[" << i << "] : ";
        if (table[i] == nullptr)
            cout << "0" << endl;
        else
        {
            node * curr = table[i];
            int j;
            for(j = 1; curr; curr = curr->next)
                j++;
            cout << j << endl;
        }
    }
}

bool hashTable::modify(char * key)
{
    data aData;
    char ticker[100], name[100], date[100];
    float value, ytd;
    retrieve(key, aData);
    remove(key);
    cin.ignore(100, '\n');
    cout << "Enter the new ticker: ";
    cin.get(ticker, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Enter the new name: ";
    cin.get(name, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Enter the new net value: ";
    cin >> value;
    cin.ignore(100, '\n');
    cout << "Enter the date of value: ";
    cin.get(date, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Enter the YTD return: ";
    cin >> ytd;
    
    
    
    aData.modify(ticker, name, value, date, ytd);
    insert(aData);
    
    return true;
}


