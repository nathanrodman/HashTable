//
//  data.cpp
//  Lab3.260.Rodman
//
//  Created by Nathan Rodman on 5/24/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#include "data.h"

data::data(): ticker(nullptr), name(nullptr), date(nullptr), netValue(0), ytd(0)
{
    
}

data::data(const data & aData)
{
    char tempTick[100];
    char tempName[100];
    char tempDate[100];
    
    aData.getTicker(tempTick);
    this->ticker = new char[strlen(tempTick) +1];
    strcpy(ticker, tempTick);
    
    aData.getName(tempName);
    this->name = new char [strlen(tempName) + 1];
    strcpy(name, tempName);
    
    aData.getDate(tempDate);
    this->date = new char [strlen(tempDate)+1];
    strcpy(date, tempDate);
    
    netValue = aData.getValue();
    ytd = aData.getYtd();
}

data::~data()
{
    if(ticker)
        delete [] ticker;
    if(name)
        delete [] name;
    if(date)
        delete [] date;
}

void data::getTicker(char * aTicker) const
{
    strcpy(aTicker, ticker);
}

void data::getName(char * aName) const
{
    strcpy(aName, name);
}

float data::getValue() const
{
    return netValue;
}

void data::getDate(char * aDate) const
{
    strcpy(aDate, date);
}

float data::getYtd() const
{
    return ytd;
}

void data::setTicker(char * aTicker)
{
    if (ticker)
        delete [] ticker;
    ticker = new char[strlen(aTicker) + 1];
    strcpy(ticker, aTicker);
}

void data::setName(char * aName)
{
    if (name)
        delete [] name;
    name = new char [strlen(aName) + 1];
    strcpy(name, aName);
}

void data::setValue(float aValue)
{
    netValue = aValue;
}

void data::setDate(char * aDate)
{
    if(date)
        delete [] date;
    date = new char [strlen(aDate) + 1];
    strcpy(date, aDate);
}

void data::setYtd(float aYtd)
{
    ytd = aYtd;
}

const data& data::operator=(const data& aData)
{
    if(this == &aData)
        return *this;
    else
    {
        setTicker(aData.ticker);
        setName(aData.name);
        setValue(aData.netValue);
        setDate(aData.date);
        setYtd(aData.ytd);
    }
    return *this;
}

bool data::modify(char * tickerSymbol, char * newName, float newNetAssetVal, char * newDate, float newDateReturn)
{
    strcpy(ticker, tickerSymbol);
    strcpy(name, newName);
    netValue = newNetAssetVal;
    strcpy(date, newDate);
    ytd = newDateReturn;
    return true;
}


void data::print() const
{
    cout << "Stock Ticker: " << ticker << endl;
    cout << "Name: " << name << endl;
    cout << "Net Value: $" << netValue << endl;
    cout << "Date of Value: " << date << endl;
    cout << "Year to Date Return: " << ytd << '%' << endl;
}