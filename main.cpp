#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include "Player.h"
#include "main.h"

using namespace std;

int Partition(vector<Player>& v, int start, int end) {

    int pivot = end;
    int j = start;
    for (int i = start; i < end; ++i) {
        if (v[i].Get_Points() < v[pivot].Get_Points())
        {
            swap(v[i], v[j]);
            ++j;
        }
    }
    swap(v[j], v[pivot]);
    return j;

}

void Quicksort(vector<Player>& v, int start, int end) {

    if (start < end) {
        int p = Partition(v, start, end);
        Quicksort(v, start, p - 1);
        Quicksort(v, p + 1, end);
    }

}
void mergeSort(vector<Player>& left, vector<Player>& right, vector<Player>& bars)
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

void sort(vector<Player>& bar)
{
    if (bar.size() <= 1) return;

    int mid = bar.size() / 2;
    vector<Player> left;
    vector<Player> right;

    for (size_t j = 0; j < mid; j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    sort(left);
    sort(right);
    mergeSort(left, right, bar);
}

int main() {
    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Group Elite 58: Fantasy Football Assistant");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "Failed to load font." << endl;
        return -1;
    }

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
    vector<Player> ALL, topTenPicks;

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
            mark = true;
        }
        if (player.Get_Position() == "WR")
        {
            WRs.push_back(player);
            mark = true;
        }
        if (player.Get_Position() == "RB")
        {
            RBs.push_back(player);
            mark = true;
        }
        if (player.Get_Position() == "K")
        {
            Ks.push_back(player);
            mark = true;
        }
        if (player.Get_Position() == "DEF")
        {
            DEFs.push_back(player);
            mark = true;
        }
        if (player.Get_Position() == "TE")
        {
            TEs.push_back(player);
            mark = true;
        }
        if (mark) {
            ALL.push_back(player);
        }
    }
    
        // Define table headers
        string headerTitles[] = { "Top 10 Picks", "Position", "Projected Pts", "Games Played" };
        vector<sf::Text> headers;

        // Prepare the headers
        for (const string& title : headerTitles) {
            sf::Text text(title, font, 20);
            text.setFillColor(sf::Color::White);
            headers.push_back(text);
        }

        // Create buttons
        sf::RectangleShape quickSortButton(sf::Vector2f(200, 50));
        quickSortButton.setPosition(262, 700); // Centered in window width and placed at the bottom
        quickSortButton.setFillColor(sf::Color::Green);

        sf::RectangleShape mergeSortButton(sf::Vector2f(200, 50));
        mergeSortButton.setPosition(562, 700); 
        mergeSortButton.setFillColor(sf::Color::Blue);

        // Create text for buttons
        sf::Text quickSortText("Quick Sort", font, 20);
        quickSortText.setPosition(quickSortButton.getPosition() + sf::Vector2f(10, 10)); 
        quickSortText.setFillColor(sf::Color::White);

        sf::Text mergeSortText("Merge Sort", font, 20);
        mergeSortText.setPosition(mergeSortButton.getPosition() + sf::Vector2f(10, 10)); 
        mergeSortText.setFillColor(sf::Color::White);


        // Load football image into a texture
        sf::Texture footballTexture;
        if (!footballTexture.loadFromFile("files/images/football.png")) {
            cout << "Failed to load football image." << endl;
            return -1;
        }
        // Create a sprite for the football image
        sf::Sprite footballSprite;
        footballSprite.setTexture(footballTexture);

        // Determine the new size
        float desiredWidth = 75.0f;
        float desiredHeight = 75.0f;

        // Calculate the scale factors
        float scaleX = desiredWidth / footballTexture.getSize().x;
        float scaleY = desiredHeight / footballTexture.getSize().y;

        // Set the scale of the sprite
        footballSprite.setScale(scaleX, scaleY);

        float footballMargin = 10.0f;
        footballSprite.setPosition(window.getSize().x - (footballTexture.getSize().x * scaleX) - footballMargin, footballMargin);

        // Define rectangles for layout
        sf::RectangleShape topTable(sf::Vector2f(800.0f, 300.0f));
        topTable.setPosition(50.0f, 50.0f);
        topTable.setFillColor(sf::Color(200, 200, 200));
        topTable.setOutlineThickness(1.0f);
        topTable.setOutlineColor(sf::Color::Black);

        sf::RectangleShape leftHistory(sf::Vector2f(150.0f, 150.0f));
        leftHistory.setPosition(50.0f, 400.0f);
        leftHistory.setFillColor(sf::Color(150, 150, 150));
        leftHistory.setOutlineThickness(1.0f);
        leftHistory.setOutlineColor(sf::Color::Black);

        sf::RectangleShape rightFuture(sf::Vector2f(150.0f, 150.0f));
        rightFuture.setPosition(824.0f, 400.0f);
        rightFuture.setFillColor(sf::Color(150, 150, 150));
        rightFuture.setOutlineThickness(1.0f);
        rightFuture.setOutlineColor(sf::Color::Black);


        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            bool needToSort = false;
            bool sorted = false; 

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // Check for button clicks
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        // If Quick Sort button is clicked
                        if (quickSortButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            cout << "Quick Sort button pressed" << endl;
                            Quicksort(ALL, 0, ALL.size() - 1);
                            needToSort = true;
                            sorted = true;
                        }
                        // If Merge Sort button is clicked
                        else if (mergeSortButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            cout << "Merge Sort button pressed" << endl;
                            sort(ALL);
                            needToSort = true;
                            sorted = true;
                        }
                    }
                }
            }

            if (needToSort && sorted) {
                topTenPicks.clear();
                for (size_t i = 0; i < 10 && i < ALL.size(); ++i) {
                    topTenPicks.push_back(ALL[i]);
                }
                needToSort = false;
            }

            window.clear(sf::Color::White);

            // Draw table and history/future rectangles
            window.draw(topTable);

            // Draw the football sprite in the top right corner
            window.draw(footballSprite);

            // Draw headers
            float currentX = 60.0f;
            float currentY = 60.0f; 
            for (sf::Text& header : headers) {
                header.setFillColor(sf::Color::Black);
                header.setPosition(currentX, currentY);
                window.draw(header);
                currentX += 200.0f; 
            }

            // Draw the top 10 picks
            currentY = 100.0f; 
            for (auto& player : topTenPicks) {
                sf::Text playerName(player.Get_Name(), font, 20);
                playerName.setFillColor(sf::Color::Black);
                playerName.setPosition(60.0f, currentY); 
                window.draw(playerName);

                // Displaying the player's projected points
                sf::Text playerPoints(to_string(player.Get_Points()), font, 20);
                playerPoints.setFillColor(sf::Color::Black);
                playerPoints.setPosition(260.0f, currentY); 
                window.draw(playerPoints);

                // Displaying the player's games played
                sf::Text playerGamesPlayed(to_string(player.Get_Games_Played()), font, 20);
                playerGamesPlayed.setFillColor(sf::Color::Black);
                playerGamesPlayed.setPosition(460.0f, currentY); 
                window.draw(playerGamesPlayed);

                currentY += 30.0f; 
            }


            // Draw buttons and text
            window.draw(quickSortButton);
            window.draw(mergeSortButton);
            window.draw(quickSortText);
            window.draw(mergeSortText);

            window.display();
        }

        return 0;
}

