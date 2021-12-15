//
// Created by junsi on 2021/6/11.
//

#ifndef P2_BOT_H
#define P2_BOT_H
#include "rand.h"
#include <string>
using namespace std;

typedef struct{
    int course_count;
    string *code;
    string *name;
    string *instructor;
} Course;

typedef struct{
    string address;
    int group_count;
    string *group_name;
    int *group_admin_num;
    string *group_admin_name;
} Group_list;

bool is_legal(string &message);
// EFFECTS: judge if the message meet all the requirement of a command, i.e. legal
// If satisfies, return true. Otherwise, return false

string return_before_first_symbol(string &str, char symbol);
// EFFECTS: divide the string into two parts using an input symbol as a divider
// Then, return the part before the symbol

string return_after_first_symbol(string &str, char symbol);
// EFFECTS: divide the string into two parts using an input symbol as a divider
// Then, return the part after the symbol

bool have_admin(string &message,const Group_list& groups);
// REQUIRES: 1 <= group_count <= 2147483647
// EFFECTS: judge if the name in the message is an admin of the group mentioned in the message.
// If yes, return true. Otherwise, return false.

void deal_message(string &message,Course courses, const Group_list& groups);
// REQUIRES: 1 <= group_count <= 2147483647, 1 <= course_count <= 2147483647
// EFFECTS: deal with the message by reacting to all the commands.

#endif //P2_BOT_H
