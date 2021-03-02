#include <stdio.h>
#include <deque>
#include <iostream>
#include <conio.h>
#include <vector>
#include <time.h>
using namespace std;

//Class for Player
class Player
{
public:
	int x, y;

	Player(int width)
	{
		//Player will start at the top of the map in the middle of the play area
		x = width / 2;
		y = 0;
	}
};

class Lane
{
private:
	deque<bool> cars;
	bool right;
public:
	Lane(int width)
	{
		for (int i = 0; i < width; i++)
			//No cars will exist at the beginning
			cars.push_front(true);
		right = rand() % 2;

	}

	void Move()
	{
		if (right)
		{
			if (rand() % 10 == 1)
				//If the random number is 1, 1 is put on the left side of the game area
				cars.push_front(true);
			else
				//If the random number isn't 1, 0 is put on the left side of the game area
				cars.push_front(false);
			//Deleting the right most element of the deque, so the size is constant
			cars.pop_back();
		}
		else
		{

			if (rand() % 10 == 1)
				//If the random number is 1, 1 is put on the left side of the game area
				cars.push_back(true);
			else
				//If the random number isn't 1, 0 is put on the left side of the game area
				cars.push_back(false);
			//Deleting the right most element of the deque, so the size is constant
			cars.pop_front();
		}
		
	}
	bool checkPos(int pos)
	{ return cars[pos]; }
	void changeDirection()
	{ right = !right; }
};

//Class Cross the Road
class CTR
{
private:
	bool quit;
	//Number of Lanes
	int number;
	int width;
	int score;
	Player* p;
	vector<Lane*> map;

public:
	CTR(int w = 20, int h = 10)
	{
		number = h;
		width = w;
		score = 0;
		quit = false;
		for (int i = 0; i < number; i++)
		{
			map.push_back(new Lane(width));
		}
		p = new Player(width);
	}

	~CTR()
	{
		delete p;
		for (int i = 0; i < map.size(); i++)
		{
			Lane* current = map.back();
			map.pop_back();
			delete current;
		}
	}


	void Draw()
	{
		system("cls");
		std::cout << " -------------Welcome to Cross The Road!-------------" << std::endl;
		std::cout << "  ---------Created By: Julian-Justin Djoum---------" << std::endl;
		std::cout << "  __________________________________________________" << std::endl << std::endl;

		for (int i = 0; i < number; i++)
		{
			for (int j = 0; j < width; j++)
			{

				if (i == 0 && (j == 0 || j == width - 1)) cout << "S";
				if (i == number - 1 && (j == 0 || j == width - 1)) cout << "F";
				//Car exists
				if (map[i]->checkPos(j) && i != 0 && i != number - 1)
				{
					cout << "#";
				}
				else if (p->x == j && p->y == i)
				{
					cout << "V";
				}
				else
					cout << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << "Score: " << score << endl;
	}
	void Input()
	{
		if (_kbhit())
		{
			char current = _getch();
			if (current == 'a')
				p->x--;
			if (current == 'd')
				p->x++;
			if (current == 's')
				p->y++;
			if (current == 'w')
				p->y--;
			if (current == 'q')
				quit = true;
		}
	}
	void Logic()
	{
		//Loop doesn't check top and bottom levels
		for (int i = 1; i < number - 1; i++)
		{
			if (rand() % 10 == 1)
				map[i]->Move();

			if (map[i]->checkPos(p->x) && p->y == i)
				quit = true;
		}

		if (p->y == number - 1)
		{
			score++;
			p->y = 0;
			cout << "\x07";
			map[rand() % number]->changeDirection();
		}
	}
	void Run()
	{
		//While quit is not true...
		while (!quit)
		{
			Input();
			Draw();
			Logic();
		}


	}

};

int main()
{
	//Makes cars spawn randomly
	srand(time(NULL));
	CTR game(30, 5);
	game.Run();
	cout << endl;
	std::cout << "  ---------Game Over!--------  " << std::endl;
	cout << endl;
	return 0;
}	
