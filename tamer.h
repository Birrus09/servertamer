#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include "randomcust.h"

#define maxspd 750
#define maxstats 300
int globseed = 12345;

using namespace std;


//mosse
struct Move{
    string name;
    int power;
    int accuracy;
    bool types[4];  //0 physical, 1 magical, 2 status, 3 healing
    vector<string> effects;
    //1     2       3
    //
    //   4      5       6
};

//prototipi per la forward declaration
struct creature_instance;
struct team
{
    std::vector<creature_instance> members;
};

//serve per taketurn
struct Puppa{
    Move mossa;
    creature_instance &target;
    creature_instance &applier;
};

void Load_Moveset(string Filename, vector<Move> &moveset){
    string temp1;
    int temp2, temp3;
    bool temp4[4];

    ifstream filein(Filename);

    string firstLine;
    getline(filein, firstLine);

    while(filein >> temp1 >> temp2 >> temp3 >> temp4[0] >> temp4[1] >> temp4[2] >> temp4[3]){
        Move temp_move{
            temp1,
            temp2,
            temp3,
            {temp4[0], temp4[1], temp4[2], temp4[3]},
            {}};
        string effect;
        while(filein >> effect && effect != "end"){
            temp_move.effects.push_back(effect);
        }
        moveset.push_back(temp_move);
    }
    filein.close();
}

vector<Move> global_moveset = {};


struct creature{
    string name;
    vector<int> base_stats; // [atk, def, matk, mdef, spd, hp]
    float growth_rate;
    vector<int> moves_learning_level;
    vector<int> moveset;  //moveset index
    creature* evolution;
    int evolution_level;  
};

struct creature_instance{
    string name;
    int lvl;
    int xp;
    int xp_treshold;
    int hp;
    int hpmax;
    int mana; // x/5
    vector<int> stats; //5
    vector<float> genetics;
    vector<int> moves; //index of moveset
    vector<string> status;
    //get stats with
    creature* instance_of;
    int timer = 0;
    //int battle_position; may be useful

    void set_timer(){
        timer = maxspd - stats[4];
    }


    Puppa taketurn(team targets){

        cout << "Choose a move: " << endl;
        for (int i = 0; i < moves.size(); i++){
            cout << i+1 << ") " << global_moveset[moves[i]].name << endl;
        }
        int move_choice;
        cin >> move_choice;
        move_choice--;

        cout << "Choose a target: " << endl;
        for (int i = 0; i < targets.members.size(); i++){
            cout << i+1 << ") " << targets.members[i].name << " HP: " << targets.members[i].hp << "/" << targets.members[i].hpmax << endl;
        }
        int target_choice;
        cin >> target_choice;
        target_choice--;

        Puppa choice{
            global_moveset[moves[move_choice]],
            targets.members[target_choice],
            *this
        };
        return choice;
    }


    Puppa AItaketurn(team targets, int seed){

        Puppa choice{
            global_moveset[0],
            targets.members[randomnum(seed)*1000 / targets.members.size()],
            *this
        };
        return choice;
    }


    void updatexptreshold(){
        this->xp_treshold = pow(this->lvl, 2.7 / this->instance_of->growth_rate) * 10 + 100;
    }


    void levelup(){
        while (true){
            if (this->xp >= this->xp_treshold)
            {
                this->xp -= this->xp_treshold;
                this->lvl++;
                this->updatexptreshold();
                //update stats
                for (int i = 0; i < 5; i++){
                    //cout << "stat update check:" << i << endl;
                    // I didn't touch ABSOULTELY ANYTHING AND NOW IT WORKS
                    stats[i] += (int)(instance_of->base_stats[i] * genetics[i] * 0.054 * intervalf(0.5, 1.3, globseed));
                }
                this->hpmax += (int)(this->instance_of->base_stats[5] * this->genetics[5] * 0.06 * intervalf(0.5, 1.4, globseed));
                this->hp = this->hpmax;
                for (int i = 0; i < this->instance_of->moves_learning_level.size() && i < this->instance_of->moveset.size(); i++){
                    if (this->lvl == this->instance_of->moves_learning_level[i]){
                        this->moves.push_back(this->instance_of->moveset[i]);
                    }
                }
            }
            else{
                break;
            }
        }

    }
};


