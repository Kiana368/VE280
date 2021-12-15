#include <iostream>
#include "rand.h"
#include "player.h"
#include "deck.h"

void shuffling(Deck &decks){
    int cut;
    cout << "Shuffling the deck" << endl;
    for (int i = 0; i <7 ; ++i) {
        cut=get_cut();
        decks.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
}
int main() {
    Deck decks;
    Card curCard{};
    shuffling(decks);
 g++ -o blackjack blackjack.cpp deck.cpp hand.cpp card.cpp rand.cpp player.cpp
//    nor_bankroll=stoi(argv[1]);
//    cur_bankroll=nor_bankroll;
//    hands=stoi(argv[2]);
//    player5_type=argv[3];
//    a4=argv[4];
     cin>>nor_bankroll>>hands>>player5_type>>a4;
     cur_bankroll=nor_bankroll;




    for (int i = 0; i <10 ; ++i) {
        curCard=decks.deal();
        cout<<SpotNames[curCard.spot]<<endl;
    }
    return 0;
}
