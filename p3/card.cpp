#include "card.h"
#include <iostream>
using namespace std;

const string SuitNames[] = {"Spades", "Hearts", "Clubs", "Diamonds"};

const string SpotNames[] = {"Two", "Three", "Four", "Five", "Six", 
                           "Seven", "Eight", "Nine", "Ten", "Jack", 
                           "Queen", "King", "Ace"};
const string SOS_Name[5] = { "Suzumiya Haruhi","Nagato Yuki","Asahina Mikuru","Kyon","Koizumi Itzuki" };
const string SC_Name[5] = { "Joseph Joestar","Kujo Jotaro","Jean Pierre Polnareff","Kakyoin Noriaki","Mohammed Avdol" };
/*
void displayCard(Card card)
{
    cout << SpotNames[card.spot] << " of " << SuitNames[card.suit]
        << flush;
}
*/
//int main(){
//    Card deck[52];
//    int pos=0;
//    for (Suit i = SPADES; i <=DIAMONDS ; i= static_cast<Suit>(i + 1)) {
//        for (Spot j = TWO; j <=ACE ; j= static_cast<Spot>(j+1)) {
//            deck[pos].suit=i;
//            deck[pos].spot=j;
//            pos++;
//        }
//    }
//    cout<<TWO<<endl;
//    cout<<deck[1].spot<<endl;
//}