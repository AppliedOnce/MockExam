#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <algorithm>

struct Score
{
	int number;
	char name;
	int value;
};

bool LoginPassword();
void Menu();
void TaskOne();
void TaskTwo();
void TaskThree();
void TaskFour();

void PrintBoard(std::vector<int> grid, int playerPos);
void PrintBoard(std::vector<std::vector<char>> grid, std::vector<int> playerPos, int score);
int MovePlayer(int playerPos);
std::vector<int> MovePlayer(std::vector<std::vector<char>> grid, std::vector<int> currentPos);
int GetRandomNumber(int max);
bool CompareScores(Score a, Score b);

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	if (LoginPassword())
	{
		Menu();
	}
}

bool LoginPassword()
{
	const int MAX_MOVES = 4;
	const int MAX_TRIES = 3;
	bool correctPassword = false;
	int moveCounter = 0;
	int tryCounter = 0;
	int wrongMoves = 0;
	std::vector<int> grid = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int playerPos = 0;
	int oldPlayerPos = -1;

	do
	{
		moveCounter = 0;
		playerPos = 0;
		oldPlayerPos = -1;
		wrongMoves = 0;
		do
		{
			PrintBoard(grid, playerPos);
			std::cout << "Press w, a, s or d to move the asterisk" << std::endl;
			oldPlayerPos = playerPos;
			playerPos = MovePlayer(playerPos);
			if (moveCounter == 0 && playerPos != 3)
			{
				wrongMoves++;
			}
			else if (moveCounter == 1 && playerPos != 4)
			{
				wrongMoves++;
			}
			else if (moveCounter == 2 && playerPos != 1)
			{
				wrongMoves++;
			}
			else if (moveCounter == 3 && playerPos != 2)
			{
				wrongMoves++;
			}
			if (playerPos != oldPlayerPos)
				moveCounter++;
			if (wrongMoves == 0 && moveCounter == MAX_MOVES)
			{
				correctPassword = true;
				std::cout << "\nCorrect password!\n" << std::endl;
			}
			else if (wrongMoves != 0 && moveCounter == MAX_MOVES)
			{
				std::cout << "\nWrong password, try again!\n" << std::endl;
			}
		} while (moveCounter < MAX_MOVES);
		tryCounter++;
	} while ((tryCounter < MAX_TRIES) && (correctPassword == false));

	return correctPassword;
}

void Menu()
{
	int menuChoice = 0;
	bool playing = true;

	do
	{
		std::cout << "1. Task 1" << std::endl;
		std::cout << "2. Task 2" << std::endl;
		std::cout << "3. Task 3" << std::endl;
		std::cout << "4. Task 4" << std::endl;
		std::cout << "5. Exit" << std::endl;
		std::cout << "Enter a number from 1 to 5: ";
		std::cin >> menuChoice;
		
		switch (menuChoice)
		{
		case 1:
			TaskOne();
			break;
		case 2:
			TaskTwo();
			break;
		case 3:
			TaskThree();
			break;
		case 4:
			TaskFour();
			break;
		case 5:
			playing = false;
			break;
		default:
			std::cout << "Invalid input... Try again." << std::endl;
			break;
		}
	} while (playing);
}

void TaskOne()
{
	int ones = 0;
	int twos = 0;
	int threes = 0;
	int fours = 0;
	int fives = 0;
	int sixes = 0;

	int die = 0;

	for (int i = 0; i < 2000; i++)
	{
		die = GetRandomNumber(6);
		switch (die)
		{
		case 1:
			ones++;
			break;
		case 2:
			twos++;
			break;
		case 3:
			threes++;
			break;
		case 4:
			fours++;
			break;
		case 5:
			fives++;
			break;
		case 6:
			sixes++;
			break;
		default:
			std::cout << "Something went terribly wrong!" << std::endl;
			break;
		}
	}

	std::cout << std::endl << "1: " << ones << " times" << std::endl;
	std::cout << "2: " << twos << " times" << std::endl;
	std::cout << "3: " << threes << " times" << std::endl;
	std::cout << "4: " << fours << " times" << std::endl;
	std::cout << "5: " << fives << " times" << std::endl;
	std::cout << "6: " << sixes << " times" << std::endl << std::endl;
}

