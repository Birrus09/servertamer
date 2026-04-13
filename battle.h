
//not implemented yet


#include <ctime>
#include "Tamer.h"

void apply_move(Puppa values){
    if(values.mossa.types[0]){
        if(values.mossa.types[3]){
            values.target.hp += values.mossa.power * values.applier.stats[0] / 100;
        }
        else{
            values.target.hp -= values.mossa.power * values.applier.stats[0] / values.target.stats[1];
        }
    }

    if(values.mossa.types[1]){
        if(values.mossa.types[3]){
            values.target.hp += values.mossa.power * values.applier.stats[2] / 100;
        }
        else{
            values.target.hp -= values.mossa.power * values.applier.stats[2] / values.target.stats[3];
        }
    }

    if(values.mossa.types[2]){
        for (int i = 0; i < values.mossa.effects.size(); i++)
            values.target.status.push_back(values.mossa.effects[i]);
    }
}




int battle(team team1, team team2, team total){
    int outcome = 0;
    int currentturn = 0;
    unsigned int BattleTimer = 0;
    bool IsAlive[6] = {1, 1, 1, 1, 1, 1};
    // 1     2       3
    //
    //    4      5       6

    //set initial timers
    for (int i = 0; i<total.members.size(); i++){
        total.members[i].set_timer();
    }


    // main cycle
    while(true){
        BattleTimer++;

    // update timers
        for (int i = 0; i<total.members.size(); i++){
            total.members[i].timer--;
        }

        // take turns
        for (int i = 0; i<team1.members.size(); i++){
            if (team1.members[i].timer == 0){
                currentturn = i+1;
                apply_move(team1.members[i].taketurn(total));
                for (int j = 0; j < total.members.size(); j++){
                    if (total.members[j].hp < 0){
                        IsAlive[j] = 0;
                        total.members[j].hp = 0;
                    }
                }
            }
        }
        for (int i = 0; i<team2.members.size(); i++){
            if (team2.members[i].timer == 0){
                currentturn = i+1;
                apply_move(team2.members[i].AItaketurn(total, time(NULL)));
                for (int j = 0; j < total.members.size(); j++){
                    if (total.members[j].hp < 0){
                        IsAlive[j] = 0;
                        total.members[j].hp = 0;
                    }
                }
            }
        }
        
        if (IsAlive[0] == 0 && IsAlive[1] == 0 && IsAlive[2] == 0){
            outcome = 2;
            break;
        }
        if (IsAlive[3] == 0 && IsAlive[4] == 0 && IsAlive[5] == 0){
            outcome = 1;
            break;
        }
    }

    //return 1 if team1 wins, 2 if team2 wins
    return outcome;
}
