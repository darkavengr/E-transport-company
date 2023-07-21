#include <streamio>
#include <string>
#include <sqlite3.h>

Database::Database() {
}

Database::Load(std::string filename) {
 sqlite3 *db;
 int returncode;
 
 if(sqlite3_open(filename,&db)) return false;		// Open the database
}

Database::New(std::string filename) {
}

bool Database::Load(std::string filename) {
bool Database::Save(std::string filename) {
std::vector<std::string> Database::Read(std::string key) {
bool Database::Write(std::string key,std::vector<std::string> valuevector) {
std::vector<std::string> Database::Find(void) {
bool Database::New(std::string filename) {
std::string Database::GetFileName(void) {
bool Database::Delete(std::string key) { 
   
