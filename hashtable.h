//
//  hashtable.h
//  Lab3.260.Rodman
//
//  Created by Nathan Rodman on 5/24/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#ifndef Lab3_260_Rodman_hashtable_h
#define Lab3_260_Rodman_hashtable_h

#include "data.h"


class hashTable
{
public:
    hashTable();
    hashTable(const hashTable & aTable);
    hashTable(const char * fileName);
    ~hashTable();
    
    const hashTable& operator= (const hashTable & aTable);
    
    void insert(const data& aData);
	bool remove(char * key);
	bool retrieve(char * key, data& aData)const;

	void display(void)const;
	int getSize(void)const;
    
    bool modify(char * key);
	void writeOut(char * fileName);
    void monitor();
    
    
private:
    struct node
	{
		data item;
		node * next;
		node(const data& aData)
		{
			item = aData;
			next = nullptr;
		}
	};
	node ** table;
	int capacity;
	int size;
	const static int DEFAULT_CAPACITY = 11;
    
	void destroyTable();
	void initializeTable();
	int calculateIndex(char * key)const;
};

#endif
