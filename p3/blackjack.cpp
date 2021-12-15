//
// Created by junsi on 2021/7/4.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "player.h"
#include "deck.h"
#include "rand.h"
using namespace std;
#define MINIMUM_BET 5

void shuffling(Deck &decks)
// MODIFIES: decks
// EFFECTS: shuffle the decks seven times
{
    int cut;
    cout << "Shuffling the deck" << endl;
    for (int i = 0; i <7 ; ++i) {
        cut=get_cut();
        decks.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
}

void stand_power(Hand &hand, Deck &decks, int c_num, Card &curCard, Player * player_n, bool is_player)
// MODIFIES: player_hand, decks, curCard, player_n
// EFFECTS: Kujo Jotaro use his power to stop the time, dicard the cards and then
// draw cards until the total count is less than 21.
{
    if (is_player==1){
        cout<<"Player: Kujo Jotaro: \"Star Platinum, Za Warudo\""<<endl;
    }else{
        cout<<"Dealer: Kujo Jotaro: \"Star Platinum, Za Warudo\""<<endl;
    }
    hand.discardAll();
    for (int j = 0; j <c_num ; ++j) {
        curCard=decks.deal();
        hand.addCard(curCard);
        if(is_player==1){
            player_n->expose(curCard);
          //  cout<<endl<<SpotNames[curCard.spot]<<endl<<endl;
        }
    }
}

bool escape(unsigned int cur_bankroll, unsigned int nor_bankroll, Team &player_team, int &player_ID)
// EFFECTS: if Joseph Joestar decide to escape, return true. Otherwise, return false.
{
    return player_team == StardustCrusaders && player_ID == 1 &&  cur_bankroll < nor_bankroll/2;
}

void cheer(const string& type,Team &team, int &ID)
// EFFECTS: if the winner is Joseph Joestar or Kakyoin Noriaki, print what they are going to say.
{
    if (team==StardustCrusaders && ID==1){
        cout<<type<<": Joseph Joestar: \"Nice!\""<<endl;
    }else if(team==StardustCrusaders && ID==4){
        cout<<type<<": Kakyoin Noriaki: \"rerorerorero rerorerorero\""<<endl;
    }else{
        return;
    }
}

void player_addCard(Card &curCard, Deck &decks, int &pc_num, Hand &player_hand)
// MODIFIES: curCard, decks, pc_num, player_hand
// EFFECTS: add one card to player_hand and modify related variables
{
    curCard = decks.deal();
    player_hand.addCard(curCard);
    pc_num++;
}

void dealer_addCard(Card &curCard, Deck &decks, int &dc_num, Hand &dealer_hand)
// MODIFIES: curCard, decks, dc_num, dealer_hand
// EFFECTS: add one card to dealer_hand and modify related variables
{
    curCard = decks.deal();
    dealer_hand.addCard(curCard);
    dc_num++;
}

void announce_expose(Player *player_n,Card &curCard, string &player_name)
// MODIFIES: player_hand
// EFFECTS: expose the curCard to the player and announce
{
    player_n->expose(curCard);
    cout << "Player: " << player_name << " dealt " << SpotNames[curCard.spot] << " of "
         << SuitNames[curCard.suit] << endl;
}

int main(int argc, char *argv[]){
    int hands;
    int nor_bankroll,cur_bankroll, save_bankroll;
    string player5_type,a4;
    Team dealer_team, player_team;

    nor_bankroll=stoi(argv[1]);
    cur_bankroll=nor_bankroll;
    hands=stoi(argv[2]);
    player5_type=argv[3];
    a4=argv[4];
    if (a4=="sc"){
        dealer_team=StardustCrusaders;
        player_team=SOSBrigade;
    }else {
        dealer_team=SOSBrigade;
        player_team=StardustCrusaders;
    }

    string player_name,dealer_name;
    int player_ID=1,dealer_ID=1,pc_num=0,dc_num=0;
    int wager;
    Player* player_n=get_Player(a4, player5_type, player_ID);
    Hand player_hand,dealer_hand;
    Card curCard{}, holeCard{}, dealerCard{};
    if (player_team==SOSBrigade){
        player_name=SOS_Name[0];
        dealer_name=SC_Name[0];
    }else{
        player_name=SC_Name[0];
        dealer_name=SOS_Name[0];
    }
    if (a4=="sos" && player_ID==1){
        cur_bankroll=2*nor_bankroll;
    }

    Deck decks;
    int thishand;
    save_bankroll=cur_bankroll;
    //Todo: run a whole game (several rounds until one team is kicked out)
    while (true){
        shuffling(decks);
        player_n->shuffled();
        //Todo: one round (several hands)
        for (thishand = 1; thishand <=hands ; ++thishand) {
            try {
                if (save_bankroll<MINIMUM_BET && thishand==1){
                    break;
                }
                if (escape(cur_bankroll,nor_bankroll,player_team,player_ID)==1){
                    thishand--;
                    break;
                }
                cout << "Hand " << thishand << " bankroll " << cur_bankroll << endl;

                if (decks.cardsLeft() < 20) {
                    shuffling(decks);
                    player_n->shuffled();
                }

                wager = player_n->bet(cur_bankroll, MINIMUM_BET);
                cout << "Player: " << player_name << " bets " << wager << endl;

                //TODO: deal four cards
                player_addCard(curCard,decks,pc_num,player_hand);
                announce_expose(player_n,curCard,player_name);
                dealer_addCard(curCard,decks,dc_num,dealer_hand);
                player_n->expose(curCard);
                dealerCard=curCard;
                cout << "Dealer: " << dealer_name << " dealt " << SpotNames[curCard.spot] << " of "
                     << SuitNames[curCard.suit] << endl;
                player_addCard(curCard,decks,pc_num,player_hand);
                announce_expose(player_n,curCard,player_name);
                dealer_addCard(curCard,decks,dc_num,dealer_hand);
                holeCard = curCard;


                //TODO: judge if natural 21
                if (player_hand.handValue().count == 21 && player_hand.handValue().soft == 1) {
                    cur_bankroll +=  wager * 3 / 2;
                    cout << "Player: " << player_name << " dealt natural 21" << endl;
                    player_hand.discardAll(); pc_num=0;
                    dealer_hand.discardAll(); dc_num=0;
                    continue;
                }

                //TODO: player draw until stand or bust
                bool do_draw = player_n->draw(dealerCard, player_hand);
                while (do_draw == 1) {
                    player_addCard(curCard, decks, pc_num, player_hand);
                    player_n->expose(curCard);
                  //  cout<<endl<<SpotNames[curCard.spot]<<endl<<endl;
                    if (player_team == StardustCrusaders && player_ID == 2) {
                        while (player_hand.handValue().count > 21) {
                            stand_power(player_hand, decks, pc_num, curCard, player_n, true);
                          //  player_n->bet(cur_bankroll,MINIMUM_BET);
                        }
                    }
                    cout << "Player: " << player_name << " dealt " << SpotNames[curCard.spot] << " of "
                         << SuitNames[curCard.suit] << endl;
                    do_draw = player_n->draw(dealerCard, player_hand);
                    if (player_hand.handValue().count > 21) {
                        break;
                    }
                }
                cout << "Player: " << player_name << "'s total is " << player_hand.handValue().count << endl;
                if (player_hand.handValue().count > 21) {
                    cout << "Player: " << player_name << " busts" << endl;
                    cur_bankroll -= wager;
                    player_hand.discardAll(); pc_num=0;
                    dealer_hand.discardAll(); dc_num=0;
                    if (cur_bankroll < MINIMUM_BET || thishand == hands || escape(cur_bankroll,nor_bankroll,player_team,player_ID) == 1) {
                        break;
                    }
                    continue;
                }

                cout << "Dealer: " << dealer_name << "'s hole card is " << SpotNames[holeCard.spot] << " of "
                     << SuitNames[holeCard.suit] << endl;
                player_n->expose(holeCard);


                //TODO: dealer draw until reach 17 or more
                while (dealer_hand.handValue().count < 17) {
                    dealer_addCard(curCard,decks,dc_num,dealer_hand);
                    if (dealer_team == StardustCrusaders && dealer_ID == 2) {
                        while (dealer_hand.handValue().count > 21) {
                            stand_power(dealer_hand, decks, dc_num, curCard,player_n,false);
                        }
                    }
                    cout << "Dealer: " << dealer_name << " dealt " << SpotNames[curCard.spot] << " of "
                         << SuitNames[curCard.suit] << endl;
                    player_n->expose(curCard);
                }
                cout << "Dealer: " << dealer_name << "'s total is " << dealer_hand.handValue().count << endl;

                //TODO: judge according to the situation of dealer (bust or not)
                if (dealer_hand.handValue().count > 21) {
                    cout << "Dealer: " << dealer_name << " busts" << endl;
                    cur_bankroll += wager;
                    player_hand.discardAll(); pc_num=0;
                    dealer_hand.discardAll(); dc_num=0;
                   continue;
                } else {
                    if (dealer_hand.handValue().count > player_hand.handValue().count) {
                        cur_bankroll -= wager;
                        cout << "Dealer: " << dealer_name << " wins this hand" << endl;
                    } else if (dealer_hand.handValue().count < player_hand.handValue().count) {
                        cur_bankroll += wager;
                        cout << "Player: " << player_name << " wins this hand" << endl;
                    } else {
                        cout << "Push" << endl;
                    }
                }

                if (cur_bankroll >= MINIMUM_BET && thishand < hands) {
                    player_hand.discardAll(); pc_num=0;
                    dealer_hand.discardAll(); dc_num=0;
                    continue;
                } else {
                    if (cur_bankroll < MINIMUM_BET || thishand == hands || escape(cur_bankroll,nor_bankroll,player_team,player_ID) == 1) {
                        break;
                    }
                }
            }
            catch (DeckEmpty err) {
                cout << "Hand " << thishand << " card used up, this hand will start again" << endl;
                shuffling(decks);
                player_n->shuffled();
                thishand=thishand-1;
                player_hand.discardAll(); pc_num=0;
                dealer_hand.discardAll(); dc_num=0;
            }
        }
        //Todo: kick out one member
        if (thishand>hands){
            thishand=hands;
        }else if ( save_bankroll<MINIMUM_BET && thishand==1 ){
            thishand=0;
        }
        cout << "Player: " << player_name << " has " << cur_bankroll << " after " << thishand << " hands"
             << endl;
        if (thishand>=hands && cur_bankroll>=MINIMUM_BET && escape(cur_bankroll,nor_bankroll,player_team,player_ID)==0){
            cout << "Dealer: " << dealer_name << " has been kicked out. The winner of this round is "<<
                 player_name <<"." << endl;
            cheer( "Player", player_team, player_ID);
            dealer_ID++;
            if (dealer_ID==6){
                break;
            }
            dealer_hand.discardAll(); dc_num=0;
            player_hand.discardAll(); pc_num=0;
            if (dealer_team==StardustCrusaders){
                dealer_name=SC_Name[dealer_ID-1];
            }else{
                dealer_name=SOS_Name[dealer_ID-1];
            }
        }else {
            if (escape(cur_bankroll,nor_bankroll,player_team,player_ID)==1){
                cout<<"Player: Joseph Joestar: \"Ni Ge Run Da Yo\""<<endl;
            }
            cout << "Player: " << player_name << " has been kicked out. The winner of this round is "<<
                 dealer_name <<"." << endl;
            cheer( "Dealer", dealer_team, dealer_ID);
            player_ID++;
            if (player_ID==6){
                break;
            }
            player_hand.discardAll(); pc_num=0;
            dealer_hand.discardAll(); dc_num=0;
            player_n=get_Player(a4,player5_type,player_ID);
            cur_bankroll=nor_bankroll;
            save_bankroll=cur_bankroll;
            if (player_team==StardustCrusaders){
                player_name=SC_Name[player_ID-1];
            }else{
                player_name=SOS_Name[player_ID-1];
            }
        }
    }
    if ((player_ID==6 && player_team==SOSBrigade) || (dealer_ID==6 && dealer_team==SOSBrigade)) {
        cout <<"Game over. The winner is Stardust Crusaders. SOS Brigade will return the computer "
                "to Joseph Joestar and Suzumiya Haruhi will become a member of Stardust Crusaders" << endl;
    }else if((player_ID==6 && player_team==StardustCrusaders) || (dealer_ID==6 && dealer_team==StardustCrusaders)){
        cout<<"Game over. The winner is SOS Brigade. SOS Brigade got four computers and Stardust "
              "Crusaders become an affiliate group of SOS Brigade"<<endl;
    }
}
