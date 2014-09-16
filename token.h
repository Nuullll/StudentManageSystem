// token.h

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include "user.h"

class Token
{
public:
	Token() {}
	Token(int id, std::string password): id_(id), password_(password) {}
    ~Token() {}
    int id() { return id_; }
	User* auth(const std::vector<User*> users);

private:
	int id_;
	std::string password_;
};


#endif