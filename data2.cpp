#include "data2.h"

namespace addrInNetwork
{
    bool data::source (char type, char * name)
    {
        _type=type;
        if(type==FILE)
        {
            _file.open(name);
            if (_file.is_open())
                return true;
            std::cerr<<"Ne moze se otvoriti fajl "<<name;
        }
        else if(type==DATABASE)
        {
            
            if(sqlite3_open(name, &_db) != SQLITE_OK)
            {
                std::cerr<<sqlite3_errmsg(_db);
                return false;
            }
            if (sqlite3_prepare( _db, "SELECT * FROM NETWORKS ORDER BY ID LIMIT ?;", -1, &_stmt, NULL )!=SQLITE_OK)
            {
                std::cerr<<sqlite3_errmsg(_db);
                return false;
            }
            //thread
            _offset+=LIMIT;
            t_data._db=_db;
            t_data.LIMIT=LIMIT;
            t_data._offset=_offset;
            if (pthread_create(&tid, NULL, load_records, (void *)&t_data) != 0) 
            {
                std::cerr<<"Neuspjelo kreiranje niti!";
                return false;
            }

            //
            sqlite3_bind_int(_stmt, 1, LIMIT);
            return true;
        }
        return false;
    }
    std::string data::read()
    {
        
        std::string line;
        if(_type==FILE)
        {
            if (std::getline(_file, line))
                return line;
            else
                return std::string();
        }
        else if (_type==DATABASE)
        {
            
            int res=sqlite3_step( _stmt );
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                /*sqlite3_finalize(_stmt);
                if (sqlite3_prepare( _db, "SELECT * FROM networks WHERE id > ? ORDER BY id LIMIT ?;", -1, &_stmt, NULL )!=SQLITE_OK)
                    return std::string();
                sqlite3_bind_int(_stmt, 2, LIMIT);
                sqlite3_bind_int(_stmt, 1, _offset);

                if(sqlite3_step( _stmt )!=SQLITE_ROW)
                    return std::string();*/
                
                //thread
                _offset+=LIMIT;
                
                sqlite3_finalize(_stmt);
                
                if (pthread_join(tid, &t_result) != 0) 
                {
                    perror("Neuspjelo cekanje na zavrsetak izvrsavanja niti!");
                    return std::string();
                }
                _stmt=(sqlite3_stmt *)t_result;
                if (_stmt==NULL)
                    return std::string();
                t_data._db=_db;
                t_data.LIMIT=LIMIT;
                t_data._offset=_offset;
                if (pthread_create(&tid, NULL, load_records, (void *)&t_data) != 0) 
                {
                    std::cerr<<"Neuspjelo kreiranje niti!";
                    return std::string();
                }
                
                //
                
            }
            _offset=sqlite3_column_int( _stmt, 0 );
            return std::string( (char *)sqlite3_column_text( _stmt, 1 ) );
        }
        return std::string();
    }
   
    data::~data(){
        if(_type==FILE)
        {
            _file.close();
        }
        else if(_type==DATABASE)
        {
            sqlite3_close(_db);
        }
    }
    //thread
    void * data::load_records(void *arg)
    {
        d_thread * t_data=(d_thread *)arg;
        sqlite3_stmt * _stmt2;
        if (sqlite3_prepare( t_data->_db, "SELECT * FROM networks, (SELECT id FROM networks ORDER BY id LIMIT ? OFFSET ?) as net WHERE net.id=networks.id;", -1, &_stmt2, NULL )!=SQLITE_OK)
            pthread_exit(NULL);
        sqlite3_bind_int(_stmt2, 1, t_data->LIMIT);
        sqlite3_bind_int(_stmt2, 2, t_data->_offset);
        t_data->_offset+=t_data->LIMIT;
        if(sqlite3_step( _stmt2 )!=SQLITE_ROW)
            pthread_exit(NULL);
        
        pthread_exit(_stmt2);
    }
    //
}
