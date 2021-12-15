
#include "bot.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "constants.h"
#include "rand.h"

using namespace std;
#define INTMAX 2147483647
#define INTMIN -2147483648



bool check_is_number(string &str)
// EFFECTS: check if the string can be transferred to a number
// If can, return true. Otherwise, return false
{
    string str_cp;
    str_cp=str;
    int if_num=str_cp[1]-'0';
    if(str_cp[0]=='-'){
        if(if_num>=1 && if_num<=9){
            return true;
        }
        return false;
    }
    if_num=str_cp[0]-'0';
    if(if_num>=1 && if_num<=9){
        return true;
    }
    return false;
}


int main(int argc, char* argv[]) {

    // TODO: dealing the errors that may occurs in argument input
    // ensure no argument missing
    if (argc != 4) {
        cout << MISSING_ARGUMENT_MESSAGE << endl;
        return 0;
    } else {
        string a3;
        a3 = argv[3];
        // ensure the input random seed is a number
        if (check_is_number(a3) == 0) {
            cout << INVALID_ARGUMENT_MESSAGE << endl;
            return 0;
        }
        // ensure the random seed does not exceed the range of integer
        if (stol(a3) > INT_MAX || stol(a3) < INT_MIN) {
            cout << OUT_OF_RANGE_MESSAGE << endl;
            return 0;
        }

        string course_data_file, group_list_file;
        int random_seed;
        istringstream isNum;
        course_data_file = argv[1];
        group_list_file = argv[2];

//        isNum.str(argv[3]);
//        if (!(isNum >> random_seed)) {
//            // ensure the random seed does not exceed the range of integer
//            if (random_seed == INTMAX || random_seed == INTMIN) {
//                cout << OUT_OF_RANGE_MESSAGE << endl;
//                return 0;
//            } else {
//                // ensure the input random seed is a number
//                cout << INVALID_ARGUMENT_MESSAGE << endl;
//                return 0;
//            }
//        }


        // Todo: implement 1. load the course data file
        // courses information are stored in struct [courses]
        // the number of courses is stored in [courses.course_count]
        // the codes of courses can be accessed by [courses.code]
        // the names of courses can be accessed by [courses.name]
        // the instructors of courses can be accessed by [courses.instructor]
        ifstream c_data;
        string c_line;
        Course courses;
        int ci = 0;
        c_data.open(course_data_file);
        // ensure the course_data_file can be opened
        if (!c_data) {
            cout << CANNOT_OPEN_FILE_PREFIX << course_data_file << endl;
            return 0;
        }
        getline(c_data, c_line);
        courses.course_count = stoi(c_line);
        string courses_code[courses.course_count];
        string courses_name[courses.course_count];
        string courses_instructor[courses.course_count];
        while (getline(c_data, c_line)) {
            courses_code[ci] = return_before_first_symbol(c_line, ',');
            c_line = return_after_first_symbol(c_line, ',');
            courses_name[ci] = return_before_first_symbol(c_line, ',');
            c_line = return_after_first_symbol(c_line, ',');
            courses_instructor[ci] = return_before_first_symbol(c_line, ',');
            c_line = return_after_first_symbol(c_line, ',');
            ci++;
        }
        c_data.close();
        courses.code = courses_code;
        courses.name = courses_name;
        courses.instructor = courses_instructor;


        // Todo: implement 2. load the group list from the file, then according to the file, load details for each group on the list.
        // groups admin information are stored in struct [groups]
        // the number of groups is stored in [groups.group_count]
        // the names of groups can be accessed by [groups.group_name]
        // the admin number of groups can be accessed by [groups.group_admin_num]
        // the admin names of groups can be accessed by [groups.group_admin_name]
        ifstream g_list;
        string g_line;
        Group_list groups;
        int gi = 0;
        g_list.open(group_list_file);
        // ensure the group list file can be opened
        if (!g_list) {
            cout << CANNOT_OPEN_FILE_PREFIX << group_list_file << endl;
            return 0;
        }
        getline(g_list, g_line);
        groups.address = g_line;
        groups.address.append("/");

        getline(g_list, g_line);
        groups.group_count = stoi(g_line);
        string groups_name[groups.group_count];
        int groups_admin_num[groups.group_count];
        string groups_admin_name[groups.group_count];
        while (getline(g_list, g_line)) {
            ifstream one_group;
            string spe_group_address, og_info;
            spe_group_address = groups.address + g_line;
            one_group.open(spe_group_address);
            getline(one_group, og_info);
            groups_name[gi] = g_line;
            groups_admin_num[gi] = stoi(og_info);
            while (getline(one_group, og_info)) {
                groups_admin_name[gi] += og_info;
                groups_admin_name[gi].append(",");
            }
            one_group.close();
            gi++;
        }
        g_list.close();
        groups.group_name = groups_name;
        groups.group_admin_name = groups_admin_name;
        groups.group_admin_num = groups_admin_num;

        // Todo: 3. initialize a random seed
        random_seed = stoi(a3);
        initializeWithSeed(random_seed);

        // Todo: 4. get a message from the standard input and deal with it
        // the bot will keep running until it is successfully stopped by the legal admin.
        string message, mes_cp;
        int pos, jud;
        while (true) {
            getline(cin, message);
            deal_message(message, courses, groups);
            mes_cp = message;
            pos = mes_cp.find_last_of(',');
            mes_cp = mes_cp.substr(pos + 1);
            mes_cp = return_before_first_symbol(mes_cp, ' ');
            jud = have_admin(message, groups);
            if (is_legal(message) && mes_cp == "#stop" && jud == 1) {
                break;
            }
        }
    }
}