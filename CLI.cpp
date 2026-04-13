//test game loop 
#include "battle.h"
//[atk, def, matk, mdef, spd, hp]

using namespace std;

void menu(){
    cout << "0) quit, ";
    //cout << "1) check creature status, ";
    //cout << "2) check creature 2 status, ";
    cout << "3) check initialization, ";
    //cout << "4) add 100xp to c2, ";
    cout << "5) test battle, ";
    cout << "6) team editor" << endl;
}


int main(){
    int squad_opt;
    int opt3; //just declare variables wherever bro, f*** you i hate your code
    vector<creature_instance> current_team;
    cout << "loading moves" << endl;
    // init
    Load_Moveset("mosse.txt", global_moveset);
    cout << "Loaded " << global_moveset.size() << " moves" << endl;
    cout << "loading creatures" << endl;
    vector<creature> testvec = Load_Creatures("dict.txt");
    cout << "Loaded " << testvec.size() << " creatures" << endl;
    cout << "loading team1" << endl;
    vector<creature_instance> Team1 = Load_squad("squad.txt", testvec);
    cout << "Loaded " << Team1.size() << " members in Team1" << endl;
    vector<creature_instance> Team2 = Load_squad("squadEnv.txt", testvec);
    cout << "Loaded " << Team2.size() << " members in Team2" << endl;

    int opt;
    int opt2;
    do
    {
        menu();
        cin >> opt;
        /*
        if (opt == 1){
            cout << "Creature Status:" << endl
            << "Name: " << cerbiatto_instance.name << endl
            << "Level: " << cerbiatto_instance.lvl << endl
            << "HP: " << cerbiatto_instance.hp << "/" << cerbiatto_instance.hpmax << endl
            << "Mana: " << cerbiatto_instance.mana << endl
            << "XP: " << cerbiatto_instance.xp << "/" << cerbiatto_instance.xp_treshold << endl
            << "Stats: " << endl
            << "atk: " << cerbiatto_instance.stats[0] << endl
            << "def: " << cerbiatto_instance.stats[1] << endl
            << "matk: " << cerbiatto_instance.stats[2] << endl
            << "mdef: " << cerbiatto_instance.stats[3] << endl
            << "spd: " << cerbiatto_instance.stats[4] << endl;
            //print moveset
            cout << "Moveset: " << endl;
            for (int i = 0; i < cerbiatto_instance.moves.size(); i++){
                cout << i +1 << ") " << global_moveset[cerbiatto_instance.moves[i]].name << endl;
            }
        }
        if (opt == 2){
            cerbiatto_instance2.levelup();
            cout << "Creature Status:" << endl
                    << "Name: " << cerbiatto_instance2.name << endl
                    << "Level: " << cerbiatto_instance2.lvl << endl
                    << "HP: " << cerbiatto_instance2.hp << "/" << cerbiatto_instance2.hpmax << endl
                    << "Mana: " << cerbiatto_instance2.mana << endl
                    << "XP: " << cerbiatto_instance2.xp << "/" << cerbiatto_instance2.xp_treshold << endl
                    << "Stats: " << endl
                    << "atk: " << cerbiatto_instance2.stats[0] << endl
                    << "def: " << cerbiatto_instance2.stats[1] << endl
                    << "matk: " << cerbiatto_instance2.stats[2] << endl
                    << "mdef: " << cerbiatto_instance2.stats[3] << endl
                    << "spd: " << cerbiatto_instance2.stats[4] << endl;

            cout << "Moveset: " << endl;
            for (int i = 0; i < cerbiatto_instance2.moves.size(); i++){
                cout << i +1 << ") " << global_moveset[cerbiatto_instance2.moves[i]].name << endl;
            }
        }
        */

        if (opt == 3)
        {
            for (int i = 0; i < global_moveset.size(); i++)
            {
                cout << global_moveset[i].name << endl;
            }
        }

        if (opt == 4)
        {
            // cerbiatto_instance2.xp += 100;
        }

        if (opt == 5)
        {
            for (int i = 0; i < 100; i++){
                cout << intervalf(0.0, 1.0, globseed) << endl;
            }
        }

        if (opt == 6)
        {
            do
            {
                cout << "0) back, 1) team1, 2) team2" << endl;

                cin >> squad_opt;
                if (squad_opt == 1)
                {
                    current_team = Team1;
                }
                if (squad_opt == 2)
                {
                    current_team = Team2;
                }
                do{
                    cout << "0) back, 1) add, 2) remove, 3) list, 4) save, 5) edit member" << endl;
                    cin >> opt2;
                    if (opt2 == 1){
                        for (int i = 0; i < testvec.size(); i++)
                        {
                            cout << i + 1 << ") " << testvec[i].name << endl;
                        }
                        int choice;
                        cin >> choice;
                        choice--;
                        current_team.push_back(CreateInstance(&testvec[choice], {(interval(90, 110, globseed) / (float)100.0), (interval(90, 110, globseed) / (float)100.0), (interval(90, 110, globseed) / (float)100.0), (interval(90, 110, globseed) / (float)100.0), (interval(90, 110, globseed) / (float)100.0), (interval(90, 110, globseed) / (float)100.0)}, testvec[choice].name + "_instance"));
                    }
                    if (opt2 == 2){
                        // remove
                        for (int i = 0; i < current_team.size(); i++)
                        {
                            cout << i + 1 << ") " << current_team[i].name << endl;
                        }
                        int choice;
                        cin >> choice;
                        choice--;
                        current_team.erase(current_team.begin() + choice);
                    }
                    if (opt2 == 3){
                        for (int i = 0; i < current_team.size(); i++)
                        {
                            cout << i + 1 << ") " << current_team[i].name << endl;
                        }
                    }
                    if (opt2 == 4){
                        cout << "select file to save: " << endl;
                        string filename;
                        cin >> filename;
                        if (squad_opt == 1)
                        {
                            Savesquad(filename + ".txt", current_team);
                        }
                        if (squad_opt == 2){
                            Savesquad(filename + ".txt", current_team);
                        }
                    }
                    if (opt2 == 5){
                        creature_instance* choice;
                        for (int i = 0; i < current_team.size(); i++){
                            cout << i + 1 << ") " << current_team[i].name << endl;
                        }
                        int choice2;
                        cin >> choice2;
                        choice2--;
                        choice = &current_team[choice2];
                        do{
                            cout << "0) quit, 1) edit name, 2) add xp, 3) edit genetics, 4) edit moveset, 5)show stats" << endl;
                            cin >> opt3;
                            if (opt3 == 1){
                                cout << "Enter new name: " << endl;
                                string newname;
                                cin >> newname;
                                choice->name = newname;
                            }
                            if (opt3 == 2){
                                cout << "Enter xp to add: " << endl;
                                int xp;
                                cin >> xp;
                                choice->xp += xp;
                                choice->levelup();
                            }
                            if (opt3 == 4){
                                if (choice->moves.size() <= 3){
                                    {cout << "Current moveset: " << endl;
                                    for (int i = 0; i < choice->moves.size(); i++){
                                        cout << i + 1 << ") " << global_moveset[choice->moves[i]].name << endl;
                                    }
                                    cout << "Available moves: " << endl;
                                    cout << choice->instance_of->moveset.size() << endl;
                                    for (int i = 0; i < choice->instance_of->moveset.size(); i++)
                                    {
                                        cout << i + 1 << ") " << global_moveset[choice->instance_of->moveset[i]].name << endl;
                                    }
                                    cout << "Enter move to add: " << endl;
                                    int move_choice;
                                    cin >> move_choice;
                                    move_choice--;
                                    choice->moves.push_back(choice->instance_of->moveset[move_choice]);}
                                }
                                else{


                                    
                                    // FIX THIS


                                    cout << "select move to overwrite: " << endl;
                                    for (int i = 0; i < choice->moves.size(); i++){
                                        cout << i + 1 << ") " << global_moveset[choice->moves[i]].name << endl;
                                    }
                                    int move_choice;
                                    cin >> move_choice;
                                    move_choice--;
                                    cout << "Available moves: " << endl;
                                    for (int i = 0; i < choice->instance_of->moveset.size(); i++){
                                        cout << i + 1 << ") " << global_moveset[choice->instance_of->moveset[i]].name << endl;
                                    }
                                    cout << "Enter move to add: " << endl;
                                    int new_move_choice;
                                    cin >> new_move_choice;
                                    new_move_choice--;
                                    choice->moves[move_choice] = choice->instance_of->moveset[new_move_choice];
                                }
                                



                            }
                            if (opt3 == 5){
                                cout << "Creature Status:" << endl
                                << "Name: " << choice->name << endl
                                << "Level: " << choice->lvl << endl
                                << "HP: " << choice->hp << "/" << choice->hpmax << endl
                                << "Mana: " << choice->mana << endl
                                << "XP: " << choice->xp << "/" << choice->xp_treshold << endl
                                << "Stats: " << endl
                                << "atk: " << choice->stats[0] << endl
                                << "def: " << choice->stats[1] << endl
                                << "matk: " << choice->stats[2] << endl
                                << "mdef: " << choice->stats[3] << endl
                                << "spd: " << choice->stats[4] << endl
                                << "hpstat: " << choice->stats[5] << endl;
                                //print moveset
                                cout << "Moves: " << endl;
                                for (int i = 0; i < choice->moves.size(); i++){
                                    cout << i +1 << ") " << global_moveset[choice->moves[i]].name << endl;
                                }
                            }
                        } while (opt3 != 0);
                    }
                } while (opt2 != 0);
            } while (squad_opt!= 0);
        }
        if (opt == 0){
            if (squad_opt == 1){
                Savesquad("squad.txt", current_team);
            }
            if (squad_opt == 1){
                Savesquad("squadEnv.txt", current_team);
            }
            cout << "Exiting..." << endl;
        }
    } while (opt != 0);
    return 0;
}
