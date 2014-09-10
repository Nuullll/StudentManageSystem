// user.cpp

#include "user.h"
#include "file.h"

void User::set_password(std::string new_password)
{
    password_ = new_password;
    UpdatePassword(id_num_, new_password);
}