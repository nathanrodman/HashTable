//
//  data.h
//  Lab3.260.Rodman
//
//  Created by Nathan Rodman on 5/24/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#ifndef Lab3_260_Rodman_data_h
#define Lab3_260_Rodman_data_h

#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

class data
{
public:
    data();
    data(const data & aData);
    ~data();
    
    void getTicker(char * aTicker)const;
    void getName(char * aName)const;
    float getValue() const;
    void getDate(char * aDate) const;
    float getYtd() const;

    void setTicker(char * aTicker);
    void setName(char * aName);
    void setValue(float aValue);
    void setDate(char * aDate);
    void setYtd(float aYtd);
    
    bool modify(char * tickerSymbol, char * newName, float newNetAssetVal, char * newDate, float newDateReturn);
    
    void print() const;
    
    const data& operator=(const data& aData);
    
private:
    char * ticker;
    char * name;
    float netValue;
    char * date;
    float ytd;
};


#endif
