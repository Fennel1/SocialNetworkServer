#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

// server和client的公共头文件
enum EnMsgType
{
    LOGIN_MSG = 1000,  // 登录消息
    LOGIN_MSG_ACK,     // 登录响应消息
    LOGINOUT_MSG,      // 注销消息
    REGISTER_MSG,      // 注册消息
    REGISTER_MSG_ACK,  // 注册响应消息
    ONE_CHAT_MSG,      // 私信消息
    ADD_FRIEND_MSG,    // 关注消息
    PUBLISH_MESSAGE_MSG, //发布动态

    CREATE_GROUP_MSG,  // 创建分区
    ADD_GROUP_MSG,     // 加入分区
    GROUP_CHAT_MSG,    // 分区内容
};

enum ErrorCode
{

    PASSWORD_ERROR = 2000,
    NO_EXIST_USER,
    NO_EXIST_Group
};

#endif // __PROTOCOL_H__

// {"msgid":1,"id":13,"password":"123456"} 