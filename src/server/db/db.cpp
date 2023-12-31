#include "db.h"
#include <muduo/base/Logging.h>

// 数据库配置信息
static const string server = "localhost";
static const string user = "root";
static const string password = "123";
static const string dbname = "chat";

// 初始化数据库连接
MySQL::MySQL()
{
    _conn = mysql_init(nullptr);
    if (_conn == nullptr){
            cout << "mysql init error!" << endl;
            exit(1);
    }
    cout << "init mysql" << endl;
}

// 释放数据库连接资源
MySQL::~MySQL()
{
    if (_conn != nullptr) {
        mysql_close(_conn);
        cout << "close mysql" << endl;
    }
}

// 连接数据库
bool MySQL::connect()
{
    // _conn = mysql_init(nullptr);
    // if (_conn == nullptr){
    //     cout << "mysql init error!" << endl;
    //     exit(1);
    // }
    std::cout << "connect mysql..." << std::endl;
    _conn = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                  password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    cout << "connect mysql success!" << endl;
    if (_conn != nullptr)
    {
        // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL上拉下来的中文显示？
        mysql_query(_conn, "set names gbk");
    }
    else
    {
        LOG_INFO << "connect mysql failed!";
        cout << "connect mysql failed!" << endl;
    }

    return _conn == nullptr ? false : true;
}

// 更新操作
bool MySQL::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败!";
        return false;
    }

    return true;
}

// 查询操作
MYSQL_RES *MySQL::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "查询失败!";
        return nullptr;
    }
    
    return mysql_use_result(_conn);
}

// 获取连接
MYSQL* MySQL::getConnection()
{
    return _conn;
}