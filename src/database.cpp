/* 
 * database.cpp
 *
 *      Author: Adeeb Sait and Matthew Boote
 *
 */

/** @file */ 

#include <iostream>
#include <stdio.h>

#include "database.h"
#include "exception.h"

/*!
 *\file database.cpp
    * 
    * \class Database
    * @brief Database class
    * 
    * @author Matthew Boote
    *
    * @details This class implements functions for storing and retrieving data from a database.
    *
    */

/*!
 *\file database.cpp
    * 
    * Database()
    *
    * @brief Database constructor
    * 
    * @author Matthew Boote
    *  
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return Boolean None
    *
    */
Database::Database() {
}

/*!
 *\file database.cpp
    * 
    * Load()
    *
    * @brief Loads a database into memory
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string filename
    * 
    * @param[out] None
    *
    * @return Boolean true or false
    *
    */
bool Database::Load(std::string filename) {
 int count;
 int tcount=0;
 DatabaseEntry temp;
 std::string line;
 std::vector<std::string> parsebuffer;
 std::string tempstring;
 int linecount=0;
 findposition=0;
 std::fstream handle;

handle.open(filename);
 if(!handle) {					// error opening file
  return(false);
 }	    
  

 //
 // Read CSV file into the database
 //

 do {						// until end of file
	 getline(handle,line);			// read line from file
	 linecount++;
	 	
	 tempstring="";

	 if(line.empty()) continue;		// empty line
	
	 parsebuffer.clear();

	 tcount=0;

	 
	 for(count=0;count<line.length();count++) {		// until end of line
  	   if(line[count] == ',') {			// at end of token		
		parsebuffer.push_back(tempstring);		// copy to token
		
		tempstring="";
	
		tcount++;
		continue;
 	    }
	     else { 				    	   
 		tempstring += line[count];
	     }
	 }
	 	 
 	
//
// Create entry object
//
       temp.key=parsebuffer[0];				// get key
	
// get values
	temp.value.clear();

	for(count=1;count<tcount;count++) {
	  temp.value.push_back(parsebuffer[count]);		// get value
	}

// If there was a token at the end that was not delimited by a token, add it to vector

	if(tempstring.compare("") != 0) temp.value.push_back(tempstring);

//
// Add to database
//	
  database_data.push_back(temp);				// add to vector
 } while(!handle.eof());			// until end of file

 handle.close();

 database_filename=filename;			// internal filename
 return(true);
}

/*!
 *\file database.cpp
    * 
    * Save()
    *
    * @brief Saves a database
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string filename
    * 
    * @return Boolean true or false
    *
    * @throw Throws an error on file I/O error
    */

bool Database::Save(std::string filename) {
 std::vector<DatabaseEntry>::iterator i;
 unsigned int count;
 std::fstream handle;

 try {
  handle.open(filename,std::fstream::out);					// open file

  if(!handle) {					// error opening file
   throw "Error opening file "+filename;
  }
 }
  catch(const char *message) {
   exception_handler(message);
   return(false);
  }


 //
// Save database to CSV file
//

// Save entries

// loop through database entries

 for(i=database_data.begin();i != database_data.end();i++) {

//
// for each entry, write out key+values

  handle << i->key << ",";			  // write out key

// write out values
  for(count=0;count<i->value.size();count++) {
   handle << i->value[count];

   if(count < i->value.size()-1) {
	handle << ",";		// write separator        
   }

  }

  handle << std::endl;		// write separator
 }

 handle.close();

 return(true);
}

/*!
 *\file database.cpp
    * 
    * Read()
    *
    * @brief Reads a row from the database
    * 
    * @author Matthew Boote
    *
    * @details Reads a row of key+values from the database
    *
    * @param[in] std::string key
    * 
    * @param[out] None
    *
    * @return std::vector<std::string>
    *
    */
std::vector<std::string> Database::Read(std::string key) {
 std::vector<DatabaseEntry>::iterator i;
 unsigned int count;
 std::vector<std::string> valuevector;

 for(i=database_data.begin();i != database_data.end();i++) {

//
// for each entry, find key
  
  if(key.compare(i->key) == 0) {		// found key
   valuevector.clear();

   valuevector.push_back(i->key);		// copy key

// copy values

  for(count=0;count<i->value.size();count++) { 
   valuevector.push_back(i->value[count]);
  }

  return(valuevector);
 }
}

 return(std::vector<std::string> {});
}

