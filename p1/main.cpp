#include <iostream>
#define MAX 1000000
using namespace std;

int remainder_of_power(int num, int power, int mod_num)
// EFFECTS: obtain num^power, then find the remainder of
// number^power modulo mod_num
{
    int ndigit = 1;
    int mul_ans[MAX / 10];
    mul_ans[0] = 1;
    for (int i = 0; i < power; ++i) {
        int carry = 0, temp_mul;
        // obtain num*num and store it in the reverse order in mul_ans
        for (int j = 0; j < ndigit; ++j) {
            temp_mul = num * mul_ans[j];
            mul_ans[j] = (temp_mul + carry) % 10;
            carry = (temp_mul + carry) / 10;
        }
        while (carry > 0) {
            mul_ans[ndigit] = carry % 10;
            ndigit++;
            carry = carry / 10;
        }
    }
}

bool is_armstrong_number(int num)
// REQUIRES: num>0 and num<=10000000 (we assume num < 32768)
// EFFECTS: returns true if num is Armstrong number
// false otherwise
{
    int satisfy_num=0;
    for (int p = 1; p < num ; ++p) {
        int rem_num;
        rem_num=remainder_of_power(p,num,num);
        if ( rem_num == p){
            satisfy_num++;
        }
    }
    return satisfy_num == num-1;
}
int main(){
    int b, e;
    int num;
    cin>>num;
    string str;
    while (num > 0)
    {
        str += num % 10 + '0';
        num = num / 10;
    }
    std::cout<<str.length()<<endl;
    return 0;

}