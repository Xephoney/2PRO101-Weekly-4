#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <ctime>
//I added this to use Sleep
#include <Windows.h>
//This is required for the sorting algorithm
#include <algorithm>



#pragma region Task 1 Functions and Variables
char CharacterToUpper(char);
char CharacterToUpper(char _a)
{
	return toupper(_a);
}
void Task1();
void Task1()
{
	std::cout << "\n\t[-- TASK 1 --]\n";
	std::string sentence;
	std::cout << "Enter a sentence or character:\n";
	std::cin.ignore(10000, '\n');
	std::getline(std::cin, sentence);

	for (int i = 0; i < sentence.length(); i++)
	{
		if (sentence[i] != ' ')
		{
			sentence[i] = CharacterToUpper(sentence[i]);
		}
	}

	std::cout << "Function result : \n" << sentence << std::endl << std::endl;
	std::cout << "When you are ready to return to the menu, just ";
	system("pause");
}

#pragma endregion

#pragma region Task 2 Functions and Variables

char Icons[5]{ '-','X','\\','/','G' };
const int height = 10;
const int width = 10;
int currentLevel = 0;

//This is a data container which holds an x and a Y postion. This translates into the 2d grid array. 
struct Position
{
	int x;
	int y;
};
//Generates a random postion on the grid. An X and a Y coordinate
Position RandomPosition();
Position RandomPosition() {

	Position newPos;

	newPos.x = rand() % width;
	newPos.y = rand() % height;

	return newPos;
}
//Prints board
void map(char board[width][height]);
void map(char board[width][height])
{
	system("cls");
	std::cout << "Get to level +-5 and reach the 'G' to win!" << std::endl;
	std::cout << "Level up: \\" << std::endl;
	std::cout << "Level down: /" << std::endl;
	std::cout << "Move around with W A S D" << std::endl << std::endl;
	std::cout << "You are on level " << currentLevel << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << board[j][i] << "";
		}
		std::cout << std::endl;
	}
}
Position Input(Position, char b[width][height]);
Position Input(Position p, char b[width][height])
{
	int key = _getch();
	b[p.x][p.y] = Icons[0];
	key = tolower(key);
	switch (key)
	{
	case 'a':
		p.x--;
		break;
	case 'd':
		p.x++;
		break;
	case 'w':
		p.y--;
		break;
	case 's':
		p.y++;
		break;
	default:
		break;
	}
	//Clamping and wrapping X axis. This prevents x from ever going of the play area.
	if (p.x > width - 1)
	{
		p.x = 0;
	}
	else if (p.x < 0)
	{
		p.x = width - 1;
	}
	//Clamping and wrapping Y axis. This prevents y from ever going of the play area.
	if (p.y > height - 1) {
		p.y = 0;
	}
	else if (p.y < 0)
	{
		p.y = height - 1;
	}
	return p;
}
void Game();
void Game() {

	char board[width][height];
	memset(board, '-', width * height);

	//Velg spiller plass. 
	Position player1;
	player1.x = width / 2;
	player1.y = height / 2;

	Position G;
	Position levelUp;
	Position levelDown;
	if (currentLevel != -5 && currentLevel != 5)
	{
		do
		{
			levelUp = RandomPosition();
		} while (levelUp.x == player1.x && levelUp.y == player1.y);
		do
		{
			levelDown = RandomPosition();
		} while (levelDown.x == player1.x && levelDown.y == player1.y || levelDown.x == levelUp.x && levelDown.y == levelUp.y);

		board[levelUp.x][levelUp.y] = Icons[2];
		board[levelDown.x][levelDown.y] = Icons[3];
	}
	else if (currentLevel == 5)
	{
		do
		{
			G = RandomPosition();
			levelDown = RandomPosition();
		} while (G.x == player1.x && G.y == player1.y || levelDown.x == player1.x && levelDown.y == player1.y);
		board[levelDown.x][levelDown.y] = Icons[3];
		board[G.x][G.y] = Icons[4];
	}
	else if (currentLevel == -5)
	{
		do
		{
			G = RandomPosition();
			levelUp = RandomPosition();
		} while (G.x == player1.x && G.y == player1.y || levelUp.x == player1.x && levelUp.y == player1.y);
		board[levelUp.x][levelUp.y] = Icons[3];
		board[G.x][G.y] = Icons[4];
	}


	//GameLoop
	do {

		board[player1.x][player1.y] = Icons[1];
		map(board);

		std::cout << "X : " << player1.x + 1 << " | Y : " << player1.y + 1 << std::endl;
		//cout << "Current level: " << currentLevel << endl;


		player1 = Input(player1, board);

		//Checking for Ladders / Stairs
		//Icons[3] = Down
		if (board[player1.x][player1.y] == Icons[3])
		{
			currentLevel--;
			Game();
			break;
		}
		else if (board[player1.x][player1.y] == Icons[2]) //Icons [2] = Up
		{
			currentLevel++;
			Game();
			break;
		}

		//Input

		// '\\' = Go up
		// '/' = Go down
		// 'G'

	} while (board[player1.x][player1.y] != Icons[4]);

	map(board);

	std::cout << "X : " << player1.x << " | Y : " << player1.y << std::endl;
	//cout << "Current level: " << currentLevel << endl;
	std::cout << "\n\n\tCongratulations, you won!";
}