/*!
 *\file database.cpp
    * 
    * Write()
    *
    * @brief Writes a row to the database
    * 
    * @author Matthew Boote
    *
    * @details Writes a row of key+values to the database
    *
    * @param[in] std::string key,std::vector<std::string> valuevector
    * 
    * @param[out] None
    *
    * @return std::vector<std::string>
    *
    */
bool Database::Write(std::string key,std::vector<std::string> valuevector) {
 std::vector<DatabaseEntry>::iterator i;
 unsigned int count;
 DatabaseEntry temp;

 for(i=database_data.begin();i != database_data.end();i++) {
  if(key.compare(i->key) == 0) {		// found key
    
// copy values
   for(count=0;count<valuevector.size();count++) {   

//
// If before end, insert. Otherwise append
//
    if(count < i->value.size()) {			// If inserting
	   i->value[count]=valuevector[count];
    }
    else {
	  i->value.push_back(valuevector[count]);	// append
   }
  }

  Save(database_filename);
  return true;
 }

}

/* new entry */

  temp.key=key;
	
// copy values
   for(count=1;count<valuevector.size();count++) {   
     temp.value.push_back(valuevector[count]);
  }

  database_data.push_back(temp);

  Save(database_filename);
  return true;
}

/*!
 *\file database.cpp
    * 
    * Find()
    *
    * @brief Finds a row in the database
    * 
    * @author Matthew Boote
    *
    * @details Finds the next row in turn in the database
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::vector<std::string>
    *
    */
std::vector<std::string> Database::Find(void) {
int count;
std::vector<std::string> valuevector;

//
// This uses a integer to store the current position
// because it isn't possible to store an iterator in
// an object

  std::vector<DatabaseEntry>::iterator iter = database_data.begin();  // go to start
  std::advance(iter,findposition);		// and to current entry

  if(iter == database_data.end()) {		// if at end
   findposition=0;
   return {};
  }

 valuevector.clear();

 valuevector.push_back(iter->key);		// copy key

// copy values
  for(count=0;count<iter->value.size();count++) {
   valuevector.push_back(iter->value[count]);
  }

  findposition++;
  return(valuevector); 
}


/*!
 *\file database.cpp
    * 
    * New()
    *
    * @brief Creates a new database
    * 
    * @author Matthew Boote
    *
    * @details Creates a database object and corresponding file.
    *
    * @param[in] std::string filename
    * 
    * @param[out] None
    *
    * @return boolean true or false
    *
    * @throw Throws on I/O error
    *
    */
bool Database::New(std::string filename) {
 std::fstream handle;
 database_filename=filename;		// filename for the database
 database_data.clear();			// The database data
 findposition=0;
 
 handle.open(filename,std::ios::out);	// create the file
 if(!handle) return(false);
 
 return(true);
 }


/*!
 *\file database.cpp
    * 
    * GetFileName()
    *
    * @brief Returns the database filename
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string database_filename
    *
    */
std::string Database::GetFileName(void) {
 return(database_filename);
}

/*!
 *\file database.cpp
    * 
    * Delete()
    *
    * @brief Deletes a row from the database
    * 
    * @author Matthew Boote
    *
    * @details Deletes a row associated with a key
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return boolean true or false
    *
    */
bool Database::Delete(std::string key) {
 std::vector<DatabaseEntry>::iterator i;
 unsigned int count;
 bool WasUpdated=false;

 //
// Save database to CSV file
//

// Save entries

// loop through database entries

 for(i=database_data.begin();i != database_data.end();i++) {

  if(key.compare(i->key) == 0) {		// if is entry

   database_data.erase(i);			// erase it
  
   WasUpdated=true;				// set updated flags
   break;
  }
 }

 if(WasUpdated == true) {
  Save(GetFileName());				// save database
  return(true);
 }
	
 return(false);
}
