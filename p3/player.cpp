//
// Created by junsi on 2021/7/4.
//

#include "player.h"
#include <iostream>
using namespace std;

//Todo: implement basic functions of Player.
string Player::getName() {
    return name;
}

int Player::getID() {
    return ID;
}

Team Player::getTeam() {
    return team;
}

void Player::setPlayer(Team tm, int id) {
    team=tm;
    ID=id;
    if (team==SOSBrigade){
        name=SOS_Name[id-1];
    }else if(team==StardustCrusaders){
        name=SC_Name[id-1];
    }
}


//Todo: implement class of Simple player
class Simple_player: public Player{
public:
    Simple_player()=default;
    Simple_player(string& playerSide, int& ID);

    virtual int bet(unsigned int bankroll,unsigned int minimum) override;

    bool draw(Card dealer, const Hand& player) override;

    void expose(Card c) override;

    void shuffled() override ;

    ~Simple_player() override =default;
};

Simple_player::Simple_player(string &playerSide, int &ID_in) {
    ID=ID_in;
    if (playerSide=="sos"){
        team=SOSBrigade;
        name=SOS_Name[ID_in-1];
    }else if(playerSide=="sc"){
        team=StardustCrusaders;
        name=SC_Name[ID_in-1];
    }
}

int Simple_player::bet(unsigned int bankroll, unsigned int minimum) {
  //  cout<<endl<<name<<" is simple player"<<endl<<endl;
    if (team==SOSBrigade && ID==1){
        return 2*minimum;
    }
    return minimum;
}

bool Simple_player::draw(Card dealer, const Hand &player) {
    HandValue current{};
    current=player.handValue();
    if (current.soft==0) {
        if (current.count <= 11) {
            return true;
        } else if (current.count == 12) {
            return !(dealer.spot == FOUR || dealer.spot == FIVE || dealer.spot == SIX);
        } else if (current.count >= 13 && current.count <= 16) {
            return !(dealer.spot == TWO || dealer.spot == THREE || dealer.spot == FOUR || dealer.spot == FIVE ||
                     dealer.spot == SIX);
        } else if (current.count >= 17) {
            return false;
        }
    }else{
        if (current.count<=17){
            return true;
        }else if(current.count==18){
            return !(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT);
        }else if(current.count>=19){
            return false;
        }
    }
    return false;
}

void Simple_player::expose(Card c) {
    return;
}

void Simple_player::shuffled() {
    return;
}


//Todo: implement the class of counting player.
class Counting_player: public Simple_player{
    int count;
public:
    Counting_player();
    Counting_player(string &playerSide, int &ID_in);

    void expose(Card c) override;

    void shuffled() override;

    int bet(unsigned int bankroll, unsigned int minimum) override;

    ~Counting_player() override = default;

};

Counting_player::Counting_player(string &playerSide, int &ID_in) {
    ID=ID_in;
    if (playerSide=="sos"){
        team=SOSBrigade;
        name=SOS_Name[ID_in-1];
    }else if(playerSide=="sc"){
        team=StardustCrusaders;
        name=SC_Name[ID_in-1];
    }
    count=0;
}

int Counting_player::bet(unsigned int bankroll, unsigned int minimum) {
  //  cout<<endl<<count<<endl<<endl;
    if (team==SOSBrigade && ID==3 ){
        if ( count<-2 && bankroll>=2*minimum){
            return 2*minimum;
        }else{
            return minimum;
        }
    }else if(team==StardustCrusaders && ID==4){
        if ( count>=4 && bankroll>=2*minimum){
            return 2*minimum;
        }else{
            return minimum;
        }
    }else if (count >= 2 && bankroll >= 2 * minimum) {
        return 2 * minimum;
    }else {
        return minimum;
    }
}

void Counting_player::expose(Card c) {
    if (c.spot==TEN || c.spot==JACK || c.spot==QUEEN || c.spot==KING || c.spot==ACE){
        count--;
    }else if(c.spot==TWO || c.spot==THREE ||c.spot==FOUR ||c.spot==FIVE || c.spot==SIX){
        count++;
    }
}

void Counting_player::shuffled() {
    count=0;
}

Counting_player::Counting_player() {
    count=0;
}

static Simple_player sp;
static Counting_player cp;

//Todo: declare static global instances of each of the Players.
// Then, implement the function to get any player
extern Player* get_Player(string& dealerSide, string& playerType, int& ID)
// EFFECTS: get a pointer to a player.
// "dealerSide" describes whether the dealer is from SOS Brigade or Stardust Crusade.
// This depends on the last program argument: [sos|sc].
// sc means the dealer team is Stardust Crusaders, sos means the dealer team is SOS Brigade.
// "playerType" describes whether Koizumi Itzuki and Mohammed Avdol are simple player or count player.
// This depends on the penultimate program argument: [simple|counting].
// If this argument is "simple", then Itzuki and Avdol are simple players.
// If this argument is "counting", then Itzuki and Avdol are countingplayers.
// "ID" is the player's ID.
{
    string playerSide;
    if (dealerSide=="sos"){
        playerSide="sc";
    }else{
        playerSide="sos";
    }
//    static Simple_player sp(playerSide, ID);
//    static Counting_player cp(playerSide,ID) ;

    if (playerSide=="sos"){
        sp.setPlayer(SOSBrigade,ID);
        cp.setPlayer(SOSBrigade,ID);
        if (ID==1){
            return &sp;
        }else if(ID==2){
            return &cp;
        }else if(ID==3){
            return &cp;
        }else if(ID==4){
            return &sp;
        }else if(ID==5){
            if (playerType=="simple"){
                return &sp;
            }else{
                return &cp;
            }
        }
    }else if (playerSide=="sc"){
        sp.setPlayer(StardustCrusaders,ID);
        cp.setPlayer(StardustCrusaders,ID);
        if (ID==1){
            return &cp;
        }else if(ID==2){
            return &cp;
        }else if(ID==3){
            return &sp;
        }else if(ID==4){
            return &cp;
        }else if(ID==5){
            if (playerType=="simple"){
                return &sp;
            }else{
                return &cp;
            }
        }
    }else{
        return nullptr;
    }
    return nullptr;
}
