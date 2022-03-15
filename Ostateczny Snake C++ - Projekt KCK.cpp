
// Snake by Pogrebniak Mateusz 
// Informatyka, Semestr V, Politechnika Bia³ostocka
// 23.11.2021



// BIBLIOTEKI
	#include <iostream>
	#include <string>
	#include <vector>			// Dodaje vector
	#include <conio.h>			// Funkcje getch()
	#include <windows.h>		// Funkcje Windows
	#include <ctime>			// Funkcje czasowe									 
	#include <fstream>			// Funkcje z plikami zewnêtrznymi
	#include "stdafx.h"			// "Powinno" usprawniaæ stabilizacjê i dzia³anie programu
	using namespace std;
// BIBLIOTEKI



// ZMIENNE GLOBALNE
	#define WIDTH 31					// Szerokoœæ Planszy
	#define HEIGHT 26					// Wysokoœæ Planszy
	char Level[HEIGHT][WIDTH];			// Plansza
	int z;
	int it = 0;							// Zmienne do Main
	int m = 1;							// Poruszanie siê klawiatur¹ w Menu G³ównym
	int n = 1;							// Poruszanie siê klawiatur¹ w Wyborze Trudnoœci
	int o = 1;							// Poruszanie siê klawiatur¹ w Opcjach
	int s = 1;							// Poruszanie siê klawiatur¹ w Tablicy Wyników
	int p = 1;							// Poruszanie siê klawiatur¹ Aktywnego Koloru
	int x = 1;							// Poruszanie siê klawiatur¹ na Koñcu Gry
	int red = 1;						// Wybór koloru (standardowo czerwony)
	int white = 1;						// Wybór koloru (standardowo bia³y)
	int violet = 1;						// Wybór koloru (standardowo fioletowy)
	vector<int>Punktacja;				// Tablica Wyników
	
// ZMIENNE GLOBALNE




// SPIS TREŒCI - DEKLARACJA FUNKCJI

	// WYŒWIETLANIE INTERFEJSU
		void ShowConsoleCursor(bool showFlag); //Wy³¹czenie kursora
		void ShowDifficulty();		// Wybór Poziomu Trudnoœci		
		void MainMenu();			// Menu g³ówne
		void ShowControllers();		// Informacje o sterowaniu
		void ShowOptions();			// Opcje
		void Scoreboard();			// Wyniki gry
		void BuildBoard();			// Budowanie Poziomu Gry
		void DrawBoard();			// Rysowanie Poziomu Gry
		void ClearScreen();			// Resetowanie i jasnoœæ obrazu
		void IsActive();			// Zmiana g³ównego motywu
		void DisplayRed();			// Maluj na czerwono
		void DisplayWhite();		// Maluj na bia³o
		void DisplayViolet();		// Maluj na fioletowo
		void LeftMark();			// Lewa Strza³ka
		void RightMark();			// Prawa Strza³ka
	// WYŒWIETLANIE INTERFEJSU


	// ZARZ¥DZANIE WÊ¯EM
		void CreateSnake();		// Utwórz Wê¿a	

		void InitializeSnake	// Inicjalizuj Wê¿a
		(int rozmiar, int snakeX[], int snakeY[]);

		void MoveWithSnake			// Zarz¹dzaj Wê¿em
		(int& rozmiar, int snakeX[], int snakeY[], int tempX[],
			int tempY[], int& item_count, int& punkty);

		void SetSnakeSpeed();	// Ustaw prêdkoœæ Wê¿a

		void FeedingSnake		// Nakarm Wê¿a
		(vector<int>& itemX, vector<int>& itemY, int& item_count, int snakeX[],
			int snakeY[], int& rozmiar, int tailX, int tailY, int& punkty);
	// ZARZ¥DZANIE WÊ¯EM


	// KOÑCZENIE GRY
		bool IsGameOver // Warunki koñca gry
		(int snakeX[], int snakeY[], int rozmiar);

		void GameOver(); // Koniec gry i ponowne zagranie
	// KOÑCZENIE GRY

// SPIS TREŒCI - DEKLARACJA FUNKCJI









