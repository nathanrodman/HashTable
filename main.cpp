//
//  main.cpp
//  Lab3.260.Rodman
//
//  Created by Nathan Rodman on 5/24/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#include "data.h"
#include"hashtable.h"
#include <iostream>
using namespace std;

void displaymenu();
void menuoptions(char decider, hashTable & table);
void makeData(hashTable & table);

int main(int argc, const char * argv[])
{
    char fileName[] = "stocks.txt";
    hashTable aTable(fileName);
    data stock;
    
    char decision = 'a';
    cout << "---------------------------------------" << endl;
    cout << "|-|-|-|-| Trading Tracker 1.0 |-|-|-|-|" << endl;
    cout << "---------------------------------------" << endl;
    
    
    while(decision != 'q')
    {
        displaymenu();
        cin >> decision;
        decision = tolower(decision);
        menuoptions(decision, aTable);
        
    }
    
    aTable.writeOut(fileName);
    return 0;
}

void displaymenu()
{
    cout << "Choose from the following menu options:" << endl;
    cout << "\td) Display stocks" << endl;
    cout << "\ta) Add a stock to the list" << endl;
    cout << "\te) Edit a stock in the list" << endl;
    cout << "\tf) Find a stock" << endl;
    cout << "\tr) Remove a stock from the list" << endl;
    cout << "\tq) Quit the program" << endl;
    cout << "\tm) For monitoring table" << endl;
    cout << "Please type the corresponding letter: ";
}

void menuoptions(char decider, hashTable & table)
{
    data aData;
    char key[100];
    switch (decider)
    {
        case 'd':
            table.display();
            break;
        case 'a':
            makeData(table);
            break;
        case 'm':
            table.monitor();
            break;
        case 'e':
            cout << "Enter the stock ticker you'd like to edit: ";
            cin.ignore(100, '\n');
            cin.get(key, 100, '\n');
            table.modify(key);
            break;
            
        case 'r':
            cout << "Enter the stock ticker you'd like to remove: ";
            cin.ignore(100, '\n');
            cin.get(key, 100, '\n');
            table.remove(key);
            break;
            
        case 'f':
            cout << "Enter the stock ticker you'd like to find: ";
            cin.ignore(100, '\n');
            cin.get(key, 100, '\n');
            table.retrieve(key, aData);
            aData.print();
            break;
            
        case 'q':
            cout << "------Program Terminated------";
            break;
            
    }
}

void makeData(hashTable & table)
{
    data aData;
    char ticker[100];
    char name[100];
    char date[100];
    float value, ytd;
    cin.ignore(100, '\n');
    cout << "Please enter the stock ticker: ";
    cin.get(ticker, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter the stock asset name: ";
    cin.get(name, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please etner the net asset value: ";
    cin >> value;
    cin.ignore(100, '\n');
    cout << "Please enter the date of that value: ";
    cin.get(date, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Please enter the year-to-date return: ";
    cin >> ytd;
    cin.ignore(100, '\n');
    
    aData.setTicker(ticker);
    aData.setName(name);
    aData.setValue(value);
    aData.setDate(date);
    aData.setYtd(ytd);
    
    table.insert(aData);

}