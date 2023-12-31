#include "usermodel.hpp"
#include "msg.hpp"
#include "db.h"


bool UserModel::insert(User& user)
{
    // 组装sql语句
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql), "insert into user(name, password, state) values('%s', '%s', '%s')",
        user.getName().c_str(), user.getPassword().c_str(), user.getState().c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }

    return false;
}

// 根据用户号码查询用户信息
User UserModel::query(int id)
{
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql), "select * from user where id = %d", id);

    cout << sql << endl;

    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                // 生成一个User对象，填入信息
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPassword(row[2]);
                user.setState(row[3]);
                mysql_free_result(res);
                cout << "user id = " << user.getId() << " name = " << user.getName() << endl;
                return user;
            }
        }
    }

    cout << "query failed!" << endl;

    // 返回空User
    return User();
}

bool UserModel::updateState(User user)
{
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql), "update user set state = '%s' where id = %d", user.getState().c_str(), user.getId());

    cout << sql << endl;

    MySQL mysql;
    if (mysql.connect())
    {
        cout << "connect" << endl;
        if (mysql.update(sql))
        {
            cout << "update" << endl;
            return true;
        }
    }
    return false;
}

// 重置用户的状态信息
void UserModel::resetState()
{
    // 1.组装sql语句
    char sql[1024] = "update user set state = 'offline' where state = 'online'";

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

vector<int> UserModel::queryFansList(int userid){
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql), "select userid from friend where friendid = %d", userid);

    MySQL mysql;
    vector<int> vec;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                vec.push_back(atoi(row[0]));
            }
        }
    }
    return vec;
}

Msg UserModel::queryMsg(int userid){
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql), "select userid, groupid, message from allmessage where userid != %d ORDER BY RAND() LIMIT 1", userid);

    MySQL mysql;
    Msg msg;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                msg.setUserId(atoi(row[0]));
                msg.setGroupId(atoi(row[1]));
                msg.setText(row[2]);
            }
        }
    }
    return msg;
}