// MENU
int main()
{
	//Wczytywanie z pliku
	fstream plik1;						// Zarz¹dzanie plikiem wyników
	plik1.open("dane.txt", std::ios::in | std::ios::out);
	int number = 0;
	while (!plik1.eof())
	{
		plik1 >> number;
		Punktacja.push_back(number);
	}
	plik1.close();

	setlocale(LC_CTYPE, "Polish"); //Ustawienie polskich znaków
	ShowConsoleCursor(false); //Wy³¹czenie kursora
	MainMenu(); //Przejœcie do MainMenu
	
}





/*
* 
	WYŒWIETLANIE INTERFEJSU
*
*/


//Wy³¹czenie kursora
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}


// MENU G£ÓWNE
void MainMenu()
{

	while (1)
	{
		DisplayViolet();
		system("cls");
		printf("\n\n");
		printf("\t\t  SSSSS    NN    NN   AAAAAAA   KK     KK  EEEEEEE\n");
		printf("\t\t SS   SS   NN    NN   AA   AA   KK   KK    EE\n");
		printf("\t\t SS   SS   NNNN  NN   AA   AA   KK  KK     EE\n");
		printf("\t\t SS        NN NN NN   AA   AA   KK KK      EE\n");
		printf("\t\t  SSS      NN  NN N   AA   AA   KKKK       EE\n");
		printf("\t\t    SSS    NN   NNN   AAAAAAA   KKKK       EEEEE\n");
		printf("\t\t      SS   NN    NN   AA   AA   KK KK      EE\n");
		printf("\t\t SS   SS   NN    NN   AA   AA   KK  KK     EE\n");
		printf("\t\t SS   SS   NN    NN   AA   AA   KK   KK    EE\n");
		printf("\t\t  SSSSS    NN    NN   AA   AA   KK     KK  EEEEEEE\n\n\n");


		if (m == 1) { DisplayRed();LeftMark();printf(" START GAME ");RightMark(); }
		if (m == 1) { DisplayWhite(); printf("\t\t\t\t  OPTIONS\n"); }
		if (m == 1) { DisplayWhite(); printf("\t\t\t\t  EXIT AND SAVE\n"); }
		if (m == 2) { DisplayWhite(); printf("\t\t\t\t  START GAME\n"); }
		if (m == 2) { DisplayRed();LeftMark();printf(" OPTIONS ");RightMark(); }
		if (m == 2) { DisplayWhite(); printf("\t\t\t\t  EXIT AND SAVE\n"); }
		if (m == 3) { DisplayWhite(); printf("\t\t\t\t  START GAME \n"); }
		if (m == 3) { DisplayWhite(); printf("\t\t\t\t  OPTIONS \n"); }
		if (m == 3) { DisplayRed();LeftMark();printf(" EXIT AND SAVE");RightMark(); }

		z = _getch();

		if (z == 72) { m--; }
		if (m == 0) { m = +3; }
		if (z == 80) { if (m < 3) { m++; } }	// Ograniczenie


		if ((z == 13) && (m == 3))
		{
			fstream plik2;
			plik2.open("dane.txt", std::ios::in | std::ios::out);
			//Zapisywanie do pliku
			for (int i = 0; i < Punktacja.size(); i++)
			{
				plik2 << Punktacja[i] << endl;
			}
			plik2.close();

			exit(0);
		}
		if ((z == 13) && (m == 2))  ShowOptions();
		if ((z == 13) && (m == 1))  ShowDifficulty();

	}
}