void TaskTwo()
{
	std::cout << std::endl;
	const int TOTAL_SCORES = 10;
	std::vector<Score> scores(TOTAL_SCORES);
	for (int i = 0; i < scores.size(); i++)
	{
		scores.at(i).name = i + 65;
		scores.at(i).value = GetRandomNumber(20);
	}
	std::cout << "No\t" << "Name\t" << "Value\t" << "Health Bar" << std::endl;
	std::sort(scores.begin(), scores.end(), CompareScores);
	for (int i = 0; i < scores.size(); i++)
	{
		scores.at(i).number = i;
		std::cout << scores.at(i).number << "\t" << scores.at(i).name << "\t" << scores.at(i).value << "\t";
		for (int j = 0; j < scores.at(i).value; j++)
		{
			std::cout << "*";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void TaskThree()
{
	std::cout << std::endl;

	std::vector<std::vector<char>> grid =
	{
		{'+','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','+'},
		{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
		{'|','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','|'},
		{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','H','|'},
		{'|',' ','|',' ','|','#','#','#','#','#','#','#','#','#','#','#','|','|'},
		{'|',' ','|',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','|'},
		{'|',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
		{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
		{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
		{'+','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','+'},
	};
	std::vector<int> playerPos = { 7, 9 };
	std::vector<int> lastPlayerPos;
	int score = 0;
	bool playing = true;
	char player = 'E';

	grid[playerPos[0]][playerPos[1]] = player;


	while (playing)
	{
		PrintBoard(grid, playerPos, score);
		lastPlayerPos = playerPos;
		playerPos = MovePlayer(grid, playerPos);

		grid[lastPlayerPos[0]][lastPlayerPos[1]] = ' ';
		if (grid[playerPos[0]][playerPos[1]] == 'H')
		{
			playing = false;
		}
		else
		{
			grid[playerPos[0]][playerPos[1]] = player;
		}
	}

	std::cout << std::endl;
}

void TaskFour()
{
	std::cout << std::endl;

	std::vector<std::vector<char>> grid =
	{
		{'+','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','+'},
		{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
		{'|','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','|'},
		{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','H','|'},
		{'|',' ','|',' ','|','#','#','#','#','#','#','#','#','#','#','#','|','|'},
		{'|',' ','|',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','|'},
		{'|',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
		{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
		{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
		{'+','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','+'},
	};
	std::vector<int> playerPos = { 7, 9 };
	std::vector<int> lastPlayerPos;
	int score = 0;
	const int POINT_AMOUNT = 10;
	bool playing = true;
	char player = 'E';
	bool pointPosValid = false;

	grid[playerPos[0]][playerPos[1]] = player;
	std::vector<int> pointPos(2, 0);

	for (int i = 0; i < POINT_AMOUNT; i++)
	{
		do
		{
			pointPos = { GetRandomNumber(grid.size() - 1), GetRandomNumber(grid[0].size() - 1) };
			std::cout << "i: " << i << ", point x: " << pointPos[0] << ", point y: " << pointPos[1] << std::endl;

			if (grid[pointPos[0]][pointPos[1]] == ' ')
			{
				grid[pointPos[0]][pointPos[1]] = '-';
				pointPosValid = true;
			}
			std::cout << pointPosValid << std::endl;
		} while (!pointPosValid);
		pointPosValid = false;
	}


	while (playing)
	{
		PrintBoard(grid, playerPos, score);
		lastPlayerPos = playerPos;
		playerPos = MovePlayer(grid, playerPos);

		grid[lastPlayerPos[0]][lastPlayerPos[1]] = ' ';
		if (grid[playerPos[0]][playerPos[1]] == '-')
		{
			score += 5;
		}
		if (grid[playerPos[0]][playerPos[1]] == 'H')
		{
			playing = false;
		}
		else
		{
			grid[playerPos[0]][playerPos[1]] = player;
		}
	}
	std::cout << std::endl;
	std::cout << "You got a score of: " << score << "!" << std::endl;
	std::cout << std::endl;
}

void PrintBoard(std::vector<int> grid, int playerPos)
{
	for (int i = 0; i < grid.size(); i++)
	{
		if (i == playerPos)
		{
			std::cout << " *";
		}
		else
		{
			std::cout << " " << grid.at(i);
		}
		if (i % 3 == 2)
		{
			std::cout << std::endl;
		}
	}
}

void PrintBoard(std::vector<std::vector<char>> grid, std::vector<int> playerPos, int score)
{
	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{
			std::cout << grid[x][y];
			if (x == 1 && y == grid[x].size() - 1)
			{
				std::cout << " " << score;
			}
		}
		std::cout << std::endl;
	}
}

int MovePlayer(int playerPos)
{
	int newPlayerPos = 0;
	bool invalidInput = false;
	char playerInput = ' ';
	do
	{
		playerInput = _getch();
		switch (tolower(playerInput))
		{
		case 'a':
			newPlayerPos = playerPos - 1;
			break;
		case 'w':
			newPlayerPos = playerPos - 3;
			break;
		case 'd':
			newPlayerPos = playerPos + 1;
			break;
		case 's':
			newPlayerPos = playerPos + 3;
			break;
		default:
			break;
		}
	} while (invalidInput);

	if (newPlayerPos < 0)
	{
		return playerPos;
	}
	else if (newPlayerPos > 8)
	{
		return playerPos;
	}

	return newPlayerPos;
}

std::vector<int> MovePlayer(std::vector<std::vector<char>> grid, std::vector<int> playerPos)
{
	std::vector<int> newPlayerPos = playerPos;
	bool invalidInput = false;
	char playerInput = ' ';
	char wall1 = '#';
	char wall2 = '|';
	do
	{
		playerInput = _getch();
		switch (tolower(playerInput))
		{
		case 'w':
			if ((grid[playerPos[0] - 1][playerPos[1]] == wall1) || (grid[playerPos[0] - 1][playerPos[1]] == wall2))
				invalidInput = true;
			else
			{
				invalidInput = false;
				newPlayerPos[0] = newPlayerPos[0] - 1;
			}
			break;
		case 'a':
			if ((grid[playerPos[0]][playerPos[1] - 1] == wall1) || (grid[playerPos[0]][playerPos[1] - 1] == wall2))
				invalidInput = true;
			else
			{
				invalidInput = false;
				newPlayerPos[1] = newPlayerPos[1] - 1;
			}
			break;
		case 's':
			if ((grid[playerPos[0] + 1][playerPos[1]] == wall1) || (grid[playerPos[0] + 1][playerPos[1]] == wall2))
				invalidInput = true;
			else
			{
				invalidInput = false;
				newPlayerPos[0] = newPlayerPos[0] + 1;
			}
			break;
		case 'd':
			if ((grid[playerPos[0]][playerPos[1] + 1] == wall1) || (grid[playerPos[0]][playerPos[1] + 1] == wall2))
				invalidInput = true;
			else
			{
				invalidInput = false;
				newPlayerPos[1] = newPlayerPos[1] + 1;
			}
			break;
		default:
			break;
		}
	} while (invalidInput);

	return newPlayerPos;
}

std::vector<int> MovePlayer(char input, std::vector<int> currentPos)
{
	std::vector<int> newPlayerPos = currentPos;
	switch (input)
	{
	case 'a':
		if ((newPlayerPos[1] - 1) >= 0)
			newPlayerPos[1] = newPlayerPos[1] - 1;
		break;
	case 'd':
		if ((newPlayerPos[1] + 1) <= 9)
			newPlayerPos[1] = newPlayerPos[1] + 1;
		break;
	case 'w':
		if ((newPlayerPos[0] - 1) >= 0)
			newPlayerPos[0] = newPlayerPos[0] - 1;
		break;
	case 's':
		if ((newPlayerPos[0] + 1) <= 9)
			newPlayerPos[0] = newPlayerPos[0] + 1;
		break;
	default:
		std::cout << "Invalid input." << std::endl;
		break;
	}

	return newPlayerPos;
}

bool CompareScores(Score a, Score b)
{
	return (a.value > b.value);
}

int GetRandomNumber(int max)
{
	int randomNumber = rand() % max + 1;
	return randomNumber;
}