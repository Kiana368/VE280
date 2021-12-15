#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#define MAX 10000000

// VE280 project 1
// created by Tao Sijun (519021910906)

// FUNCTION: obtain the number and type from the command line
// then judge whether the number satisfies the type
// returns true if satisfies
// false otherwise

void print_prompt()
    // EFFECTS: print out the prompt for the required input
{
    std::cout << "Please enter the integer and the test number: ";
}

int remainder_of_power(int num, int power)
    // EFFECTS: return the remainder of num^power modulo num
{
    int remainder = 1;
    int i = 1;
    while (i<=power){
        remainder = (remainder * num) % power;
        i++;
    }
    return remainder;
}

bool is_armstrong_number(int num)
    // REQUIRES: num>0 and num<=10000000 (we assume num < 32768)
    // EFFECTS: returns true if num is Armstrong number
    // false otherwise
{
    for (int p = 1; p < num ; ++p) {
        if ( remainder_of_power(p,num) != p){
            return false;
        }
    }
    return true;
}

bool is_cyclone_jet(int num)
    // REQUIRES: num>0 and num<=10000000
    // EFFECTS: returns true if num is Cyclone Jet
    // false otherwise
{
    int char_num[100];
    int digit = 0, digit_num, not_satisfy = 0;
    while (num > 0){
        digit_num = num-(num/10)*10;
        char_num[digit] = digit_num;
        num = num/10;
        digit++;
    }
    for (int i = 0; i < digit/2; ++i) {
        if (char_num[i] != char_num[digit-i-1]){
            not_satisfy++;
            break;
        }
    }
    return not_satisfy == 0;
}

bool is_black_premium_car_number(int num)
    // REQUIRES: num>0 and num<=10000000
    // EFFECTS: returns true if num is Black Premium Car number
    // false otherwise
{
    float x;
    x = (sqrt(24*num+1)+1)/6;
    return (int) x == x;
}

bool is_auspicious_number(int num)
    // REQUIRES: num>0 and num<=10000000
    // EFFECTS: returns true if num is Auspicious number
    // false otherwise
{
    int divisor[num], divisor_num=0, sum=0;
    for (int i = 1; i < num ; ++i) {
        if (num % i == 0){
            divisor[divisor_num] = i;
            divisor_num++;
        }
    }
    for (int j = 0; j < divisor_num ; ++j) {
        sum = sum + divisor[j];
    }
    return sum > num;
}

int main()
    // this program can take a number and the type as the input
    // and return 1 if the number satisfies the type
{
    int number = 0, type = 0;
    while (number <=0 | number > 1e7 | type <= 0 | type > 4){
        print_prompt();
        std::cin >> number;
        std::cin >> type;
    }
    if (type == 1){
        std::cout << is_armstrong_number(number);
    }else if (type == 2){
        std::cout << is_cyclone_jet(number);
    }else if (type == 3){
        std::cout << is_black_premium_car_number(number);
    }else {
        std::cout << is_auspicious_number(number);
    }
    return 0;
}
