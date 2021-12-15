//
// Created by junsi on 2021/6/11.
//
#include <iostream>
#include "rand.h"
#include "bot.h"
using namespace std;

bool cmp_str(string &str1,string str2)
// EFFECTS: compare the strings
// If str1 and str2 are the same, return true. Otherwise, return false
{
    int l1=str1.size(),l2=str2.size();
    if (l1!=l2){
        return false;
    }else{
        for (int i = 0; i <l1 ; ++i) {
            if (str1[i]!=str2[i]){
                return false;
            }
        }
        return true;
    }
}

bool cmp_right(string &str)
// EFFECTS: judge if the string is the required legal command
// If satisfies, return true. Otherwise, return false
{
    return cmp_str(str, "#course") || cmp_str(str, "#instructor")|| cmp_str(str, "#stop") || cmp_str(str, "#help")|| cmp_str(str, "#time");
}


string return_before_first_symbol(string &str, char symbol)
// EFFECTS: divide the string into two parts using an input symbol as a divider
// Then, return the part before the symbol
{
    string ans;
    ans=str;
    symbol=ans.find_first_of(symbol);
    ans=ans.substr(0,symbol);
    return ans;
}

string return_after_first_symbol(string &str, char symbol)
// EFFECTS: divide the string into two parts using an input symbol as a divider
// Then, return the part after the symbol
{
    string ans;
    int symbol_pos;
    ans=str;
    symbol_pos=ans.find_first_of(symbol);
    ans=ans.substr(symbol_pos+1);
    return ans;
}


bool has_group(string &message,const Group_list& groups)
// REQUIRES: 1 <= group_count <= 2147483647
// EFFECTS: judge if the group mentioned in the message is included in the given group list
// If included, return true. Otherwise, return false
{
    string group_tbd;
    group_tbd=message;
    group_tbd=return_after_first_symbol(group_tbd,',');
    group_tbd=return_before_first_symbol(group_tbd,',');
    for (int i = 0; i <groups.group_count ; ++i) {
        if (group_tbd==groups.group_name[i]){
            return true;
        }
    }
    return false;
}

bool is_legal(string &message)
// EFFECTS: judge if the message meet all the requirement of a command, i.e. legal
// If satisfies, return true. Otherwise, return false
{
    int comma_pos,space_pos,well_pos;
    string tb_deal;
    tb_deal=message;
    comma_pos=tb_deal.find_last_of(',');
    tb_deal=tb_deal.substr(comma_pos+1);
    well_pos=tb_deal.find('#');
    space_pos=tb_deal.find(' ');
    if (well_pos!=0){
        return false;
    }
    if (space_pos<0){
        return cmp_right(tb_deal);
    }else{
        tb_deal=tb_deal.substr(0,space_pos);
        return cmp_right(tb_deal);
    }
}

void deal_illegal_command(string &mes_cp)
// EFFECTS: react to the illegal command by either repeating, admiring, or doing nothing
{
    RespChoice rand_res;
    int coin_result;
    rand_res = randomResponse();
    if (rand_res == REPEAT) {
        cout << mes_cp << endl;
    } else if (rand_res == ADMIRE) {
        coin_result = flipCoin();
        if (coin_result == 1) {
            cout << "Respect " << mes_cp << endl;
        } else {
            cout << "I really admire " << mes_cp << endl;
        }
    }
}

void return_course(string &message,Course courses)
// REQUIRES: 1 <= course_count <= 2147483647
// EFFECTS: react to the command "#course"
// If the keyword can be found, list the information of the course whose code includes the keyword in command
// If the keyword is missing or the keyword cannot be found, print out the corresponding error message
{
    string keyword;
    keyword=message;
    int symbol_pos,find=0;
    symbol_pos=keyword.find('#');
    keyword=keyword.substr(symbol_pos);
    if (keyword=="#course"){
        cout<<MISSING_KEYWORD<<endl;
    }else {
        symbol_pos=keyword.find(' ');
        keyword=keyword.substr(symbol_pos);
        symbol_pos=keyword.find_first_not_of(' ');
        if (symbol_pos<0){
            cout<<MISSING_KEYWORD<<endl;
        }else {
            keyword = keyword.substr(symbol_pos);
            for (int i = 0; i < courses.course_count; ++i) {
                string code;
                code = courses.code[i];
                if (code.find(keyword) >= 0 && code.find(keyword) <= 10) {
                    find++;
                    cout << "Course Code: " << courses.code[i] << endl;
                    cout << "Course Name: " << courses.name[i] << endl;
                    cout << "Instructor: " << courses.instructor[i] << endl;
                }
            }
            if (find == 0) {
                cout << COURSE_NOT_FOUND << endl;
            }
        }
    }
    cout<<endl;
}