//example
//"ciao" has {wax_off, wax_on} as moves
//{wax_off, wax_on, cut} as moveset
//{0, 0, 7} as mll
//at lvl 7 it gets cut




// don't touch this
//FUCK YOU PAST ME NOW I NEED A NEW FUNCTION
creature_instance CreateInstance(creature* base, vector<float> genetics_vector, string name){
    creature_instance giveback{
        name,
        1,
        0,
        100,
        (int)(base->base_stats[5] * genetics_vector[5]),
        (int)(base->base_stats[5] * genetics_vector[5]),
        5,
        {(int)(base->base_stats[0] * genetics_vector[0]), (int)(base->base_stats[1] * genetics_vector[1]), (int)(base->base_stats[2] * genetics_vector[2]), (int)(base->base_stats[3] * genetics_vector[3]), (int)(base->base_stats[4] * genetics_vector[4])},
        genetics_vector,
        {base->moveset[0]},
        {},
        base,
        0
    };
    return giveback;
}

creature_instance CreateInitializedInstance(string name, int lvl, int xp, int xp_tresh, int hp, int hp_tresh, int mana, vector<int> stats, vector<float> gen, vector<int> moves, vector<string> status, vector<float> gen_vec, creature base){
    creature_instance giveback{
        name,
        lvl,
        xp,
        xp_tresh,
        hp,
        hp_tresh,
        mana,
        stats,
        gen_vec,
        moves,
        status,
        &base
    };
    return giveback;
}



creature_instance Evolve(creature_instance &instance){
    creature_instance evoluzione;
    // needs to be initialized
    evoluzione = CreateInstance(instance.instance_of->evolution, instance.genetics, instance.instance_of->evolution->name);
    delete(&instance);
    return evoluzione;
}



creature mr_cerbiatto{"mr_cerbiatto", {100, 100, 100, 100, 100, 100}, 1.7, {1, 5, 7, 13}, {0, 3}, nullptr, -1};
creature fleshgorger{"fleshgorger", {150, 80, 60, 95, 110, 80}, 1.5, {1, 5, 7, 13}, {0, 6}, nullptr, -1};
creature not_so_innocuous_rock{"not_so_innocuous_rock", {120, 140, 115, 98, 75, 155}, 1.2, {1, 5, 7, 13}, {0, 6}, nullptr, -1};
creature innocuous_rock{"innocuous_rock", {30, 75, 55, 90, 65, 85}, 1.9, {1, 5, 7, 13}, {0, 3, 6, 7}, &not_so_innocuous_rock, 10};
creature miaospellcaster{"spellcaster", {20, 64, 120, 105, 98, 80}, 1.6, {1, 5, 7}, {4, 5, 7}, nullptr, -1};



//genetics vector are 6 elements long

vector<creature> Load_Creatures(string filename){

    string tempname;
    vector<int> tempstats(6);
    float grt_rate;
    vector<int> tempmvlvllrnlvl;
    int tempm;
    vector<int> moveset;
    string src_evolution;
    int ev_level;


    ifstream infile(filename);
    string firstline;
    getline(infile, firstline);
    vector<creature> returnthis;

    //dynamic vectors are termitaed with -1
    while (infile >> tempname >> tempstats[0] >> tempstats[1] >> tempstats[2] >> tempstats[3]  >> tempstats[4] >> tempstats[5] >> grt_rate){
        //cout << "loading creature: " << tempname << endl;
        int i = 0;
        while (infile >> tempm){
            if(tempm < 0){
                break;
            }
            else{
                tempmvlvllrnlvl.push_back(tempm);
            }
        }

        i = 0;

        while (infile >> tempm){
            if(tempm < 0){
                break;
            }
            else{
                moveset.push_back(tempm);
            }
        }

        infile >> firstline; //discard evolution
        infile >> ev_level;

        creature tempcr{
            tempname,
            tempstats,
            grt_rate,
            tempmvlvllrnlvl,
            moveset,
            //handle evolutions later
            nullptr,
            ev_level
        };
        returnthis.push_back(tempcr);
    }

    return returnthis;
}