// WYBÓR POZIOMU TRUDNOŒCI
void ShowDifficulty()
{


	while (1)
	{
		system("cls");	// Wyczyœæ obraz
		DisplayWhite();
		printf("\n\n\n\t\t\t    CHOOSE DIFFICULTY LEVEL:      \n\n\n");

		if (n == 1) { DisplayRed();LeftMark();printf(" EASY ");RightMark(); }
		if (n == 1) { DisplayWhite(); printf("\t\t\t\t  MEDIUM\n"); }
		if (n == 1) { DisplayWhite(); printf("\t\t\t\t  HARD\n"); }
		if (n == 2) { DisplayWhite(); printf("\t\t\t\t  EASY\n"); }
		if (n == 2) { DisplayRed();LeftMark();printf(" MEDIUM ");RightMark(); }
		if (n == 2) { DisplayWhite(); printf("\t\t\t\t  HARD\n"); }
		if (n == 3) { DisplayWhite(); printf("\t\t\t\t  EASY \n"); }
		if (n == 3) { DisplayWhite(); printf("\t\t\t\t  MEDIUM \n"); }
		if (n == 3) { DisplayRed();LeftMark();printf(" HARD ");RightMark(); }

		z = _getch();

		if (z == 72) { n--; }
		if (z == 80) { n++; }
		if (n == 4) if (n > 3) { n--; } // Ograniczenie

		if (n == 0) { n = +3; }



		if ((z == 13) && (n == 3)) ShowControllers();
		if ((z == 13) && (n == 2)) ShowControllers();
		if ((z == 13) && (n == 1)) ShowControllers();
		
	}
}

// INFORMACJE O STEROWANIU
void ShowControllers()
{
	system("cls");
	cout << "\n\n\t\t\t CONTROLERS 'w', 'a', 's', 'd'\n\t\t\t\t Pause - 'p'\n\n";
	cout << "\n\n\t\t\t Watch out for your tail and wall";
	cout << "\n\n\t\t\t    Press any key to continue...\n\n\t\t\t\t";
	_getch();	// Oczekiwanie na klawisz
	//Punktacja.push_back(0);
	CreateSnake();
}

// Opcje
void ShowOptions()
{
	while (1)
	{
		system("cls");									// Czyszczenie Ekranu
		DisplayWhite();
		printf("\n\n\n\t\t\t\t OPTIONS:      \n\n\n");

		/*
		if (n == 1) { DisplayRed();LeftMark();printf(" CHOOSE ANOTHER COLOR ");RightMark(); }
		if (n == 1) { DisplayWhite(); printf("\t\t\t\t  BACK\n"); }
		if (n == 2) { DisplayRed();LeftMark();printf(" BACK ");RightMark(); }
		if (n == 2) { DisplayWhite(); printf("\t\t\t\t  CHOOSE ANOTHER COLOR\n"); }
		*/


		if (o == 1) { DisplayRed(); }printf("\t\t\t CHOOSE ANOTHER COLOR\n");DisplayWhite();
		if (o == 2) { DisplayRed(); }printf("\t\t\t BACK\n");DisplayWhite();
		z = _getch();

		if (z == 72) { o--; }
		if (o == 0) { o = +2; }
		if (z == 80) { if (o < 2) { o++; } }	// Ograniczenie z do³u
		if ((z == 13) && (o == 1)) IsActive();
		if ((z == 13) && (o == 2)) MainMenu();
	}
}


// WYNIKI GRY
void Scoreboard()
{


	while (1)
	{
		system("cls");	// Wyczyœæ ekran
		DisplayViolet();
		printf("\n\n\n\t\t\t SCORES:      \n\n\n");

		DisplayWhite();
		for (int i = 0; i < Punktacja.size(); i++)
		{
			printf("\t\t\t   ");
			cout << Punktacja[i] << endl;
		}

		if (s == 1) { DisplayRed(); printf("\n\n\t\t\t BACK\n");}
	
		DisplayWhite();

		z = _getch();

		if (z == 72) { s--; }
		if (s == 0) { s = +1; }
		if (z == 80) { if (s < 1) { s++; } }	// Ograniczenie z do³u
		if ((z == 13) && (s == 1)) MainMenu();
	}

}

// BUDOWANA POZIOMU
void BuildBoard()
{

	for (int i = 0; i < HEIGHT; i++)
	{
		
		for (int j = 0; j < WIDTH; j++)
		{
			Level[i][j] = ' ';
			Level[0][j] = '#';
			Level[i][0] = '#';
			Level[i][WIDTH - 1] = '#';
			Level[HEIGHT - 1][j] = '#';
		}
		
	}
}


