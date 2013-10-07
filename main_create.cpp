/* 
 * File:   main.cpp
 * Author: Haris
 *
 * Created on October 5, 2013, 7:25 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  /* int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");*/
   return 0;
}

static int callback2(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   char *sql;

   rc = sqlite3_open("test.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }
   
   /*sql="DROP TABLE NETWORKS";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table deleted successfully\n");
   }*/
   
   
   
   sql = "CREATE TABLE NETWORKS("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NETWORK        TEXT    NOT NULL);";

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }
   
   

   sql = "INSERT INTO NETWORKS (ID,NETWORK) "  \
         "VALUES (1, '127.1.1.0/16' ); " \
         "INSERT INTO NETWORKS (ID,NETWORK) "  \
         "VALUES (2, '10.4.200.0/18'); "     \
         "INSERT INTO NETWORKS (ID,NETWORK)" \
         "VALUES (3, '10.5.0.0/16');" \
         "INSERT INTO NETWORKS (ID,NETWORK)" \
         "VALUES (4, '10.0.0.0/8');";

   rc = sqlite3_exec(db, sql, callback2, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }
   
   
   sqlite3_close(db);
   return 0;
}


