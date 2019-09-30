// Mirrors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>

constexpr int Width = 10;
constexpr int Height = 10;

const char Map[Height][1 + Width] =
{
    "##########",
    "#P.......#",
    "#........#",
    "#........#",
    "#........#",
    "#........#",
    "#........#",
    "#........#",
    "#........#",
    "#######.##",
};

enum Dir
{
    North, 
    South,
    East,
    West
};

int MoveCost(int x, int y, Dir dir)
{
    if (Map[x][y] == '.')
    {
        // Is this an exit?
        if (0 == x || 0 == y || Width - 1 == x || Height - 1 == y)
        {
            return 0; // reached an exit
        }
    }

    int cost = INT_MAX;
    switch (dir)
    {
    case North:
        y = y - 1;
        if (Map[x][y] == '.')
        {
            cost = std::min(cost, MoveCost(x, y, East));
            cost = std::min(cost, MoveCost(x, y, West));
            if (cost != INT_MAX) ++cost; // Changed direction
            cost = std::min(cost, MoveCost(x, y, North));
        }
        break;
    case South:
        y = y + 1;
        if (Map[x][y] == '.')
        {
            cost = std::min(cost, MoveCost(x, y, East));
            cost = std::min(cost, MoveCost(x, y, West));
            if (cost != INT_MAX) ++cost; // Changed direction
            cost = std::min(cost, MoveCost(x, y, South));
        }
        break;
    case East:
        x = x + 1;
        if (Map[x][y] == '.')
        {
            cost = std::min(cost, MoveCost(x, y, North));
            cost = std::min(cost, MoveCost(x, y, South));
            if (cost != INT_MAX) ++cost; // Changed direction
            cost = std::min(cost, MoveCost(x, y, East));
        }
        break;
    case West:
        x = x - 1;
        if (Map[x][y] == '.')
        {
            cost = std::min(cost, MoveCost(x, y, North));
            cost = std::min(cost, MoveCost(x, y, South));
            if (cost != INT_MAX) ++cost; // Changed direction
            cost = std::min(cost, MoveCost(x, y, West));
        }
        break;
    }

    return cost;
}

int CountMirrors()
{
    // Seek to the starting point
    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
            if (Map[x][y] == 'P')
            {
                int cost = MoveCost(x, y, North);
                cost = std::min(cost, MoveCost(x, y, South));
                cost = std::min(cost, MoveCost(x, y, East));
                cost = std::min(cost, MoveCost(x, y, West));

                return cost;
            }
        }
    }

    return INT_MAX;
}

int main()
{
    int result = CountMirrors();
    std::cout << "Num Mirrors: " << result << std::endl;
    return result;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
