/*
 * message.h
 *
 *  Created on: 18 Feb 2022
 *      Author: Matthew Boote
 */

#include <string>
#include <sstream>

#ifndef MESSAGE_USER_INTERFACE_H_
#define MESSAGE_USER_INTERFACE_H_

#define MESSAGE_VECTOR_ID	 0
#define MESSAGE_VECTOR_SENDER	 1
#define MESSAGE_VECTOR_SUBJECT	 2
#define MESSAGE_VECTOR_TIME_DATE 3
#define MESSAGE_VECTOR_MESSAGE   4

class Message {
 private:

 public:
 Message();
 bool CheckForMessages(std::string username);
 bool MessageInterface(std::string username);
 bool SendMessageInternal(std::string sender,std::string recipient,std::string subject,std::string message);
 bool SendMessage(std::string sender,std::string recipient,std::string subject,std::string message);
 bool SendMessageInterface(std::string sender);

};
#endif
