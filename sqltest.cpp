#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void insertSQL(sqlite3 *db, int rc, char *zErrMsg){
    const char* sql = 
        "INSERT INTO USERS (USERNAME,GEAR,RETURN) "  \
        "VALUES ('rstowe', 'kayak,10', 2017-04-12); " \
        "INSERT INTO USERS (USERNAME,GEAR,RETURN) "  \
        "VALUES ('tmack', 'thescoop,1', 2018-08-21); " \
        "INSERT INTO USERS (USERNAME,GEAR,RETURN)" \
        "VALUES ('wcadwell', 'everything,7', 2020-04-12); " \
        "INSERT INTO USERS (USERNAME,GEAR,RETURN)" \
        "VALUES ('mstrayer', 'paracord,10', 2017-06-20);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Records created successfully\n");
    }
}

void createTableSQL(sqlite3 *db, int rc, char *zErrMsg){
    const char* sql = "CREATE TABLE USERS("  \
    "USERNAME       TEXT    PRIMARY KEY     NOT NULL," \
    "GEAR           TEXT    NOT NULL," \
    "RETURN           DATE    NOT NULL);";

        // Execute SQL statement //
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }

}

void insertParams(sqlite3 *db, int rc, char *zErrMsg, 
            std::string name, std::string gear, std::string date){
    const char* sql = "INSERT INTO USERS (USERNAME,GEAR,RETURN)" \
        "VALUES (" + name + "," + gear + "," + date + ");";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Records created successfully\n");
    }
}

int main(int argc, char* argv[]){
    sqlite3 *db;
    char *zErrMsg = 0;
    int  rc;

    // Open database 
    rc = sqlite3_open("test.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }else{
        fprintf(stdout, "Opened database successfully\n");
    }

    createTableSQL(db, rc, zErrMsg);

    insertSQL(db, rc, zErrMsg);

    // Close database
    sqlite3_close(db);
    return 0;
}