// WYŒWIETLANIE POZIOMU
void DrawBoard()
{
	
	for (int i = 0; i < HEIGHT; i++)
	{
		cout << endl;
		for (int j = 0; j < WIDTH; j++)
			cout << " " << Level[i][j];

	}
	
}


// RESETOWANIE POZIOMU
void ClearScreen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

// Aktywne opcje
void IsActive()
{
	while (1)
	{
		system("cls");	// Wyczyœæ ekran
		DisplayWhite();
		cout << endl << "\n\n\t\t\tCHOOSE YOUR COLOR:      \n\n\n";

		/*
		if (n == 1) { DisplayRed();LeftMark();printf(" EASY ");RightMark(); }
		if (n == 1) { DisplayWhite(); printf("\t\t\t\t  MEDIUM\n"); }
		if (n == 1) { DisplayWhite(); printf("\t\t\t\t  HARD\n"); }
		if (n == 2) { DisplayWhite(); printf("\t\t\t\t  EASY\n"); }
		if (n == 2) { DisplayRed();LeftMark();printf(" MEDIUM ");RightMark(); }
		if (n == 2) { DisplayWhite(); printf("\t\t\t\t  HARD\n"); }
		if (n == 3) { DisplayWhite(); printf("\t\t\t\t  EASY \n"); }
		if (n == 3) { DisplayWhite(); printf("\t\t\t\t  MEDIUM \n"); }
		if (n == 3) { DisplayRed();LeftMark();printf(" HARD ");RightMark(); 
		*/

		if (p == 1) { DisplayRed(); }printf("\t\t\t\t VIOLET \n");DisplayWhite();
		if (p == 2) { DisplayRed(); }printf("\t\t\t\t YELLOW \n");DisplayWhite();
		if (p == 3) { DisplayRed(); }printf("\t\t\t\t BLUE \n");DisplayWhite();
		if (p == 4) { DisplayRed(); }printf("\t\t\t\t GREEN \n");DisplayWhite();
		if (p == 5) { DisplayRed(); }printf("\n\t\t\t\t BACK \n");DisplayWhite();
		z = _getch();

		if (z == 72) { p--; }
		if (p == 0) { p = +5; }
		else
			if (z == 80) { if (p < 5) { p++; } }	// Ograniczenie z do³u


		//Zmiana koloru
		if ((z == 13) && (p == 1))
		{
			violet = 1;
			DisplayRed();
		}
		if ((z == 13) && (p == 2))	
		{
			violet = 2;
			DisplayRed();
		}
		if ((z == 13) && (p == 3))
		{
			violet = 3;
			DisplayRed();
		}
		if ((z == 13) && (p == 4))
		{
			violet = 4;
			DisplayRed();
		}
		
		if ((z == 13) && (p == 5))	// Powrót do Menu
		{
			ShowOptions();
		}


	}
}


// MALUJ NA CZERWONO
void DisplayRed()
{
	if (white == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED); //bia³y kolor
	}
}

//MALUJ NA BIA£O
void DisplayWhite()
{
	if (red == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);	//czerwony kolor
	}
}

// MALUJ NA FILOTETOWO
void DisplayViolet()
{
	if (violet == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED); //fioletowy
	}

	if (violet == 2)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED); //oliwka
	}

	if (violet == 3)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE); //niebieski
	}
	if (violet == 4)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);	//zielony
	}
}

// Lewa strza³ka
void LeftMark()
{
	cout << "\t\t\t\t->";
}

// Prawa strza³ka
void RightMark()
{
	cout << "<-\n";
}




/*
*
	ZARZ¥DZANIE WÊ¯EM
*
*/


// UTWÓRZ WÊ¯A
void CreateSnake()
{
	int rozmiar = 3; //Ustaw rozmiar pocz¹tkowy wê¿a
	int item_count = 0;
	int punkty = 0;
	int snakeX[100], snakeY[100], tempX[100], tempY[100];
	


	system("cls");
	InitializeSnake(rozmiar, snakeX, snakeY);
	BuildBoard();
	MoveWithSnake(rozmiar, snakeX, snakeY, tempX, tempY, item_count, punkty);

	_getch();
}


