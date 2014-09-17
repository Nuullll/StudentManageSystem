// token.cpp

#include "token.h"
#include <iostream>

User* Token::auth(const std::vector<User*> users)
{
	std::vector<User*>::const_iterator it;
	for (it = users.begin(); it != users.end(); it++)
	{
		if ((**it).id_ == id_)
		{
			if ((**it).password_ == password_)
				return *it;
			else
				return NULL; 		// Invalid password.
		}
	}
	return NULL;		// User does not exist.
}