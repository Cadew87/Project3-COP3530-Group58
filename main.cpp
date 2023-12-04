#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include "Player.h"

using namespace std;
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}
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
    vector<Player> ALL;

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
        bool mark = false;
        //these if statements choose the vector the player goes to
        if (player.Get_Position() == "QB")
        {
            QBs.push_back(player);
            mark= true;
        }
        if (player.Get_Position() == "WR")
        {
            WRs.push_back(player);
            mark= true;
        }
        if (player.Get_Position() == "RB")
        {
            RBs.push_back(player);
            mark= true;
        }
        if (player.Get_Position() == "K")
        {
            Ks.push_back(player);
            mark= true;
        }
        if (player.Get_Position() == "DEF")
        {
            DEFs.push_back(player);
            mark= true;
        }
        if (player.Get_Position() == "TE")
        {
            TEs.push_back(player);
            mark = true;
        }
        if (mark){
            ALL.push_back(player);
        }
    }
    string answer;
    cout << "Insert 1 for Merge Sort or anything else for Quick Sort: ";
    cin >> answer;
    //Call sort for MergeSort
    if (answer == "1"){
        sort(ALL);
    }
    //Call Quicksort for Quicksort
    else{
        Quicksort(ALL, 0, ALL.size() - 1);
    }

    int width = 1200;
    int height = 800;
    sf::RenderWindow window(sf::VideoMode(width, height), "Top Ten Fantasy Football Picks", sf::Style::Close);
    sf::RectangleShape shape1;
    shape1.setSize(sf::Vector2f(width,height));
    shape1.setPosition(0,0);
    shape1.setFillColor(sf::Color::Blue);
    vector<sf::RectangleShape> recs;
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text welcome("Top Ten Fantasy Football Picks",font,24);
    sf::Text prom("Pick:",font,20);

    welcome.setStyle( sf::Text::Bold | sf::Text::Underlined);
    prom.setStyle( sf::Text::Bold);

    setText(welcome,width/2.0f, 20);
    setText(prom,width/2.0f, 580);
    for(int i =0; i<11; i++){
        for(int j=0; j<5;j++){
            sf::RectangleShape rec;
            rec.setSize(sf::Vector2f(150,38));
            rec.setFillColor(sf::Color::White);
            rec.setPosition(155*j + 215, 43*i + 55);
            recs.push_back(rec);
        }
    }
    sf::RectangleShape back;
    back.setSize(sf::Vector2f(780,480));
    back.setPosition(210,50);
    back.setFillColor(sf::Color::Black);
    sf::RectangleShape p1000;
    p1000.setSize(sf::Vector2f(200,260));
    p1000.setPosition(5,5);
    p1000.setFillColor(sf::Color::White);
    sf::RectangleShape p100;
    p100.setSize(sf::Vector2f(200, 260));
    p100.setPosition(5,270);
    p100.setFillColor(sf::Color::White);
    sf::RectangleShape p10;
    p10.setSize(sf::Vector2f(200,260));
    p10.setPosition(5,535);
    p10.setFillColor(sf::Color::White);
    sf::RectangleShape f1000;
    f1000.setSize(sf::Vector2f(200,260));
    f1000.setPosition(995,5);
    f1000.setFillColor(sf::Color::White);
    sf::RectangleShape f100;
    f100.setSize(sf::Vector2f(200, 260));
    f100.setPosition(995,270);
    f100.setFillColor(sf::Color::White);
    sf::RectangleShape f10;
    f10.setSize(sf::Vector2f(200,260));
    f10.setPosition(995,535);
    f10.setFillColor(sf::Color::White);
    sf::RectangleShape p1;
    p1.setSize(sf::Vector2f(200,260));
    p1.setPosition(210,535);
    p1.setFillColor(sf::Color::White);
    sf::RectangleShape f1;
    f1.setSize(sf::Vector2f(200,260));
    f1.setPosition(790,535);
    f1.setFillColor(sf::Color::White);
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }

        }
        window.clear();
        window.draw(shape1);
        window.draw(back);
        for (int i = 0; i<recs.size(); i++){
            window.draw(recs[i]);
        }
        window.draw(p1000);
        window.draw(p100);
        window.draw(p10);
        window.draw(p1);
        window.draw(f1);
        window.draw(f1000);
        window.draw(f100);
        window.draw(f10);
        window.draw(welcome);
        window.draw(prom);
        window.display();
    }

    return 0;
}
