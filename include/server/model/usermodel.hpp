#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"
#include "msg.hpp"
#include <iostream>
#include <vector>

class UserModel
{
public:
    // User表的插入方法
    bool insert(User &user);

    // 根据用户号码查询用户信息
    User query(int id);

    // 更新用户的状态信息
    bool updateState(User user);

    // 重置用户的状态信息
    void resetState();

    std::vector<int> queryFansList(int userid);

    Msg queryMsg(int userid);
};

#endif // USERMODEL_H