#pragma endregion

#pragma region Task 3 Functions and Variables
struct PersonInfo {
	int phonenumber = 55889933;
	std::string name = "Ola";
};
std::vector <PersonInfo> persons{0};

void DisplayEmployeeInfo();
void DisplayEmployeeInfo()
{
	if(persons.size() != 0)
	{ 
		std::cout << "| ID | " << "| Name | " << "| Phone Number | \n";
		for (int i = 0; i < persons.size(); i++)
		{
			std::cout << "| " << i + 1 << " | " << persons.at(i).name << "\t | " << persons.at(i).phonenumber << " |\n";
		}
		std::cout << std::endl;
		
	}
	else
	{
		std::cout << "You have no employees working for you at the moment! \nAfter you have added some employees they will end up here \n\n";
		system("pause");
	}
	
}

void AddEmployee();
void AddEmployee()
{
	std::string name;
	int phone;
	std::cout << "Okay! How is our new hire? \n";
	std::cout << "Name : ";
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	std::getline(std::cin, name);
	
	std::cout << "Great, now what is " << name << "'s phone number?\n";
	std::cout << "phone number : ";
	
	std::cin.clear();
	std::cin >> phone;

	PersonInfo temp;
	temp.name = name;
	temp.phonenumber = phone;
	persons.push_back(temp);
	
	std::cout << "Great! " << name << " is now our employee! \n";
	system("pause");
}

void FireEmployee();
void FireEmployee()
{
	int id = 0;
	DisplayEmployeeInfo();
	std::cout << "To remove an employee just refeer to their ID";
	std::cout << "Which of the employees above do you want to fire?\n";
	std::cout << "\t ID : ";


	std::cin.clear();
	std::cin.ignore(10000, '\n');
	std::cin >> id;
	id--;
	if (id >= 0 && id < persons.size())
	{
		std::cout << "Okay! We fire " << persons.at(id).name << std::endl;
		persons.erase(persons.begin() + id);
	}
	system("pause");
}

void Task3();
void Task3() 
{
	do
	{
		system("CLS");
		int answer = 0;
		std::cout << "Hi there Manager! What do you want to do today? \n";
		std::cout << "\t 1. Display employee info \n";
		std::cout << "\t 2. Add new employee \n";
		std::cout << "\t 3. Fire employee \n";
		std::cout << "\t 4. Call it a day and go home\n";
		
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cin >> answer;
		switch (answer)
		{
			case 1 :
				DisplayEmployeeInfo();
				system("pause");
				break;
			case 2 :
				//I preform a simple check here just to make sure im able to add people into the vector.
				if (persons.size() < 10)
				{
					AddEmployee();
					break;
				}
				else
				{
					std::cout << "Im sorry sir, but you have 10 employees already!\n";
					std::cout << "You'll have to fire some before you can add a new employee!\n";
					system("pause");
					break;
				}
				break;
			case 3 :
				if (persons.size() > 0)
				{
					FireEmployee();
					break;
				}
				else
				{
					std::cout << "Im sorry sir, but you have no employees to fire!\n";
					std::cout << "You'll have to hire someone first some before you can fire them!\n";
					system("pause");
					break;
				}
				break;
			case 4 :
				return;
				break;
			default:
				break;
		}
	} while (true);
}
#pragma endregion

#pragma region Task 4 Functions and Variables

