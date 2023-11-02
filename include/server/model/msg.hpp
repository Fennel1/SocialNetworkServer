#ifndef __MSG_H__
#define __MSG_H__

#include <string>

class Msg
{
public:
    Msg(int usrid = -1, int groupid = -1, std::string text = "")
        : _userid(usrid),
          _groupid(groupid),
          _text(text)
    {}

    void setUserId(int usrid) { _userid = usrid; }
    void setGroupId(int groupid) { _groupid = groupid; }
    void setText(std::string text) { _text = text; }

    int getUsrId() { return _userid; }
    int getGroupId() { return _groupid; }
    std::string getText() { return _text; }

private:
    int _userid;
    int _groupid;
    std::string _text;
};

#endif // __GROUP_H__