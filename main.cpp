#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include "Player.h"

using namespace std;
//center text function used in COP 3503
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int Partition(vector<Player> &v, int start, int end){

    int pivot = end;
    int j = start;
    // Go through entire vector checking pivot
    for(int i=start;i<end;++i){
        // check if Value inside vector is larger than pivot
        if(v[i].Get_Points()<v[pivot].Get_Points())
        {
            swap(v[i],v[j]);
            ++j;
        }
    }
    swap(v[j],v[pivot]);
    return j;

}

void Quicksort(vector<Player> &v, int start, int end )
{
    //Recursively sort through vector
    if(start<end){
        int p = Partition(v,start,end);
        Quicksort(v,start,p-1);
        Quicksort(v,p+1,end);
    }

}
void mergeSort(vector<Player>&left, vector<Player>& right, vector<Player>& middle)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0;
    int j = 0;
    int k = 0;

    while (j < nL && k < nR)
    {
        // Merge Middle with left
        if (left[j].Get_Points() < right[k].Get_Points())
        {
            middle[i] = left[j];
            j++;
        }
            //Merge Middle with right
        else
        {
            middle[i] = right[k];
            k++;
        }
        i++;
    }
    //Add set left to middle
    while (j < nL) {
        middle[i] = left[j];
        j++;
        i++;
    }
    //Add right to middle
    while (k < nR) {
        middle[i] = right[k];
        k++;
        i++;
    }
}