void Savesquad(string filename, vector<creature_instance> squad){
    ofstream fileout(filename);
    fileout << "name            lvl  xp    xp_tresh    hp    hp_max   mana   stats                        gen_vec         moves        base(name)      status" << endl;
    for (int i = 0; i < squad.size(); i++){
        fileout << squad[i].name << "\t\t" << squad[i].lvl << "\t" << squad[i].xp << " " << squad[i].xp_treshold << "\t" << squad[i].hp << " " << squad[i].hpmax << " " << squad[i].mana << "\t";
        for (int j = 0; j < 6; j++){
            fileout << squad[i].stats[j] << " ";
        }
        for (int j = 0; j < 6; j++){
            fileout << squad[i].genetics[j] << " ";
        }
        for (int j = 0; j < squad[i].moves.size(); j++){
            fileout << squad[i].moves[j] << " ";
        }
        fileout << -1 << "\t"; //moveset terminator
        fileout << squad[i].instance_of->name << "\t";
        for (int j = 0; j < squad[i].status.size(); j++){
            fileout << squad[i].status[j] << " ";
        }
        fileout << "end" << endl;
    }
}

vector<creature_instance> Load_squad(string filename, vector<creature> dict){
    vector<creature_instance> returnthis;
    ifstream infile(filename);
    string name;
    int lvl, xp, xp_tresh, hp, hp_tresh, mana;
    string basename;

    //discard first line
    string firstline;
    getline(infile, firstline);
    
    while (infile >> name >> lvl >> xp >> xp_tresh >> hp >> hp_tresh >> mana){
        creature_instance tempcr{
            name,
            lvl,
            xp,
            xp_tresh,
            hp,
            hp_tresh,
            mana,
            vector<int>(6),      // Initialize stats with 6 elements
            vector<float>(6),    // Initialize genetics with 6 elements
            {},
            {},
            nullptr
        };
        
        // Read 6 stats values
        for (int i = 0; i < 6; i++){
            infile >> tempcr.stats[i];
        }
        
        // Read 6 genetics values
        for (int i = 0; i < 6; i++){
            infile >> tempcr.genetics[i];
        }
        
        // Read moves until -1
        int temp;
        while (infile >> temp && temp != -1){
            tempcr.moves.push_back(temp);
        }
        
        // Read base creature name and find it in dict
        infile >> basename;
        for (int i = 0; i < dict.size(); i++){
            if (dict[i].name == basename){
                tempcr.instance_of = &dict[i];
                break;
            }
        }
        
        // Read status effects until "end"
        string temp2;
        while (infile >> temp2 && temp2 != "end"){
            tempcr.status.push_back(temp2);
        }
        
        returnthis.push_back(tempcr);
    }
    
    infile.close();
    return returnthis;
}

/*creature_instance cerbiatto_instance = CreateInstance(&mr_cerbiatto, {1, 1, 1, 1, 1, 1, 1}, "mr_istanza");
creature_instance cerbiatto_instance2 = CreateInstance(&mr_cerbiatto, {1.1, 0.9, 1, 1, 1.1, 1}, "mr_istanza2");
creature_instance cerbiatto_instance3 = CreateInstance(&mr_cerbiatto, {0.8, 1.3, 1, 1.3, 0.7, 1, 1}, "mr_istanza3");

creature_instance fleshgorger_instance = CreateInstance(&fleshgorger, {1, 1, 1, 1, 1, 1, 1}, "fleshgorger_istanza");
creature_instance cerbiattp_player = CreateInstance(&mr_cerbiatto, {1, 1, 1, 1, 1, 1, 1}, "Sburb_player");
creature_instance big_rock = CreateInstance(&not_so_innocuous_rock, {1, 1, 1, 1, 1, 1, 1}, "big_rock");

creature_instance megamiao = CreateInstance(&miaospellcaster, {1, 1, 1, 1, 1, 1, 1}, "miao :£");*/

//vector <creature_instance*> instance_vector_DEBUG = {&cerbiatto_instance, &cerbiatto_instance2, &cerbiatto_instance3, &fleshgorger_instance, &cerbiattp_player, &big_rock, &megamiao};
