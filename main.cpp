/* 
 * File:   main.cpp
 * Author: Haris
 *
 * Created on October 5, 2013, 3:31 PM
 */

#include <iostream>
#include <string.h>
#include "address.h"
//#include "data.h"
#include "data2.h"
#include "network.h"

using namespace std;

int main(int argc, char** argv) {
    addrInNetwork::data input;
    addrInNetwork::address ip;
    addrInNetwork::network net;
    
    if(argc>4 || argc<3){
        cerr<<"Pogresan broj argumenata!\n";
        cerr<<"Primjeri poziva aplikacije:\n";
        cerr<<"./aplikacija --database test.db 10.0.0.0\n";
        cerr<<"./aplikacija mreze.txt 10.0.0.0\n";
        return -1;
    }

    if(strcmp(argv[1],"--database")==0)
    {    
        if (!input.source(addrInNetwork::DATABASE,argv[2]))
        {
            return -1;
        }
        if (!ip.set_addr(argv[3]))
        {
            cerr<<"Pogresna IP adresa";
            return -1;
        }
            
    }
    else
    {
        if (!input.source(addrInNetwork::FILE,argv[1]))
            return -1;
        if (!ip.set_addr(argv[2]))
        {
            cerr<<"Pogresna IP adresa";
            return -1;
        }
    }
    
    char c_name[18];
    string name;
    
    while((name=input.read())!="")
    {
        strcpy(c_name, name.c_str());
        if (!net.set(c_name))
        {
            cerr<<"Pogresna mrezna adresa";
            continue;
        }
        if (net.has_addres(ip))
            cout<<name<<"\n"; 
    }
    
    return 0;
}