struct Dice
{
	int face;
	bool locked = false;
	void Roll()
	{
		face = (rand() % 6) + 1;
	}
};
void RollDice(Dice* ptr, int size);
void RollDice(Dice* ptr, int size)
{
	for (int i = 0; i < size; i++)
	{
		if(ptr[i].locked == false)
		{
			ptr[i].Roll();
		}
	}
}
void Display(Dice *ptr, int size);
void Display(Dice *ptr, int size)
{
	system("CLS");

	std::cout << "Press |H| or |SPACE| to roll the dice! \n";
	std::cout << "To keep your roll for any particular dice, just press 1 - 5 to lock that dice.\n";
	std::cout << "A locked dice will have [ ] around it!\n";

	std::cout << "To return to the main menu, press |E|\n\n";

	for (int i = 0; i < size; i++)
	{
		if (ptr[i].locked)
		{
			std::cout << "| [" << ptr[i].face << "] ";
		}
		else
		{
			std::cout << "|  " << ptr[i].face << "  ";
		}
	}
	std::cout << "|\n\n";

	
}

void CalculateSameDice(Dice *arr, int size);
void CalculateSameDice(Dice *arr, int size)
{
	int _count = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i].face == 6)
		{
			_count++;
		}
	}
	std::cout << "Total number of 6's : " << _count << std::endl << std::endl;
}

void CalculatePairs(Dice *arr, int size);
void CalculatePairs(Dice *arr, int size)
{
	//First i need to sort the array. 
	//Then i go through and check if one element has more than one of it.

	int faceCopy[5];
	for (int i = 0; i < size; i++)
	{
		faceCopy[i] = arr[i].face;
	}
	std::sort(faceCopy, faceCopy +5);

	int counter = 0;
	Dice temp;
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j < size; j++)
		{
			if ((faceCopy[i] - faceCopy[j]) == 0 && i != j)
			{
				std::cout << "Pairs of " << faceCopy[i] << std::endl;
				break;
			}
		}
	}

}

void Task4();
void Task4()
{
	Dice AllDice[5];
	int AllDiceSize = _countof(AllDice);

	//This loop is only played once to scramble the dice.
	for (int i = 0; i < AllDiceSize; i++)
	{
		AllDice[i].Roll();
	}
	//Displays all dice
	do
	{
		Display(AllDice, AllDiceSize);
		CalculateSameDice(AllDice, AllDiceSize);
		CalculatePairs(AllDice, AllDiceSize);
		int input = _getch();
		input = tolower(input);
		switch (input)
		{
		case 32 : case 104 : 
			//SPACE
			RollDice(AllDice,AllDiceSize);
			Sleep(50);
			break;
		case 49 :
			// 1 on the keyboard
			AllDice[0].locked = !(AllDice[0].locked);
			Sleep(50);
			break;
		case 50 : 
			// 2
			AllDice[1].locked = !(AllDice[1].locked);
			Sleep(50);
			break;
		case 51 :
			// 3
			AllDice[2].locked = !(AllDice[2].locked);
			Sleep(50);
			break;
		case 52 : 
			// 4
			AllDice[3].locked = !(AllDice[3].locked);
			Sleep(50);
			 
			break;
		case 53 : 
			// 5
			AllDice[4].locked = !(AllDice[4].locked);
			Sleep(50);
			break;
		case 101 : 
			//e has been pressed
			return;
		default:
			break;
		}
		//The reason i use sleep inside at 50 ms is to stop it from looping to fast to then register double. 

	} while (true);
	
}
#pragma endregion


int main()
{
	srand(time(NULL));
	do
	{
		int Choice = 0;
		system("cls");
		std::cout << "Welcome to Weekly 4 \n";
		std::cout << "What task would you like to check out first? \n";
		std::cout << "\t |1. Sentence to upper case \n";
		std::cout << "\t |2. Grid Boi \n";
		std::cout << "\t |3. Employee Manager 2020\n";
		std::cout << "\t |4. Roll-The-Dice\n";
		std::cout << "\t |5. Exit \n\n";
		std::cout << "Select one of the tasks above : ";
		
		std::cin >> Choice;

		switch (Choice)
		{
		case 1:
			Task1();
			break;
		case 2:
			Game();
			break;
		case 3:
			Task3();
			break;
		case 4:
			Task4();
			break;
		case 5:
			std::cout << "Exiting application! Goodbye \n\n\n\n\n\n\n";
			return 0;
		default:
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			break;
		}
	} while (true);
	return 0;
}