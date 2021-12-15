//
// Created by junsi on 2021/7/4.
//

#include "hand.h"
#include <iostream>
using namespace std;


Hand::Hand() {
    HandValue temp{};
    curValue=temp;
}

void Hand::discardAll() {
    curValue.count=0;
    curValue.soft=false;
}

void Hand::addCard(Card c) {
    if (curValue.soft==0) {
        if (c.spot == ACE) {
            if (curValue.count <= 10) {
                curValue.count += 11;
                curValue.soft = true;
            } else {
                curValue.count += 1;
            }
        } else {
            if (c.spot == JACK || c.spot == QUEEN || c.spot == KING) {
                curValue.count += 10;
            } else {
                curValue.count += c.spot + 2;
            }
        }
    }else if(curValue.soft==1){
        int add_num;
        if (c.spot == JACK || c.spot == QUEEN || c.spot == KING) {
            add_num= 10;
        } else if(c.spot==ACE){
            add_num=1;
        }
        else {
            add_num= c.spot + 2;
        }
        if (curValue.count+add_num>21){
            curValue.soft=false;
            curValue.count=curValue.count+add_num-10;
        }else{
            curValue.count+=add_num;
        }
    }
}

HandValue Hand::handValue() const {
    HandValue ans{};
    ans.count=curValue.count;
    ans.soft=curValue.soft;
    return ans;
}