void sort(vector<Player> & middle)
{
    if (middle.size() <= 1) return;

    int mid = middle.size() / 2;
    vector<Player> left;
    vector<Player> right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(middle[j]);
    for (size_t j = 0; j < (middle.size()) - mid; j++)
        right.push_back(middle[mid + j]);

    //Recursively sort
    sort(left);
    sort(right);
    mergeSort(left, right, middle);
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
        //note: the position vectors ended up unused
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
    //creating the GUI
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
    int pick_count = 1;

    //this is the pick counter
    sf::Text count(to_string(pick_count),font,20);
    welcome.setStyle( sf::Text::Bold | sf::Text::Underlined);
    prom.setStyle( sf::Text::Bold);
    count.setStyle( sf::Text::Bold);

    //locations of titles
    setText(welcome,width/2.0f, 20);
    setText(prom,width/2.0f, 580);
    setText(count,width/2.0f, 620);
    vector<sf::Text> names_ten;
    vector<sf::Text> games_ten;
    vector<sf::Text> points_ten;
    vector<sf::Text> pos_ten;
    vector<sf::Text> teams_ten;
    //for loop to show stats
    for(int i =0; i<10; i++){
        sf::Text temp(ALL[100000-i-pick_count].Get_Name(),font,10);
        temp.setFillColor(sf::Color::Black);
        temp.setStyle( sf::Text::Bold);
        temp.setPosition(218, 43*i + 103);
        names_ten.push_back(temp);
        sf::Text temp1(ALL[100000-i-pick_count].Get_Team(),font,12);
        temp1.setFillColor(sf::Color::Black);
        temp1.setStyle( sf::Text::Bold);
        temp1.setPosition(373, 43*i + 103);
        teams_ten.push_back(temp1);
        sf::Text temp2(ALL[100000-i-pick_count].Get_Position(),font,12);
        temp2.setFillColor(sf::Color::Black);
        temp2.setStyle( sf::Text::Bold);
        temp2.setPosition(528, 43*i + 103);
        pos_ten.push_back(temp2);
        sf::Text temp3(to_string(ALL[100000-i-pick_count].Get_Points()),font,12);
        temp3.setFillColor(sf::Color::Black);
        temp3.setStyle( sf::Text::Bold);
        temp3.setPosition(683, 43*i + 103);
        points_ten.push_back(temp3);
        sf::Text temp4(to_string(ALL[100000-i-pick_count].Get_Games_Played()),font,12);
        temp4.setFillColor(sf::Color::Black);
        temp4.setStyle( sf::Text::Bold);
        temp4.setPosition(838, 43*i + 103);
        games_ten.push_back(temp4);
    }
    //for loop for the background rectangles for the middle graph
    for(int i =0; i<11; i++){
        for(int j=0; j<5;j++){
            sf::RectangleShape rec;
            rec.setSize(sf::Vector2f(150,38));
            rec.setFillColor(sf::Color::White);
            rec.setPosition(155*j + 215, 43*i + 55);
            recs.push_back(rec);
        }
    }

    //background of the graph and creation of the buttons
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

    //titles of buttons
    sf::Text p1000Text("Past 1000 Picks", font, 20);
    sf::Text p100Text("Past 100 Picks", font, 20);
    sf::Text p10Text("Past 10 Picks", font, 20);
    sf::Text p1Text("Past 1 Pick", font, 20);
    sf::Text f1000Text("Future 1000 Picks", font, 20);
    sf::Text f100Text("Future 100 Picks", font, 20);
    sf::Text f10Text("Future 10 Picks", font, 20);
    sf::Text f1Text("Future 1 Pick", font, 20);

    //text color
    p1000Text.setFillColor(sf::Color::Black);
    p100Text.setFillColor(sf::Color::Black);
    p10Text.setFillColor(sf::Color::Black);
    p1Text.setFillColor(sf::Color::Black);
    f1000Text.setFillColor(sf::Color::Black);
    f100Text.setFillColor(sf::Color::Black);
    f10Text.setFillColor(sf::Color::Black);
    f1Text.setFillColor(sf::Color::Black);

    //text location
    setText(p1000Text, p1000.getPosition().x + p1000.getSize().x / 2, p1000.getPosition().y + p1000.getSize().y / 2);
    setText(p100Text, p100.getPosition().x + p100.getSize().x / 2, p100.getPosition().y + p100.getSize().y / 2);
    setText(p10Text, p10.getPosition().x + p10.getSize().x / 2, p10.getPosition().y + p10.getSize().y / 2);
    setText(p1Text, p1.getPosition().x + p1.getSize().x / 2, p1.getPosition().y + p1.getSize().y / 2);
    setText(f1000Text, f1000.getPosition().x + f1000.getSize().x / 2, f1000.getPosition().y + f1000.getSize().y / 2);
    setText(f100Text, f100.getPosition().x + f100.getSize().x / 2, f100.getPosition().y + f100.getSize().y / 2);
    setText(f10Text, f10.getPosition().x + f10.getSize().x / 2, f10.getPosition().y + f10.getSize().y / 2);
    setText(f1Text, f1.getPosition().x + f1.getSize().x / 2, f1.getPosition().y + f1.getSize().y / 2);

    //graph titles
    sf::Text Name("Name", font, 20);
    sf::Text Team("Team", font, 20);
    sf::Text POS("Position", font, 20);
    sf::Text Points("Total Points", font, 20);
    sf::Text Games("Total Games", font, 20);

    Name.setFillColor(sf::Color::Black);
    Team.setFillColor(sf::Color::Black);
    POS.setFillColor(sf::Color::Black);
    Points.setFillColor(sf::Color::Black);
    Games.setFillColor(sf::Color::Black);
    Name.setPosition(218, 63);
    Team.setPosition(373, 63);
    POS.setPosition(528, 63);
    Points.setPosition(683, 63);
    Games.setPosition(838, 63);

    //the while loop for the window
    while(window.isOpen())
    {
        //in order to update the graph
        for(int i =0; i<10; i++){
            sf::Text temp(ALL[100000-i-pick_count].Get_Name(),font,10);
            temp.setFillColor(sf::Color::Black);
            temp.setStyle( sf::Text::Bold);
            temp.setPosition(218, 43*i + 103);
            names_ten[i]=temp;
            sf::Text temp1(ALL[100000-i-pick_count].Get_Team(),font,12);
            temp1.setFillColor(sf::Color::Black);
            temp1.setStyle( sf::Text::Bold);
            temp1.setPosition(373, 43*i + 103);
            teams_ten[i]=temp1;
            sf::Text temp2(ALL[100000-i-pick_count].Get_Position(),font,12);
            temp2.setFillColor(sf::Color::Black);
            temp2.setStyle( sf::Text::Bold);
            temp2.setPosition(528, 43*i + 103);
            pos_ten[i]=temp2;
            sf::Text temp3(to_string(ALL[100000-i-pick_count].Get_Points()),font,12);
            temp3.setFillColor(sf::Color::Black);
            temp3.setStyle( sf::Text::Bold);
            temp3.setPosition(683, 43*i + 103);
            points_ten[i]=temp3;
            sf::Text temp4(to_string(ALL[100000-i-pick_count].Get_Games_Played()),font,12);
            temp4.setFillColor(sf::Color::Black);
            temp4.setStyle( sf::Text::Bold);
            temp4.setPosition(838, 43*i + 103);
            games_ten[i]=temp4;
        }
        //in order the update the counter
        sf::Text temp(to_string(pick_count),font,20);
        temp.setStyle( sf::Text::Bold);
        setText(temp,width/2.0f, 620);
        count = temp;
        //looking for events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                //all the if statements relate to all the buttons and have maxes and minimums accordingly
                if (p1000.getGlobalBounds().contains(mousePos.x, mousePos.y) and pick_count > 1000) {

                    cout << "Past 1000 Picks button pressed." << endl;
                    pick_count-=1000;
                    sf::sleep(sf::milliseconds(500));
                }
                else if (p100.getGlobalBounds().contains(mousePos.x, mousePos.y) and pick_count > 100) {
                    cout << "Past 100 Picks button pressed." << endl;
                    pick_count-=100;
                    sf::sleep(sf::milliseconds(500));
                }
                else if (p10.getGlobalBounds().contains(mousePos.x, mousePos.y) and pick_count > 10) {
                    cout << "Past 10 Picks button pressed." << endl;
                    pick_count-=10;
                    sf::sleep(sf::milliseconds(500));
                }
                else if (p1.getGlobalBounds().contains(mousePos.x, mousePos.y) and pick_count > 1) {
                    cout << "Past 1 Picks button pressed." << endl;
                    pick_count--;
                    sf::sleep(sf::milliseconds(500));
                }
                else if (f1000.getGlobalBounds().contains(mousePos.x, mousePos.y) and pick_count<98992) {
                    cout << "Future 1000 Picks button pressed." << endl;
                    pick_count+=1000;
                    sf::sleep(sf::milliseconds(500));
                }
                else if (f100.getGlobalBounds().contains(mousePos.x, mousePos.y) and pick_count<99892) {
                    cout << "Future 100 Picks button pressed." << endl;
                    pick_count+=100;
                    sf::sleep(sf::milliseconds(500));
                }
                else if (f10.getGlobalBounds().contains(mousePos.x, mousePos.y) and pick_count<99982) {
                    cout << "Future 10 Picks button pressed." << endl;
                    pick_count+=10;
                    sf::sleep(sf::milliseconds(500));
                }
                else if (f1.getGlobalBounds().contains(mousePos.x, mousePos.y) and pick_count<99991) {
                    cout << "Future 10 Picks button pressed." << endl;
                    pick_count++;
                    sf::sleep(sf::milliseconds(500));
                }
            }
        }

        // this draws and redraws the window when neccesary
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
        window.draw(count);
        for(int i =0; i<10; i++){
            window.draw(names_ten[i]);
            window.draw(teams_ten[i]);
            window.draw(pos_ten[i]);
            window.draw(points_ten[i]);
            window.draw(games_ten[i]);
        }
        window.draw(p1000Text);
        window.draw(p100Text);
        window.draw(p10Text);
        window.draw(f1000Text);
        window.draw(f100Text);
        window.draw(f10Text);
        window.draw(f1Text);
        window.draw(p1Text);
        window.draw(Name);
        window.draw(Points);
        window.draw(POS);
        window.draw(Team);
        window.draw(Games);
        window.display();
    }

    return 0;
}
