/* 
 * File:   data.h
 * Author: haris
 *
 * Created on October 6, 2013, 1:31 PM
 */

#ifndef DATA_H
#define	DATA_H
#include <sqlite3.h> 
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdexcept>
//thread
#include <pthread.h>
#include <unistd.h>
//
namespace addrInNetwork
{
    char const FILE=0;
    char const DATABASE=1;
    class data
    {
        char _type;
        std::ifstream _file;
        sqlite3 * _db;
        sqlite3_stmt * _stmt;
        long unsigned int _offset;
        unsigned int const LIMIT;
        //thread
        pthread_t tid;
        void *t_result;
        
        //
        
    public:
        //thread
        struct d_thread{
            sqlite3 * _db;
            long unsigned int _offset;
            unsigned int LIMIT;
        };
        d_thread t_data;
        static void * load_records(void *);
        //
        data():_db(NULL),_stmt(NULL),_offset(0),_type(-1),LIMIT(200){}
        bool source (char type, char * name);
        std::string read();
        ~data();
    };

}


#endif	/* DATA_H */

