// token.cpp

#include "token.h"
#include <iostream>

int Token::auth(const std::vector<User *> users)
{
	std::vector<User *>::const_iterator it;
	for (it = users.begin(); it != users.end(); it++)
	{
		if ((**it).id_ == id_)
		{
			if ((**it).password_ == password_)
				return (**it).identity_;
			else
				return -1; 		// Invalid password.
		}
	}
	return -2;		// User does not exist.
}