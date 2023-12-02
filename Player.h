#include <iostream>
#include <string>

using namespace std;
//this is a class in order to put players stats in one vector
class Player{
    //player's name
    string name;
    //player's position
    string position;
    //player's team
    string team;
    //player's games played
    int gp;
    //player's points
    float points;
public:
    //contruct the player
    Player(string n, string pos, string t, int g, float p){
        name = n;
        position = pos;
        team = t;
        gp = g;
        points = p;
    }
    //get access to the name
    string Get_Name(){
        return name;
    }
    //get access to the position
    string Get_Position(){
        return position;
    }
    //get access to the team
    string Get_Team(){
        return team;
    }
    //get access to the games played
    int Get_Games_Played(){
        return gp;
    }
    //get access to the total points
    float Get_Points(){
        return points;
    }
};
