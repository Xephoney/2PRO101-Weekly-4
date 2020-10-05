#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <ctime>
#include <random>

using namespace std;
const int height = 15;
const int width = 30;
int currentLevel = 0;
char Icons[5]{ '-','X','\\','/','G' };
struct Position
{
	int x;
	int y;
};


string Task1(string);
string Task1(string _sentence)
{

	int size = _sentence.length();
	for (int i = 0; i < size; i++)
	{
		if (_sentence[i] != ' ')
		{
			_sentence[i] = toupper(_sentence[i]);
		}
	}
	return _sentence;
}

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
	cout << "Get to level +-5 and reach the 'G' to win!" << endl;
	cout << "Level up: \\" << endl;
	cout << "Level down: /" << endl;
	cout << "Move around with W A S D" << endl << endl;
	cout << "You are on level " << currentLevel << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << board[j][i] << "";
		}
		cout << endl;
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

		cout << "X : " << player1.x + 1 << " | Y : " << player1.y + 1 << endl;
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

	cout << "X : " << player1.x << " | Y : " << player1.y << endl;
	//cout << "Current level: " << currentLevel << endl;
	cout << "\n\n\tCongratulations, you won!";
}

struct PersonInfo {
	int phonenumber;
	string name;

};
void task3();
void task3() {
	vector <PersonInfo> persons{ 10 };
	for (int i = 0; i < persons.size(); i++)
	{
		cout << persons[i].name << endl;
		cout << persons[i].phonenumber << endl << endl;
	}
}


int main()
{
	
	#pragma region Task1
		string sentence;
		cout << "enter a sentence:\n";
		getline(cin, sentence);
		string _sentence = Task1(sentence);
		cout << _sentence << endl;
	#pragma endregion
	
	
	#pragma region Task2
		srand(time(NULL));
		Game();
	#pragma endregion
	
	task3();


	return 0;
}




