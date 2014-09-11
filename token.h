// token.h

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include "user.h"

class Token
{
public:
	Token(){};
	Token(std::string id, std::string password): id_(id), password_(password) {};
	~Token(){};
    
    std::string id() { return id_; }
	int auth(const std::vector<User *> users);

private:
	std::string id_;
	std::string password_;
};


#endif