// INICJALIZACJA WÊ¯A
void InitializeSnake(int rozmiar, int snakeX[], int snakeY[])
{
	//Wymiarowanie Wê¿a
	snakeX[0] = WIDTH / 2;	snakeY[0] = 3;
	snakeX[1] = WIDTH / 2;	snakeY[1] = 2;
	snakeX[2] = WIDTH / 2;	snakeY[2] = 1;

	for (int i = 3; i < 100; i++)
	{
		snakeX[i] = NULL;
		snakeY[i] = NULL;
	}

	// Umieszczenie Wê¿a na planszy
	for (int i = 0; i < rozmiar; i++)
		Level[snakeY[i]][snakeX[i]] = 'o';
}

// ZARZ¥DZANIE WÊ¯EM
void MoveWithSnake(int& rozmiar, int snakeX[], int snakeY[], int tempX[], int tempY[], int& item_count, int& punkty)
{
	int count = 0;
	char input = ' ';
	char previnput = 's';
	int tailX, tailY;
	bool gameOver = false;
	vector<int> itemX, itemY;


	
	//G£ÓWNA PÊTLA GRY
	while (!gameOver) 
	{


		// Prêdkoœæ Wê¿a
		SetSnakeSpeed();


		// Dodawanie œladów ogona
		tailY = snakeY[rozmiar - 1];
		tailX = snakeX[rozmiar - 1];


		// Usuwanie œladów po ogonie
		Level[tailY][tailX] = ' ';
		FeedingSnake(itemX, itemY, item_count, snakeX, snakeY, rozmiar, tailX, tailY, punkty);


		// Kopiowanie Wê¿a do tablicy temp
		for (int i = 0; i < rozmiar - 1; i++)
		{
			tempX[i + 1] = snakeX[i];						// Kopiowanie wartoœci y
			tempY[i + 1] = snakeY[i];						// Kopiowanie wartoœci x
		}


		// Kopiowanie g³owy Wê¿a
		tempX[0] = snakeX[0];
		tempY[0] = snakeY[0];


		// Kopiowanie z tablicy temp
		for (int i = 0; i < rozmiar; i++)
		{
			snakeX[i] = tempX[i];						// Kopiowanie wartoœci Y
			snakeY[i] = tempY[i];						// Kopiowanie wartoœci X
		}

		// Pobranie klawisza
		if (_kbhit())
			input = _getch();



		//PORUSZANIE
			// WHILE MOVING DOWN
			if (previnput == 's')
			{
				snakeY[0] += 1;								// Zestaw g³ów na nowej pozycji
				if (input == 'a' || input == 'A')			// IdŸ w lewo
					previnput = 'a';
				else if (input == 'd' || input == 'D')	// IdŸ w prawo
					previnput = 'd';
			}
			// WHILE MOVING UP
			else if (previnput == 'w')
			{
				snakeY[0] -= 1;								// Zestaw g³ów na nowej pozycji
				if (input == 'a' || input == 'A')		// IdŸ w lewo
					previnput = 'a';
				else if (input == 'd' || input == 'D')	// IdŸ w prawo
					previnput = 'd';
			}
			// WHILE MOVING RIGHT
			else if (previnput == 'd')
			{
				snakeX[0] += 1;								// Zestaw g³ów na nowej pozycji
				if (input == 'w' || input == 'W')		// IdŸ w górê
					previnput = 'w';
				else if (input == 's' || input == 'S')	// IdŸ w dó³
					previnput = 's';
			}
			// WHILE MOVING LEFT
			else if (previnput == 'a')
			{
				snakeX[0] -= 1;
				if (input == 'w' || input == 'W')			// IdŸ w góre
					previnput = 'w';
				else if (input == 's' || input == 'S')	// IdŸ w dó³
					previnput = 's';
			}



		// Pauza gry
		if (input == 'p' || input == 'P')
			_getch();


		// Rysowanie i zmiana pozycji Wê¿a		
		for (int i = 0; i < rozmiar; i++)
			Level[snakeY[i]][snakeX[i]] = 'o';


		// Czy gra siê skoñczy³a?
		gameOver = IsGameOver(tempX, tempY, rozmiar);
		if (gameOver == true)
		{
			cout << "\a\a";
			break;
		}

		Punktacja[Punktacja.size() - 1] = punkty;

		// Aktualizowanie planszy
		ClearScreen();
		DrawBoard();
	}

	
}

