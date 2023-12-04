# generate a random dataset of NFL fantasy stats
# The fantasy points are randomized for each game according to the position ranges

from faker import Faker
import random
import csv

fake = Faker()

# define the NFL teams and positions
teams = [
    "Cardinals", "Falcons", "Ravens", "Bills", "Panthers", "Bears", "Bengals", "Browns",
    "Cowboys", "Broncos", "Lions", "Packers", "Texans", "Colts", "Jaguars", "Chiefs",
    "Chargers", "Rams", "Dolphins", "Vikings", "Patriots", "Saints", "Giants", "Jets",
    "Raiders", "Eagles", "Steelers", "49ers", "Seahawks", "Buccaneers", "Titans", "Redskins"
]

positions = ["QB", "RB", "WR", "TE", "K", "DEF"]

# number of data points
num_data_points = 100000

# function to calculate points based on position and games played
def calculate_points(position, games_played):
    total_points = 0
    for _ in range(games_played):
        if position == "QB":
            points = round(random.uniform(15, 40), 2)  # QB range 15-40
        elif position == "RB":
            points = round(random.uniform(10, 30), 2)  # RB range 10-30
        elif position == "WR":
            points = round(random.uniform(5, 30), 2)   # WR range 5-30
        elif position == "TE":
            points = round(random.uniform(0, 20), 2)   # TE range 0-20
        elif position == "K":
            points = round(random.uniform(0, 15), 2)   # K range 0-15
        elif position == "DEF":
            points = round(random.uniform(0, 20), 2)   # DEF range 0-20
        total_points += points
    return total_points

# open a CSV file to write the data
with open('fantasy_football_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Player Name", "Team", "Position", "Games Played", "Total Points"])

    # generate the data
    for _ in range(num_data_points):
        first_name = fake.first_name_male()
        last_name = fake.last_name()
        name = f"{first_name} {last_name}"
        team = random.choice(teams)
        position = random.choice(positions)
        games_played = random.randint(1, 16)
        total_points = calculate_points(position, games_played)

        # write the data to the CSV file
        writer.writerow([name, team, position, games_played, total_points])