void return_instructor(string &message,Course courses)
// REQUIRES: 1 <= course_count <= 2147483647
// EFFECTS: react to the command "#instructor"
// If the keyword can be found, list the information of the instructor whose name includes the keyword in command
// If the keyword is missing or the keyword cannot be found, print out the corresponding error message
{
    string keyword;
    keyword = message;
    int symbol_pos, find = 0;
    string ins_name[300];
    symbol_pos = keyword.find('#');
    keyword = keyword.substr(symbol_pos);
    if (keyword == "#instructor") {
        cout << MISSING_KEYWORD << endl;
    } else {
        symbol_pos = keyword.find(' ');
        keyword = keyword.substr(symbol_pos);
        symbol_pos=keyword.find_first_not_of(' ');
        if (symbol_pos<0){
            cout<<MISSING_KEYWORD<<endl;
        }else {
            keyword = keyword.substr(symbol_pos);
            for (int i = 0; i < courses.course_count; ++i) {
                string instructor;
                int repeat = 0;
                instructor = courses.instructor[i];
                for (int k = 0; k < find; ++k) {
                    if (instructor == ins_name[k]) {
                        repeat = 1;
                    }
                }
                if (repeat == 1) {
                    continue;
                }
                if (instructor.find(keyword) >= 0 && instructor.find(keyword) <= 100) {
                    ins_name[find] = instructor;
                    cout << "Instructor: " << instructor << endl;
                    cout << "Courses: " << courses.code[i];
                    find++;
                    for (int j = i + 1; j < courses.course_count; ++j) {
                        if (courses.instructor[j] == ins_name[find - 1]) {
                            cout << ' ' << courses.code[j];
                        }
                    }
                    cout << endl;
                }
            }
            if (find == 0) {
                cout << FACULTY_NOT_FOUND << endl;
            }
        }
    }
    cout<<endl;
}

void return_time(string &message)
// EFFECTS: print out the time in the message
{
    string time;
    time=return_before_first_symbol(message,',');
    cout<<time<<endl;
    cout<<endl;
}

bool have_admin(string &message, const Group_list& groups)
// REQUIRES: 1 <= group_count <= 2147483647
// EFFECTS: judge if the name in the message is an admin of the group mentioned in the message.
// If yes, return true. Otherwise, return false.
{
    string name, gi_mes, gi_ori;
    int comma_pos;
    comma_pos = message.find_last_of(',');
    name = message.substr(0, comma_pos);
    gi_mes = return_after_first_symbol(name, ',');
    gi_mes = return_before_first_symbol(gi_mes, ',');
    comma_pos = name.find_last_of(',');
    name = name.substr(comma_pos + 1);
    string one_group;
    int admin_num;
    string admin_name;
    for (int i = 0; i < groups.group_count; ++i) {
        one_group=groups.group_admin_name[i];
        gi_ori = groups.group_name[i];
        admin_num = groups.group_admin_num[i];
        if (gi_mes == gi_ori) {
            for (int j = 0; j < admin_num; ++j) {
                admin_name = return_before_first_symbol(one_group, ',');
                one_group = return_after_first_symbol(one_group, ',');
                if (name == admin_name) {
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

void stop_or_not(string &message, const Group_list& groups)
// EFFECTS: react to the command "#stop"
// If the name is an admin of the group mentioned in the message, print out the exit message.
// If not, pint out the fail message.
{
    int judge;
    judge=have_admin(message,groups);
    if (judge==1){
        cout << EXIT_PROMPT << endl;
    }else {
        cout << STOP_BOT_FAIL << endl;
    }
    cout<<endl;
}

void try_help(){
    cout<<HELP_TEXT<<endl;
    cout<<endl;
}

void deal_message(string& message, Course courses, const Group_list& groups)
// REQUIRES: 1 <= group_count <= 2147483647, 1 <= course_count <= 2147483647
// EFFECTS: deal with the message by reacting to all the commands.
{
    int comma_pos;
    string mes_cp;
    mes_cp=message;
    comma_pos=mes_cp.find_last_of(',');
    mes_cp=mes_cp.substr(comma_pos+1);
    if (is_legal(message)==0 ) {
        deal_illegal_command(mes_cp);
        cout<<endl;
    }else{
        if(has_group(message,groups)) {
            mes_cp=return_before_first_symbol(mes_cp,' ');
            if (mes_cp.find("#course")<100) {
                return_course(message, courses);
            }
            if (mes_cp.find("#instructor")<100 ) {
                return_instructor(message, courses);
            }
            if (mes_cp.find("#help")<100 ) {
                try_help();
            }
            if (mes_cp.find("#time")<100 ) {
                return_time(message);
            }
            if (mes_cp.find("#stop") <100) {
                stop_or_not(message, groups);
            }
        }
    }
}
