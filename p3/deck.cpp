//
// Created by junsi on 2021/7/4.
//

#include "deck.h"
#include <iostream>
using namespace std;

Deck::Deck() {
    next=0;
    int pos=0;
    for (Suit i = SPADES; i <=DIAMONDS ; i= static_cast<Suit>(i + 1)) {
        for (Spot j = TWO; j <=ACE ; j= static_cast<Spot>(j+1)) {
            deck[pos].suit=i;
            deck[pos].spot=j;
            pos++;
        }
    }
}

void Deck::reset() {
    next=0;
    int pos=0;
    for (Suit i = SPADES; i <=DIAMONDS ; i= static_cast<Suit>(i + 1)) {
        for (Spot j = TWO; j <=ACE ; j= static_cast<Spot>(j+1)) {
            deck[pos].suit=i;
            deck[pos].spot=j;
            pos++;
        }
    }
}

void Deck::shuffle(int n) {
    next=0;
    Card leftDec[n],rightDec[DeckSize-n];
    int pos=0;
    for (int j = 0; j <n ; ++j) {
        leftDec[j]=deck[j];
    }
    for (int k = n; k <DeckSize ; ++k) {
        rightDec[k-n]=deck[k];
    }
    if (2*n>DeckSize){
        for (int i = 0; i <DeckSize-n ; ++i) {
            deck[pos]=rightDec[i];
            pos++;
            deck[pos]=leftDec[i];
            pos++;
        }
        for (int j = DeckSize-n; j <n ; ++j) {
            deck[pos]=leftDec[j];
            pos++;
        }
    }else {
        for (int i = 0; i <n ; ++i) {
            deck[pos]=rightDec[i];
            pos++;
            deck[pos]=leftDec[i];
            pos++;
        }
        for (int j = n; j <DeckSize-n ; ++j) {
            deck[pos]=rightDec[j];
            pos++;
        }
    }
}

Card Deck::deal() {
    Card ans=deck[next];
    next++;
    if (next>DeckSize){
        throw DeckEmpty{};
    }else{
        return ans;
    }
}

int Deck::cardsLeft() {
    return DeckSize-next;
}

