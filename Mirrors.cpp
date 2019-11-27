// Mirrors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Meaningless comment

#include <iostream>
#include <algorithm>

constexpr int Width = 8;
constexpr int Height = 8;
constexpr char Map[Height][1 + Width] =
{
    "########",
    "#P.....#",
    "#......#",
	"#...####",
	"#......#",
	"#......#",
	"#......#",
	"#####.##",
};

char TraceMap[Height][Width] = { 0 };

enum Dir
{
    North, 
    South,
    East,
    West
};

int ExitPathCount = 0;
int SmallestSolutionMirrorCount = INT_MAX;

int TryMove(int x, int y, Dir dir, int MirrorCount)
{
	int cost = INT_MAX;

    if (Map[x][y] != '#')
    {
        // Is this an exit?
        if (0 == x || 0 == y || Width - 1 == x || Height - 1 == y)
        {
			ExitPathCount++;
			std::cout << "Found exit path #" << ExitPathCount << " using " << MirrorCount << " mirrors!!!" << std::endl;
			SmallestSolutionMirrorCount = std::min(SmallestSolutionMirrorCount, MirrorCount);
            return 0; // reached an exit
        }

		switch (dir)
		{
		case North:
			y = y - 1;
			if (Map[x][y] == '.' && TraceMap[x][y] == 0)
			{
				TraceMap[x][y] = 1;
				cost = TryMove(x, y, North, MirrorCount);
				if (MirrorCount + 1 < SmallestSolutionMirrorCount)
				{
					int turncost = std::min(TryMove(x, y, West, MirrorCount + 1), TryMove(x, y, East, MirrorCount + 1));
					if (turncost != INT_MAX)
					{
						cost = std::min(turncost + 1, cost);
					}
				}
				TraceMap[x][y] = 0;
			}
			break;
		case South:
			y = y + 1;
			if (Map[x][y] == '.' && TraceMap[x][y] == 0)
			{
				TraceMap[x][y] = 1;
				cost = TryMove(x, y, South, MirrorCount + 1);
				if (MirrorCount + 1 < SmallestSolutionMirrorCount)
				{
					int turncost = std::min(TryMove(x, y, West, MirrorCount + 1), TryMove(x, y, East, MirrorCount + 1));
					if (turncost != INT_MAX)
					{
						cost = std::min(turncost + 1, cost);
					}
				}
				TraceMap[x][y] = 0;
			}
			break;
		case East:
			x = x + 1;
			if (Map[x][y] == '.' && TraceMap[x][y] == 0)
			{
				TraceMap[x][y] = 1;
				cost = TryMove(x, y, East, MirrorCount);
				if (MirrorCount + 1 < SmallestSolutionMirrorCount)
				{
					int turncost = std::min(TryMove(x, y, North, MirrorCount + 1), TryMove(x, y, South, MirrorCount + 1));
					if (turncost != INT_MAX)
					{
						cost = std::min(turncost + 1, cost);
					}
				}
				TraceMap[x][y] = 0;
			}
			break;
		case West:
			x = x - 1;
			if (Map[x][y] == '.' && TraceMap[x][y] == 0)
			{
				TraceMap[x][y] = 1;
				cost = TryMove(x, y, West, MirrorCount);
				if (MirrorCount + 1 < SmallestSolutionMirrorCount)
				{
					int turncost = std::min(TryMove(x, y, North, MirrorCount + 1), TryMove(x, y, South, MirrorCount + 1));
					if (turncost != INT_MAX)
					{
						cost = std::min(turncost + 1, cost);
					}
				}
				TraceMap[x][y] = 0;
			}
			break;
		}
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
                int cost = TryMove(x, y, North, 0);
                cost = std::min(cost, TryMove(x, y, South, 0));
                cost = std::min(cost, TryMove(x, y, East, 0));
                cost = std::min(cost, TryMove(x, y, West, 0));

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