//USTAW PRÊDKOŒÆ WÊ¯A
void SetSnakeSpeed()
{
	if (n == 1)
	{
		Sleep(100);
		cout << endl << "   EASY";
	}
	else if (n == 2)
	{
		Sleep(50);
		cout << endl << "   MEDIUM";
	}
	else if (n == 3)
	{
		Sleep(15);
		cout << endl << "   HARD";
	}

}

//NAKARM WÊ¯A
void FeedingSnake(vector<int>& itemX, vector<int>& itemY, int& item_count, int snakeX[], int snakeY[], int& rozmiar, int tailX, int tailY, int& punkty)
{
	clock_t interval = clock() % 4000;
	cout << "\t\t	Your Score: " << punkty << endl;

	// Poka¿ przedmioty w odstêpach czasu

	if (interval > 2800)
	{
		item_count++;
		srand((unsigned)time(NULL));

		// Pozycje znajduj¹ siê w przypadkowych miejscach
		itemX.push_back(rand() % (WIDTH - 2) + 1);
		itemY.push_back(rand() % (HEIGHT - 2) + 1);
		Level[itemY.back()][itemX.back()] = 'S';
	}

	// SprawdŸ pozycje
	for (int i = 0; i < item_count; i++)
	{
		if ((snakeX[0] == itemX.at(i)) && (snakeY[0] == itemY.at(i)))
		{

			//Dodawanie punktów
			punkty += 100;

			// Usuwanie pozycji
			item_count--;
			itemY.erase(itemY.begin() + 1);
			itemX.erase(itemX.begin() + 1);

			// W¹¿ roœnie
			rozmiar++;
			snakeX[rozmiar - 1] = tailX;
			snakeY[rozmiar - 1] = tailY;
			cout << "\a";
		}
	}
}





/*
*
	KONIEC GRY
*
*/


// WARUNKI KOÑCA GRY
bool IsGameOver(int snakeX[], int snakeY[], int rozmiar)
{

	// Zjedzenie w³asnego ogona
	for (int i = 2; i < rozmiar; i++)
	{
		if ((snakeX[0] == snakeX[i]) && (snakeY[0] == snakeY[i]))
		{
			cout << endl << "\t\t	GAME OVER!";
			_getch();
			Sleep(2000);
			GameOver();
			return true;
		}
	}

	//Wpadniêcie na obramowanie planszy
	if ((snakeX[0] == WIDTH - 1) || (snakeY[0] == HEIGHT - 1) || (snakeX[0] == 0) || (snakeY[0] == 0))
	{
		cout << endl << "\t\t	GAME OVER!";
		Sleep(2000);
		_getch();
		GameOver();
		return true;
	}
	else
		return false;
}

// KONIEC GRY I MO¯LIWOŒÆ ZAGRANIA PONOWNIE
void GameOver()
{
	while (1)
	{
		system("cls");
		DisplayWhite();

		printf("\n\n\n\n\t\t\t      GAME OVER\n\n\n\t\t\t   WANT TO PLAY AGAIN?\n");
		if (x == 1) { DisplayRed();LeftMark();printf(" YES ");RightMark(); }
		if (x == 1) { DisplayWhite();printf("\t\t\t\t  NO\n"); }
		if (x == 2) { DisplayWhite(); printf("\t\t\t\t  YES\n"); }
		if (x == 2) { DisplayRed();LeftMark();printf(" NO ");RightMark(); }
		z = _getch();

		if (z == 72) { if (x > 1) { x--; } }
		if (z == 80) { if (x < 2) { x++; } }
		if ((z == 13) && (x == 2))  exit(1);
		if ((z == 13) && (x == 1))  Scoreboard();
	}
}


