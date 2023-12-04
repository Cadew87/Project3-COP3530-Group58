#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;
int Partition(vector<Player> &v, int start, int end){

    int pivot = end;
    int j = start;
    for(int i=start;i<end;++i){
        if(v[i].Get_Points()<v[pivot].Get_Points())
        {
            swap(v[i],v[j]);
            ++j;
        }
    }
    swap(v[j],v[pivot]);
    return j;

}

void Quicksort(vector<Player> &v, int start, int end ){

    if(start<end){
        int p = Partition(v,start,end);
        Quicksort(v,start,p-1);
        Quicksort(v,p+1,end);
    }

}
void mergeSort(vector<Player>&left, vector<Player>& right, vector<Player>& bars)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR)
    {
        if (left[j].Get_Points() < right[k].Get_Points())
        {
            bars[i] = left[j];
            j++;
        }
        else
        {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}

void sort(vector<Player> & bar)
{
    if (bar.size() <= 1) return;

    int mid = bar.size() / 2;
    vector<Player> left;
    vector<Player> right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    sort(left);
    sort(right);
    mergeSort(left, right, bar);
}

int main() {
    //accessing the csv file with player info
    ifstream player_file;
    player_file.open("fantasy_football_data.csv");
    //this will be used to look at each line of the csv
    string line;
    //vectors of players seperated into their positions
    vector<Player> QBs;
    vector<Player> WRs;
    vector<Player> RBs;
    vector<Player> TEs;
    vector<Player> Ks;
    vector<Player> DEFs;

    //this while loop is accessing the csv line by line until there are no more lines
    while (getline(player_file, line)) {
        //this accesses the next line
        stringstream current(line);
        //variables; note: temp is used for variables that are not strings.
        string name;
        string pos;
        string team;
        int gp;
        float points;
        string temp;

        //name is the first value in the csv
        getline(current, name, ',');
        //team is the second value in the csv
        getline(current, team, ',');
        //position is the third value in the csv
        getline(current, pos, ',');
        //games played is the fourth value in the csv, and it must be converted to int
        getline(current, temp, ',');
        gp = atoi(temp.c_str());
        //games played is the fourth value in the csv, and it must be converted to float
        getline(current, temp);
        points = atof(temp.c_str());

        //this creates the player in the class
        Player player(name, pos, team, gp, points);

        //these if statements choose the vector the player goes to
        if (player.Get_Position() == "QB")
        {
            QBs.push_back(player);
        }
        if (player.Get_Position() == "WR")
        {
            WRs.push_back(player);
        }
        if (player.Get_Position() == "RB")
        {
            RBs.push_back(player);
        }
        if (player.Get_Position() == "K")
        {
            Ks.push_back(player);
        }
        if (player.Get_Position() == "DEF")
        {
            DEFs.push_back(player);
        }
        if (player.Get_Position() == "TE")
        {
            TEs.push_back(player);
        }
    }

    //Call sort for MergeSort
    sort(QBs);
    //Call Quicksort for Quicksort
    Quicksort(QBs, 0, Qbs.size() - 1)
    
    return 0;
}

