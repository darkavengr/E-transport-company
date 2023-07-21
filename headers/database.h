/*
 * database.h
 *
 *  Created on: 17 Feb 2022
 *      Author: Adeeb Sait and Matthew Boote
 */

#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#ifndef DATABASE_H_
#define DATABASE_H_

#define MAX_LINE_LENGTH 255

//
// A single database entry
//
class DatabaseEntry {
public:
		 std::string key;						//	key
		 std::vector<std::string> value;				// value
};

//
// A database
//
class Database {

private:
    std::string database_filename;		// filename for the database
    std::vector<DatabaseEntry> database_data;		// The database data
    unsigned int findposition;

public:
    Database();	
    bool Load(std::string filename);
    bool Save(std::string filename);
    std::vector<std::string> Read(std::string key);
    bool Write(std::string key,std::vector<std::string> valuevector);
    std::vector<std::string> Find(void);
    bool New(std::string filename);
    std::string GetFileName(void);
    bool Delete(std::string key);
 };	

#endif /* DATABASE_H_ */

