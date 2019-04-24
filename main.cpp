//allows "unsafe" functions like sprintf
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "conio2.h"
#include <string.h>

//state of closed function (success)
#define GAME_END 0
//state of closed function (success)
#define EXIT_SUCCESS 0
//state of closed function (failure)
#define EXIT_FAILURE 1
//state of closed function (failure)
#define EXIT_FILE_OPEN_FAILURE 2
//state of closed function (failure)
#define EXIT_MEMORY_ALLOCATION_FAILURE 3
//number of letters' kinds
#define LETTERS_AMOUNT 27
//value of first alphabet letter
#define LETTER_INDEX_EXCHANGE 'A'
//legend's width
#define LEGEND_WIDTH 30
//legend's height
#define LEGEND_HEIGHT 25
//legend's x offset
#define LEGEND_X_OFFSET 1
//legend's y offset
#define LEGEND_Y_OFFSET 1
//defines window layout
#define WINDOW_LAYOUT 0
//defines spacing
#define WINDOW_LAYOUT_SPACING 5
//board's width
#define BOARD_WIDTH 15
//board's x offset
#define BOARD_X_OFFSET 1
//board's y offset
#define BOARD_Y_OFFSET 5
//letters x offset
#define LETTERS_X_OFFSET 15
//letters y offset
#define LETTERS_Y_OFFSET 35
//insert x offset
#define INSERT_X_OFFSET 15
//insert y offset
#define INSERT_Y_OFFSET 40
//message x offset
#define MESSAGE_X_OFFSET 15
//message y offset
#define MESSAGE_Y_OFFSET 45
//message line characters
#define MAX_INLINE_LETTERS 50
//multiplier max letters
#define MAX_MULTIPLIER_LETTERS 10
//word legend x offset
#define WORD_LEGEND_X_OFFSET 15
//word legend y offset
#define WORD_LEGEND_Y_OFFSET 50
//points x offset
#define POINTS_X_OFFSET 40
//points y offset
#define POINTS_Y_OFFSET 35
//two bytes char boolean flag
#define IS_ARROW_KEY 0
//arrow key code
#define ARROW_UP 0x48
//arrow key code
#define ARROW_DOWN 0x50
//arrow key code
#define ARROW_LEFT 0x4b
//arrow key code
#define ARROW_RIGHT 0x4d
//escape character
#define ESCAPE_KEY 'q'
//new game character
#define NEW_GAME_KEY 'n'
//tutorial mode key
#define TUTORIAL_MODE_KEY 't'
//insert key
#define INSERT_WORD_KEY 'i'
//insert cancel key
#define INSERT_CANCEL_KEY 0x1b
//insert accept key
#define INSERT_ACCEPT_KEY 0x0d
//insert delete key
#define INSERT_DELETE_KEY 0x08
//rotate key
#define INSERT_ROTATE_KEY 'o'
//exchange key
#define EXCHANGE_START_KEY 'w'
//exchange accept key
#define EXCHANGE_ACCEPT_KEY 0x0d
//exchange cancel key
#define EXCHANGE_CANCEL_KEY 0x1b
//exchange minimum range
#define EXCHANGE_MIN_RANGE_KEY 0x31
//exchange maximum range
#define EXCHANGE_MAX_RANGE_KEY 0x37
//save start key
#define SAVE_START_KEY 's'
//save accept key
#define SAVE_ACCEPT_KEY 0x0d
//save delete key
#define SAVE_DELETE_KEY 0x08
//save cancel key
#define SAVE_CANCEL_KEY 0x1b
//save override yes
#define SAVE_OVERRIDE_YES 'y'
//save override no
#define SAVE_OVERRIDE_NO 'n'
//load start key
#define LOAD_START_KEY 'l'
//load accept key
#define LOAD_ACCEPT_KEY 0x0d
//load delete key
#define LOAD_DELETE_KEY 0x08
//load cancel key
#define LOAD_CANCEL_KEY 0x1b
//path max letters
#define PATH_MAX_LETTERS 40
//maximum number of players' letters
#define PLAYER_LETTERS_AMOUNT 7
//maximum number of players
#define PLAYER_PLAYERS_AMOUNT 2
//null character
#define NULL_CHARACTER '\0'
//empty character
#define EMPTY_CHARACTER ' '
//empty character save placeholder
#define EMPTY_CHARACTER_SAVE '/'
//exchange upper-lower value
#define EXCHANGE_UPPERLOWER_VALUE 32
//player id
#define PLAYER_ID 0
//ai id
#define AI_ID 1
//dictionary index
#define DICTIONARY_ARGUMENT_INDEX 1
//default dictionary path
#define DICTIONARY_PATH_DEFAULT "dictionarydefault.txt"
//max word length
#define DICTIONARY_WORD_MAX_LENGTH 80
//blank letters amounts
#define BLANK_LETTERS_AMOUNT 2
//maximum space for score
#define SCORE_MAX_LETTERS 4
//points exchange start value
#define SCORE_EXCHANGE_VALUE 0x30
//debug value
#define SCORE_DEBUG_VALUE ':'
//xOrigin
#define XORIGIN (BOARD_X_OFFSET + ((1 + WINDOW_LAYOUT) % 2) * (LEGEND_WIDTH + LEGEND_X_OFFSET + WINDOW_LAYOUT_SPACING) + 1)
//yOrigin
#define YORIGIN (BOARD_Y_OFFSET + 1)

//kind of board's field
enum FieldType
{
	ws3 = RED,
	ws2 = LIGHTMAGENTA,
	ls3 = BLUE,
	ls2 = LIGHTBLUE,
	start = MAGENTA,
	nothing = WHITE
};

//multipliers of fields
enum FieldValue
{
	vws3 = 3,
	vws2 = 2,
	vls3 = 3,
	vls2 = 2
};

//RBT colors
enum Color
{
	black,
	red
};

//single dictionary node
struct Node
{
	char *word;
	int points;

	Color color;
	Node *parent;
	Node *left;
	Node *right;
};

//board data container
struct Board
{
	FieldType fields[BOARD_WIDTH][BOARD_WIDTH];
	char letters[BOARD_WIDTH][BOARD_WIDTH];
};

struct Player
{
	bool selected[PLAYER_LETTERS_AMOUNT];
	char letters[PLAYER_LETTERS_AMOUNT];
	int lettersAmount[LETTERS_AMOUNT];
	int points;
};

//main data container
struct GameHandler
{
	bool init;
	bool firstWord;
	int letters[LETTERS_AMOUNT];
	Board board;
	Player players[PLAYER_PLAYERS_AMOUNT];
	Node *dictionary;
	char *dictionaryPath;
	unsigned int seed;
	long int randomID;
	bool AIinclude;
	bool tutorial;
};

//in-game amount of each letter
enum LetterAmount
{
	la_A = 9,
	la_B = 2,
	la_C = 2,
	la_D = 4,
	la_E = 12,
	la_F = 2,
	la_G = 3,
	la_H = 2,
	la_I = 9,
	la_J = 1,
	la_K = 1,
	la_L = 4,
	la_M = 2,
	la_N = 6,
	la_O = 9,
	la_Q = 1,
	la_P = 2,
	la_R = 6,
	la_S = 4,
	la_T = 6,
	la_U = 4,
	la_V = 2,
	la_W = 2,
	la_X = 1,
	la_Y = 2,
	la_Z = 1,
	la_PUSTY = BLANK_LETTERS_AMOUNT
};

//points of each letter
enum LetterPoints
{
	lp_A = 1,
	lp_B = 3,
	lp_C = 3,
	lp_D = 2,
	lp_E = 1,
	lp_F = 4,
	lp_G = 2,
	lp_H = 4,
	lp_I = 1,
	lp_J = 8,
	lp_K = 5,
	lp_L = 1,
	lp_M = 3,
	lp_N = 1,
	lp_O = 1,
	lp_Q = 10,
	lp_P = 3,
	lp_R = 1,
	lp_S = 1,
	lp_T = 1,
	lp_U = 1,
	lp_V = 4,
	lp_W = 4,
	lp_X = 8,
	lp_Y = 4,
	lp_Z = 10
};

//kinds of frames
enum FrameKind
{
	solid = 1,
	dashed = 2
};

//initialization of game
void GameStart(GameHandler &gameHandler);
//initalization of gamehandler start values
GameHandler GameHandlerInit(const char *path = "");
//closes game
void GameClose(GameHandler &gameHandler);
//grants points to a PLAYER
void GrantPoints(GameHandler &gameHandler, const char *word, bool vertical, bool player = true);
//prints legend
void PrintLegend(const GameHandler &gameHandler);
//prints coordinates (arguments sets coords position)
void PrintCoords(int xBack, int yBack, int x = -1, int y = -1);
//prints board WIDTH per HEIGHT in (X,Y) position
void PrintBoard(GameHandler gameHandler);
//prints frame WIDTH per HEIGHT in current cursor's postition
void PrintFrame(int width, int height, FrameKind frameKind);
//prints player's letters
void PrintPlayerLetters(Player player);
//prints word in legend
void PrintWordLegend(const char *word, const char *letters);
//prints a message String
void PrintMessage(const char *msg);
//prints actual score
void PrintPoints(const GameHandler gameHandler);
//prints word value (tutorial)
void PrintWordValue(const char* word);
//clear word value (tutorial)
void ClearWordValue();
//clears word in legend
void ClearWordLegend();
//clears message
void ClearMessage();
//loads dictionary
void DictionaryLoad(GameHandler &gameHandler);
//closes dictionary
void DictionaryClose(GameHandler &gameHandler);
//inserts a node
void DictionaryInsert(GameHandler &gameHandler, Node *word);
//fixes double black
void FixDoubleBlack(Node *&root, Node *&node);
//fixes red red
void FixRedRed(Node *&root, Node *&node);
//return replacing node
Node * RBTreeReplace(Node *deleted);
//dictionary transform
void NodeLeftRotate(Node *&root, Node *&node);
//dictionary transform
void NodeRightRotate(Node *&root, Node *&node);
//return sibling
Node * Sibling(Node *node);
//return uncle
Node * Uncle(Node *node);
//compares two word
//returns 1 if A>B
//returns 0 if A==B
//returns -1 if A<B
int WordCompare(const char *A, const char *B);
//looks for a word in dictionary
//return true if dictionary contains WORD
//false if not
bool FindWord(const Node *dictionary, const char *word);
//looks for a NODE in dictionary
//return NODE if dictionary contains WORD
//NULL if not
Node * FindNode(Node *dictionary, const char *word);
//inserts WORD on the game board
//returns true if turn is ended
//false if not
int InsertWord(const char *word, GameHandler &gameHandler);
//clears space around board
void ClearOffBoard();
//returns C amount
int GetLetterAmount(char c = '/');
//returns C points
int GetLetterPoints(char c = '/');
//return c-string length
int GetStringLength(const char *string);
//returns absolute of X
int Absolute(int x);
//initializate Player
Player PlayerInit(GameHandler &gameHandler, bool human = true);
//return random value in range [0-RANGE]
int Random(int range, GameHandler &gameHandler);
//return upper case letter
char UpperCase(char c);
//draws letters
void DrawLetters(GameHandler &gameHandler, bool human = true);
//returns a random letter
char GetRandomLetter(GameHandler &gameHandler);
//exchanges letters (input-function)
//return true if turn is ended
//false if not
bool Exchange(GameHandler &gameHandler);
//exchanges letters
void ExchangeLetters(GameHandler &gameHandler, bool human = true);
//saves game data
void SaveGame(const GameHandler &gameHandler);
//loads game data
void LoadGame(GameHandler &gameHandler);
//AI turn
void AITurn(GameHandler &gameHandler);
//Creates word (AI turn)
bool CreateWord(const GameHandler &gameHandler, char *&word);
//checks if word fits a board (AI turn)
bool CheckFit(const GameHandler &gameHandler, int x, int y, int lettersCount, char *wordletters, bool vertical);
//checks if word exsists in dictionary
bool CheckWord(const GameHandler &gameHandler, int x, int y, const char* wordLetters, const char* aiLetters, char *&word, int &points, bool vertical);
//saves permutations (AI Turn)
void Permutation(FILE *permutations, char *base, char *perm, int lengthBase, int lengthPerm);
//doing permutations
void DoPermutations(char *letters);


//determines AI player is allowed to play
#define AI_INCLUDE 1


int main(int argc, char *argv[])
{

	// if the program is compiled in pure C, then we need to initialize
	// the library ourselves; __cplusplus is defined only if a C++ compiler
	// is used

	#ifndef __cplusplus
		Conio2_Init();
	#endif

	char c;


	//defines main data container
	GameHandler gameHandler = GameHandlerInit();
	gameHandler.init = false;
	
	GameStart(gameHandler);

	int x = XORIGIN;
	int y = YORIGIN;

	char buffer[BOARD_WIDTH + 1];

	do
	{
		
		//goto top-left corner of a board;
		gotoxy(x, y);

		textbackground(GREEN);
		textcolor(BLACK);
		putch(gameHandler.board.letters[wherex() - XORIGIN][wherey() - YORIGIN]);

		gotoxy(x, y);

		// we wait for key press and get its code
		// most key codes correspond to the characters, like
		// a is 'a', 2 is '2', + is '+', but some special keys
		// like cursors provide two characters, where the first
		// one is zero, e.g., "up arrow" is zero and 'H'
		c = getch();

		// we do not want the key 'H' to play role of "up arrow"
		// so we check if the first code is zero
		if (c == IS_ARROW_KEY)
		{
			textbackground(gameHandler.board.fields[wherex() - XORIGIN][wherey() - YORIGIN]);
			putch(gameHandler.board.letters[wherex() - XORIGIN][wherey() - YORIGIN]);

			c = getch();		// the next code knowing that this will be a special key
			if		(c == ARROW_UP && y > YORIGIN)					    y--;
			else if (c == ARROW_DOWN && y < YORIGIN + BOARD_WIDTH - 1)  y++;
			else if (c == ARROW_LEFT && x > XORIGIN)				    x--;
			else if (c == ARROW_RIGHT && x < XORIGIN + BOARD_WIDTH - 1) x++;

			PrintCoords(x, y);
		}
		else if (c == NEW_GAME_KEY)
		{
			DictionaryClose(gameHandler);
			gameHandler = GameHandlerInit();
			GameStart(gameHandler);
			x = XORIGIN;
			y = YORIGIN;
		}
		else if (c == INSERT_WORD_KEY)
		{
			int index = 0;

			buffer[0] = NULL_CHARACTER;

			PrintWordLegend(buffer, gameHandler.players[PLAYER_ID].letters);

			while ((c = getch()) != INSERT_CANCEL_KEY)
			{
				if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) && (GetStringLength(buffer) < BOARD_WIDTH))
				{
					buffer[index] = UpperCase(c);
					buffer[index + 1] = NULL_CHARACTER;
					PrintWordLegend(buffer, gameHandler.players[PLAYER_ID].letters);

					index++;

					if (gameHandler.tutorial == true)
					{
						if (FindWord(gameHandler.dictionary, buffer) == true)
						{
							PrintMessage("Dictionary contains this word.");
						}
						else
						{
							PrintMessage("Dictionary does not contain this word.");
						}
					}
				}
				else if (c == INSERT_DELETE_KEY)
				{
					if (index > 0)
					{
						buffer[index - 1] = NULL_CHARACTER;
						PrintWordLegend(buffer, gameHandler.players[PLAYER_ID].letters);

						index--;
					}

					if (gameHandler.tutorial == true)
					{
						if (FindWord(gameHandler.dictionary, buffer) == true)
						{
							PrintMessage("Dictionary contains this word.");
						}
						else
						{
							PrintMessage("Dictionary does not contain this word.");
						}
					}
				}
				else if (c == INSERT_ACCEPT_KEY)
				{
					ClearWordLegend();

					if (FindWord(gameHandler.dictionary, buffer) == true)
					{
						int result = InsertWord(buffer, gameHandler);
						
						ClearOffBoard();
						PrintLegend(gameHandler);
						PrintBoard(gameHandler);

						if (result == 1)
						{
							if (gameHandler.AIinclude)
							{
								AITurn(gameHandler);
							}

							DrawLetters(gameHandler);
							PrintPlayerLetters(gameHandler.players[PLAYER_ID]);
						}
						else if (result == -1)
						{
							PrintMessage("Wrong move! Turn lost!");

							if (gameHandler.AIinclude)
							{
								AITurn(gameHandler);
							}
						}
					}
					else
					{
						PrintMessage("Typed word is incorrect");
						if (gameHandler.AIinclude)
						{
							AITurn(gameHandler);
						}
					}

					ungetch(INSERT_CANCEL_KEY);
				}
			}
			ClearWordLegend();
		}
		else if (c == EXCHANGE_START_KEY)
		{
			PrintMessage("Exchange in progress...");

			if (Exchange(gameHandler) == true)
			{
				PrintPlayerLetters(gameHandler.players[PLAYER_ID]);

				if (gameHandler.AIinclude)
				{
					AITurn(gameHandler);
				}
			}
			else
			{
				PrintPlayerLetters(gameHandler.players[PLAYER_ID]);
			}

			ClearMessage();
		}
		else if (c == SAVE_START_KEY)
		{
			SaveGame(gameHandler);
		}
		else if (c == LOAD_START_KEY)
		{
			LoadGame(gameHandler);

			srand(gameHandler.seed);

			for (int i = 0; i < gameHandler.randomID; i++)
			{
				rand();
			}

			GameStart(gameHandler);
		}
		else if (c == TUTORIAL_MODE_KEY)
		{
			gameHandler.tutorial = !gameHandler.tutorial;
			PrintLegend(gameHandler);
		}
	}
	while (c != ESCAPE_KEY);

	GameClose(gameHandler);
	
	return EXIT_SUCCESS;
}

//starts a game
void GameStart(GameHandler &gameHandler)
{
	//if a new game
	if (gameHandler.init == false)
	{
		textmode(C4350);

		// settitle sets the window title
		settitle("Scrabble");

		// hide the blinking cursor
		_setcursortype(_NOCURSOR);

		gameHandler.init = true;
	}

	// we set black to be the background color
	// check conio2.h for available colors
	textbackground(BLACK);
	// clear the screen: we fill it out with spaces with
	// the specified background color
	clrscr();
	// we set the text color (7 == LIGHTGRAY)
	textcolor(LIGHTGRAY);

	PrintLegend(gameHandler);
	PrintBoard(gameHandler);
	PrintPlayerLetters(gameHandler.players[PLAYER_ID]);
	PrintPoints(gameHandler);
	DictionaryLoad(gameHandler);
}

GameHandler GameHandlerInit(const char *path)
{
	GameHandler gameHandler;
	gameHandler.init = true;
	gameHandler.firstWord = true;
	gameHandler.tutorial = false;
	gameHandler.seed = (unsigned int)time(NULL);
	gameHandler.randomID = 0;
	gameHandler.AIinclude = AI_INCLUDE;

	srand(gameHandler.seed);

	if (GetStringLength(path) == 0)
	{
		int length;

		if (__argc > 1)
			gameHandler.dictionaryPath = __argv[DICTIONARY_ARGUMENT_INDEX];
		else
		{
			length = GetStringLength(DICTIONARY_PATH_DEFAULT);
			gameHandler.dictionaryPath = (char *)malloc(length + 1);


			const char* temp = DICTIONARY_PATH_DEFAULT;
			for (int i = 0; *(temp + i) != NULL_CHARACTER; i++)
			{
				*(gameHandler.dictionaryPath + i) = *(temp + i);
			}
			*(gameHandler.dictionaryPath + length) = NULL_CHARACTER;
		}


		for (char c = 'A'; c <= 'Z' + 1; c++)
		{
			gameHandler.letters[(int)c - LETTER_INDEX_EXCHANGE] = GetLetterAmount(c);
		}

		Board board;

		int offset = (BOARD_WIDTH / 2) / 2;

		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			for (int y = 0; y < BOARD_WIDTH; y++)
			{
				board.fields[x][y] = FieldType::nothing;
			}
		}

		//fields and letters initialization
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			for (int y = 0; y < BOARD_WIDTH; y++)
			{
				board.letters[x][y] = EMPTY_CHARACTER;

				if (x == y || x == (BOARD_WIDTH - 1 - y))
				{
					if (x == 0 || x == BOARD_WIDTH - 1)
					{
						board.fields[x][y] = FieldType::ws3;
					}
					else if (x == BOARD_WIDTH / 2 - 1 || x == BOARD_WIDTH / 2 + 1)
					{
						board.fields[x][y] = FieldType::ls2;
					}
					else if (x == BOARD_WIDTH / 2 - 2 || x == BOARD_WIDTH / 2 + 2)
					{
						board.fields[x][y] = FieldType::ls3;
					}
					else if (x == BOARD_WIDTH / 2)
					{
						board.fields[x][y] = FieldType::start;
					}
					else if (offset > 1)
					{
						board.fields[x][y] = FieldType::ws2;
					}
				}
				else if (x == offset || x == BOARD_WIDTH - 1 - offset)
				{
					if (y % (BOARD_WIDTH / 2) == 0)
					{
						if (offset > 1)
						{
							board.fields[x][y] = FieldType::ls2;
							if (x == BOARD_WIDTH / 2 || y == BOARD_WIDTH / 2)
							{
								if (x > y)
								{
									board.fields[x + 1][y - 1] = FieldType::ls2;
									board.fields[x + 2][y - 2] = FieldType::ls3;
								}
								if (x < y)
								{
									board.fields[x - 1][y + 1] = FieldType::ls2;
									board.fields[x - 2][y + 2] = FieldType::ls3;
								}
								if (x > BOARD_WIDTH / 2 || y > BOARD_WIDTH / 2)
								{
									board.fields[x + 1][y + 1] = FieldType::ls2;
									board.fields[x + 2][y + 2] = FieldType::ls3;
								}
								if (x < BOARD_WIDTH / 2 || y < BOARD_WIDTH / 2)
								{
									board.fields[x - 1][y - 1] = FieldType::ls2;
									board.fields[x - 2][y - 2] = FieldType::ls3;
								}
							}
						}
					}
				}
				else if (y == offset || y == BOARD_WIDTH - 1 - offset)
				{
					if (x % (BOARD_WIDTH / 2) == 0)
					{
						if (offset > 1)
						{
							board.fields[x][y] = FieldType::ls2;
							if (x == BOARD_WIDTH / 2 || y == BOARD_WIDTH / 2)
							{
								if (x > y)
								{
									board.fields[x + 1][y - 1] = FieldType::ls2;
									board.fields[x + 2][y - 2] = FieldType::ls3;
								}
								if (x < y)
								{
									board.fields[x - 1][y + 1] = FieldType::ls2;
									board.fields[x - 2][y + 2] = FieldType::ls3;
								}
								if (x > BOARD_WIDTH / 2 || y > BOARD_WIDTH / 2)
								{
									board.fields[x + 1][y + 1] = FieldType::ls2;
									board.fields[x + 2][y + 2] = FieldType::ls3;
								}
								if (x < BOARD_WIDTH / 2 || y < BOARD_WIDTH / 2)
								{
									board.fields[x - 1][y - 1] = FieldType::ls2;
									board.fields[x - 2][y - 2] = FieldType::ls3;
								}
							}
						}
					}
				}
				else if (x == BOARD_WIDTH / 2 || y == BOARD_WIDTH / 2)
				{
					if (x != y)
					{
						if (x == 0 || y == 0 || x == BOARD_WIDTH - 1 || y == BOARD_WIDTH - 1)
						{
							board.fields[x][y] = FieldType::ws3;
						}
					}
				}
			}
		}

		gameHandler.board = board;

		//defines human player
		gameHandler.players[PLAYER_ID] = PlayerInit(gameHandler);

		if (gameHandler.AIinclude)
		{
			gameHandler.players[AI_ID] = PlayerInit(gameHandler);
		}

	}
	else
	{
		//load
	}

	return gameHandler;
}

void PrintLegend(const GameHandler &gameHandler)
{
	//legend's x and y coordinates (x changes depending on board total width and window layout)
	int x = LEGEND_X_OFFSET + WINDOW_LAYOUT * (BOARD_WIDTH + BOARD_X_OFFSET + WINDOW_LAYOUT_SPACING);
	int y = LEGEND_Y_OFFSET;

	gotoxy(x, y);

	textbackground(BLACK);
	textcolor(WHITE);

	//printing frame
	PrintFrame(LEGEND_WIDTH, LEGEND_HEIGHT, FrameKind::dashed);

	//printing controls
	gotoxy(x + 2, y + 2);
	cputs("q       = exit");
	gotoxy(x + 2, y + 3);
	cputs("cursors = moving");
	gotoxy(x + 2, y + 4);
	cputs("n       = new game");
	gotoxy(x + 2, y + 5);
	cputs("enter   = cofnirm");
	gotoxy(x + 2, y + 6);
	cputs("esc     = cancel");
	gotoxy(x + 2, y + 7);
	cputs("i       = insert");
	gotoxy(x + 2, y + 8);
	cputs("backspc = delete");
	gotoxy(x + 2, y + 9);
	cputs("o       = rotate");
	gotoxy(x + 2, y + 10);
	cputs("w       = exchange");
	gotoxy(x + 2, y + 11);
	cputs("[1]-[7] = select");
	gotoxy(x + 2, y + 12);
	cputs("s       = save");
	gotoxy(x + 2, y + 13);
	cputs("l       = load");
	gotoxy(x + 2, y + 14);
	cputs("t       = tutorial");
	gotoxy(x + 2, y + 15);
	cputs("------------------------");
	gotoxy(x + 2, y + 16);
	cputs("Daniel Szynszecki 175683");
	gotoxy(x + 2, y + 17);
	cputs("a b c d f g h i j m");

	//cursor

	gotoxy(x + 2, y + 20);
	cputs("------------------------");
	gotoxy(x + 2, y + 21);
	cputs("tutorial mode ");
	if (gameHandler.tutorial == true)
	{
		textcolor(GREEN);
		cputs("ON ");
	}
	else
	{
		textcolor(RED);
		cputs("OFF");
	}

	textcolor(WHITE);

	gotoxy(x + 2, y + 22);
	cputs("AI ");
	if (gameHandler.AIinclude == true)
	{
		textcolor(GREEN);
		cputs("ON ");
	}
	else
	{
		textcolor(RED);
		cputs("OFF");
	}

	textcolor(WHITE);

	PrintCoords(BOARD_X_OFFSET + ((1 + WINDOW_LAYOUT) % 2) * (LEGEND_WIDTH + LEGEND_X_OFFSET + WINDOW_LAYOUT_SPACING) + 1, BOARD_Y_OFFSET + 1, x + 2, y + 18);
}

void PrintCoords(int xBack, int yBack, int xCoord, int yCoord)
{
	static int x;
	static int y;

	if (xCoord >= 0)
		x = xCoord;
	if (yCoord >= 0)
		y = yCoord;
	
	gotoxy(x, y);

	char sentence[] = "cursor: (A,A)";
	sentence[9] = 'A' + xBack - XORIGIN;
	sentence[11] = 'A' + yBack - YORIGIN;

	textbackground(BLACK);
	textcolor(WHITE);
	cputs(sentence);

	gotoxy(xBack, yBack);
}

void PrintBoard(GameHandler gameHandler)
{
	int xBack = wherex();
	int yBack = wherey();

	//board's x and y coordinates (x changes depending on legend total width and window layout)
	int x = BOARD_X_OFFSET + ((1 + WINDOW_LAYOUT) % 2) * (LEGEND_WIDTH + LEGEND_X_OFFSET + WINDOW_LAYOUT_SPACING);
	int y = BOARD_Y_OFFSET;

	gotoxy(x, y);
	//printing frame
	PrintFrame( BOARD_WIDTH + 2, BOARD_WIDTH + 2, FrameKind::solid);

	x++;
	y++;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			gotoxy(x + i, y + j);
			textbackground(gameHandler.board.fields[i][j]);
			putch(gameHandler.board.letters[i][j]);
		}
	}

	gotoxy(xBack, yBack);
}

void PrintFrame(int width, int height, FrameKind framekind)
{
	int xCoord = wherex();
	int yCoord = wherey();

	for (int y = yCoord; y < yCoord + height + 1; y += height - 1)
	{
		for (int x = xCoord; x < xCoord + width; x++)
		{
			gotoxy(x, y);

			if (framekind == FrameKind::solid)
			{
				textbackground(DARKGRAY);
				textcolor(BLACK);

				char c;

				if (x != xCoord && x != xCoord + width - 1)
					c = 'A' + x - xCoord - 1;
				else
					c = EMPTY_CHARACTER;

				putch(c);

			}
			else if(framekind == FrameKind::dashed)
				putch('-');
		}
	}

	for (int x = xCoord; x < xCoord + width + 1; x += width - 1)
	{
		for (int y = yCoord + 1; y < yCoord + height; y ++)
		{
			gotoxy(x, y);

			if (framekind == solid)
			{
				textbackground(DARKGRAY);
				textcolor(BLACK);

				char c;

				if (y != yCoord && y != yCoord + height - 1)
					c = 'A' + y - yCoord - 1;
				else
					c = EMPTY_CHARACTER;

				putch(c);

			}
			else if (framekind == dashed)
				putch('|');
		}
	}
}

void PrintPlayerLetters(Player player)
{
	int xBack = wherex();
	int yBack = wherey();

	gotoxy(LETTERS_X_OFFSET, LETTERS_Y_OFFSET);

	textbackground(BLACK);
	textcolor(WHITE);
	cputs("Player letters:");

	textcolor(BLACK);

	gotoxy(LETTERS_X_OFFSET, LETTERS_Y_OFFSET + 2);

	for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
	{
		if (player.selected[i] == false)
			textbackground(WHITE);
		else
			textbackground(YELLOW);

		putch(player.letters[i]);
		textbackground(BLACK);
		putch(EMPTY_CHARACTER);
	}

	gotoxy(xBack, yBack);
}

void PrintWordLegend(const char *word, const char *letters)
{
	ClearWordLegend();

	int xBack = wherex();
	int yBack = wherey();

	gotoxy(INSERT_X_OFFSET, INSERT_Y_OFFSET);

	textbackground(BLACK);
	textcolor(WHITE);
	cputs("Word:");

	textcolor(BLACK);

	gotoxy(INSERT_X_OFFSET, INSERT_Y_OFFSET + 2);

	int lettersAmount[LETTERS_AMOUNT] = { 0 };

	for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
	{
		int index;
		if (letters[i] != EMPTY_CHARACTER)
			index = letters[i] - 'A';
		else
			index = LETTERS_AMOUNT - 1;

		lettersAmount[index]++;
	}

	for (int i = 0; *(word + i) != NULL_CHARACTER; i++)
	{
		textbackground(RED);

		for (int j = 0; j < PLAYER_LETTERS_AMOUNT; j++)
		{
			if (*(word + i) == letters[j])
			{
				int index;
				if (letters[j] != EMPTY_CHARACTER)
					index = letters[j] - 'A';
				else
					index = LETTERS_AMOUNT - 1;

				if (lettersAmount[index] > 0)
				{
					lettersAmount[index]--;
					textbackground(GREEN);
				}
				break;
			}
		}

		putch(*(word + i));
	}

	gotoxy(xBack, yBack);
}

void PrintMessage(const char *msg)
{
	ClearMessage();

	int xBack = wherex();
	int yBack = wherey();

	textbackground(BLACK);
	textcolor(WHITE);

	gotoxy(MESSAGE_X_OFFSET, MESSAGE_Y_OFFSET);

	for (int i = 0; (*(msg + i) != NULL_CHARACTER && i<MAX_INLINE_LETTERS); i++)
	{
		putch(*(msg + i));
	}

	gotoxy(xBack, yBack);
}

void PrintPoints(const GameHandler gameHandler)
{
	int xBack = wherex();
	int yBack = wherey();

	gotoxy(POINTS_X_OFFSET, POINTS_Y_OFFSET);

	textbackground(BLACK);
	textcolor(WHITE);

	cputs("Player's score: ");

	char points[SCORE_MAX_LETTERS + 1];

	for (int i = 0; i < SCORE_MAX_LETTERS; i++)
	{
		points[i] = '0';
	}

	int temp = gameHandler.players[PLAYER_ID].points;

	int index = SCORE_MAX_LETTERS - 1;
	while (temp != 0)
	{
		points[index] = (char)(SCORE_EXCHANGE_VALUE + temp % 10);
		temp /= 10;
		index--;
	}

	points[SCORE_MAX_LETTERS] = NULL_CHARACTER;

	cputs(points);

	if (gameHandler.AIinclude == true)
	{

		gotoxy(POINTS_X_OFFSET, POINTS_Y_OFFSET + 1);

		cputs("AI's score: ");

		char points[SCORE_MAX_LETTERS + 1];

		for (int i = 0; i < SCORE_MAX_LETTERS; i++)
		{
			points[i] = '0';
		}

		temp = gameHandler.players[AI_ID].points;

		index = SCORE_MAX_LETTERS - 1;
		while (temp != 0)
		{
			points[index] = (char)(SCORE_EXCHANGE_VALUE + temp % 10);
			temp /= 10;
			index--;
		}

		points[SCORE_MAX_LETTERS] = NULL_CHARACTER;

		cputs(points);

	}

	gotoxy(xBack, yBack);
}

void PrintWordValue(const char* word)
{
	ClearWordValue();

	int xBack = wherex();
	int yBack = wherey();

	gotoxy(WORD_LEGEND_X_OFFSET, WORD_LEGEND_Y_OFFSET);

	textbackground(BLACK);
	textcolor(WHITE);

	for (int i = 0; *(word + i) != NULL_CHARACTER; i++)
	{
		putch(*(word + i));
	}

	gotoxy(xBack, yBack);
}

void ClearWordValue()
{
	int xBack = wherex();
	int yBack = wherey();

	gotoxy(WORD_LEGEND_X_OFFSET, WORD_LEGEND_Y_OFFSET);

	textbackground(BLACK);

	for (int i = 0; i < MAX_INLINE_LETTERS; i++)
	{
		putch(EMPTY_CHARACTER);
	}

	gotoxy(xBack, yBack);
}

void ClearWordLegend()
{
	int xBack = wherex();
	int yBack = wherey();

	for (int i = 0; i < 3; i+=2)
	{
		gotoxy(INSERT_X_OFFSET, INSERT_Y_OFFSET + i);

		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			textbackground(BLACK);
			putch(EMPTY_CHARACTER);
		}
	}

	gotoxy(xBack, yBack);
}

void ClearMessage()
{
	int xBack = wherex();
	int yBack = wherey();

	textbackground(BLACK);

	gotoxy(MESSAGE_X_OFFSET, MESSAGE_Y_OFFSET);

	for (int i = 0; i < MAX_INLINE_LETTERS; i++)
	{
		putch(EMPTY_CHARACTER);
	}

	gotoxy(xBack, yBack);
}

void DictionaryLoad(GameHandler &gameHandler)
{
	PrintMessage("Loading dictionary...");

	gameHandler.dictionary = NULL;

	FILE *file = fopen(gameHandler.dictionaryPath, "r");
	if (file == NULL)
	{
		exit(EXIT_FILE_OPEN_FAILURE);
	}

	char buffer[DICTIONARY_WORD_MAX_LENGTH];

	while (fscanf(file, "%s", buffer) != EOF)
	{
		if (GetStringLength(buffer) <= BOARD_WIDTH)
		{
			Node *word = (Node *)malloc(sizeof(Node));

			if (word == NULL)
				exit(EXIT_MEMORY_ALLOCATION_FAILURE);

			int length = GetStringLength(buffer);
			word->word = (char *)malloc(length + 1);

			if (word->word == NULL)
				exit(EXIT_MEMORY_ALLOCATION_FAILURE);

			word->points = 0;

			for (int i = 0; i < length; i++)
			{
				word->word[i] = buffer[i];
				word->points += GetLetterPoints(buffer[i]);
			}
			word->word[length] = NULL_CHARACTER;

			word->left = NULL;
			word->right = NULL;

			DictionaryInsert(gameHandler, word);
		}
	}

	fclose(file);
	PrintMessage("Done!");
}

void DictionaryClose(GameHandler &gameHandler)
{
	PrintMessage("Closing dictionary...");

	FILE *file = fopen(gameHandler.dictionaryPath, "r");
	if (file == NULL)
	{
		exit(EXIT_FILE_OPEN_FAILURE);
	}

	char buffer[DICTIONARY_WORD_MAX_LENGTH];
	Node *leaf;

	while (fscanf(file, "%s", buffer) != EOF)
	{
		leaf = FindNode(gameHandler.dictionary, buffer);

		Node *replace = RBTreeReplace(leaf);

		// True when REPLACE and LEAF are both black 
		bool bothBlack = ((replace == NULL || replace->color == Color::black) && (leaf->color == Color::black));

		Node *parent = leaf->parent;

		if (replace == NULL)
		{
			// REPLACE is NULL therefore LEAF is leaf 
			if (leaf == gameHandler.dictionary)
			{
				// LEAF is root, making root null 
				gameHandler.dictionary = NULL;
			}
			else
			{
				if (bothBlack)
				{
					FixDoubleBlack(gameHandler.dictionary, leaf);
				}
				else {
					// REPLACE or LEAF is red 
					if (Sibling(leaf) != NULL)
						// SIBLING is not null, make it red" 
						Sibling(leaf)->color = Color::red;
				}

				// delete LEAF from the tree 
				if (leaf->parent->left == leaf)
				{
					parent->left = NULL;
				}
				else
				{
					parent->right = NULL;
				}
			}
			
			free(leaf->word);
			free(leaf);

			return;
		}

		if (leaf->left == NULL || leaf->right == NULL)
		{
			// LEAF has 1 child 
			if (leaf == gameHandler.dictionary)
			{
				// LEAF is root, assign the value of REPLACE to LEAF, and delete REPLACE 

				free(leaf->word);
				leaf->word = (char *)malloc(GetStringLength(replace->word) + 1);

				for (int i = 0; i < GetStringLength(replace->word); i++)
				{
					leaf->word[i] = replace->word[i];
				}
				leaf->word[GetStringLength(leaf->word)] = NULL_CHARACTER;

				free(replace->word);
				free(replace);

				leaf->left = leaf->right = NULL;
			}
			else
			{
				// Detach LEAF from tree and move REPLACE up 
				if (leaf->parent->left == leaf)
				{
					parent->left = replace;
				}
				else
				{
					parent->right = replace;
				}

				free(leaf->word);
				free(leaf);

				replace->parent = parent;

				if (bothBlack) {
					// REPLACE and LEAF both black, fix double black at REPLACE 
					FixDoubleBlack(gameHandler.dictionary, replace);
				}
				else
				{
					// REPLACE or LEAF red, color REPLACE black 
					replace->color = Color::black;
				}
			}
			return;
		}

		// LEAF has 2 children, swap values with successor and recurse 
		
		free(leaf->word);
		leaf->word = (char *)malloc(GetStringLength(replace->word) + 1);

		for (int i = 0; i < GetStringLength(replace->word); i++)
		{
			leaf->word[i] = replace->word[i];
		}
		leaf->word[GetStringLength(leaf->word)] = NULL_CHARACTER;

		free(replace->word);
		free(replace);
	}

	fclose(file);
}

void DictionaryInsert(GameHandler &gameHandler, Node *word)
{
	if (gameHandler.dictionary == NULL)
	{
		gameHandler.dictionary = word;
		gameHandler.dictionary->parent = NULL;
		gameHandler.dictionary->left = NULL;
		gameHandler.dictionary->right = NULL;
		gameHandler.dictionary->color = Color::black;
	}
	else
	{
		//standard BST insert
		Node *leaf = gameHandler.dictionary;
		do
		{
			int result = WordCompare(word->word, leaf->word);

			if (result > 0)
			{
				if (leaf->right == NULL)
				{
					leaf->right = word;
					word->parent = leaf;
					leaf = leaf->right;
					break;
				}
					leaf = leaf->right;

			}
			else if (result < 0)
			{
				if (leaf->left == NULL)
				{
					leaf->left = word;
					word->parent = leaf;
					leaf = leaf->left;
					break;
				}
					leaf = leaf->left;
			}
			else
			{
				return;
			}

		} while (true);

		//normalization
		leaf->color = Color::red;

		FixRedRed(gameHandler.dictionary, leaf);
	}
}

void FixDoubleBlack(Node *&root, Node *&node)
{
	if (node == root)
		return;

	Node *sibling = Sibling(node);
	Node *parent = node->parent;
	if (sibling == NULL) {
		// No sibiling, double black pushed up 
		FixDoubleBlack(root, parent);
	}
	else
	{
		if (sibling->color == Color::red) {
			// Sibling red 
			parent->color = Color::red;
			sibling->color = Color::black;
			if (sibling->parent->left == sibling)
			{
				// left case 
				NodeRightRotate(root, parent);
			}
			else
			{
				// right case 
				NodeLeftRotate(root, parent);
			}
			FixDoubleBlack(root, node);
		}
		else
		{
			// Sibling black 
			if ((sibling->right != NULL && sibling->right->color == Color::red) || (sibling->left != NULL && sibling->left->color == Color::red))
			{
				// at least 1 red children 
				if (sibling->left != NULL && sibling->left->color == Color::red)
				{
					if (sibling->parent->left == sibling)
					{
						// left left 
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						NodeRightRotate(root, parent);
					}
					else
					{
						// right left 
						sibling->left->color = parent->color;
						NodeRightRotate(root, sibling);
						NodeLeftRotate(root, parent);
					}
				}
				else
				{
					if (sibling->parent->left == sibling)
					{
						// left right 
						sibling->right->color = parent->color;
						NodeLeftRotate(root, sibling);
						NodeRightRotate(root, parent);
					}
					else
					{
						// right right 
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						NodeLeftRotate(root, parent);
					}
				}
				parent->color = Color::black;
			}
			else
			{
				// 2 black children 
				sibling->color = Color::red;
				if (parent->color == Color::black)
					FixDoubleBlack(root, parent);
				else
					parent->color = Color::black;
			}
		}
	}
}

void FixRedRed(Node *&root, Node *&node)
{
	// if NODE is root color it black and return 
	if (node == root)
	{
		node->color = Color::black;
		return;
	}

	// initialize parent, grandparent, uncle 
	Node *parent = node->parent;
	Node *grandparent = parent->parent;

	Node *uncle = Uncle(node);

	if (parent->color != Color::black)
	{
		if (uncle != NULL && uncle->color == Color::red)
		{
			// uncle red, perform recoloring and recurse 
			parent->color = Color::black;
			uncle->color = Color::black;
			grandparent->color = Color::red;
			FixRedRed(root, grandparent);
		}
		else
		{
			// Else perform LR, LL, RL, RR 
			if (parent->parent->left == parent)
			{
				if (node->parent->left == node)
				{
					// for left right 
					Color temp = parent->color;
					parent->color = grandparent->color;
					grandparent->color = temp;
				}
				else
				{
					NodeLeftRotate(root, parent);

					Color temp = grandparent->color;
					grandparent->color = node->color;
					node->color = temp;
				}
				// for left left and left right 
				NodeRightRotate(root, grandparent);
			}
			else
			{
				if (node->parent->left == node)
				{
					// for right left 
					NodeRightRotate(root, parent);

					Color temp = grandparent->color;
					grandparent->color = node->color;
					node->color = temp;
				}
				else
				{
					Color temp = parent->color;
					parent->color = grandparent->color;
					grandparent->color = temp;
				}

				// for right right and right left 
				NodeLeftRotate(root, grandparent);
			}
		}
	}
}

Node * RBTreeReplace(Node *deleted)
{
	if (deleted->left != NULL && deleted->right != NULL)
	{
		Node *temp = deleted;

		while (temp->left != NULL)
		{
			temp = temp->left;
		}

		return temp;
	}

	// when leaf 
	if (deleted->left == NULL && deleted->right == NULL)
		return NULL;

	// when single child 
	if (deleted->left != NULL)
		return deleted->left;
	else
		return deleted->right;
}

void NodeLeftRotate(Node *&root, Node *&node)
{
	// RIGHT will be NODE's right child 
	Node *right = node->right;

	// update root if current node is root 
	if (node == root)
		root = right;

	if (node->parent != NULL)
	{
		if (node->parent->left == node)
		{
			node->parent->left = right;
		}
		else
		{
			node->parent->right = right;
		}
	}

	right->parent = node->parent;
	node->parent = right;

	// connect NODE with RIGHT's left element 
	node->right = right->left;
	// connect RIGHT's left element with NODE 
	// if it is not null 
	if (right->left != NULL)
		right->left->parent = node;

	// connect new parent with x 
	right->left = node;
}

void NodeRightRotate(Node *&root, Node *&node)
{
	// LEFT will be node's left child 
	Node *left = node->left;

	// update root if current node is root 
	if (node == root)
		root = left;

	if (node->parent != NULL)
	{
		if (node->parent->left == node)
		{
			node->parent->left = left;
		}
		else
		{
			node->parent->right = left;
		}
	}

	left->parent = node->parent;
	node->parent = left;

	// connect NODE with LEFT's right element 
	node->left = left->right;
	// connect LEFT's right element with NODE 
	// if it is not null 
	if (left->right != NULL)
		left->right->parent = node;

	// connect LEFT with NODE 
	left->right = node;
}

Node * Sibling(Node *node)
{
	// sibling null if no parent 
	if (node->parent == NULL)
		return NULL;

	if (node->parent->left == node)
		return node->parent->right;

	return node->parent->left;
}

Node * Uncle(Node *node)
{
	// If no parent or grandparent, then no uncle 
	if (node->parent == NULL || node->parent->parent == NULL)
		return NULL;

	if (node->parent->parent->left == node->parent)
		// uncle on right 
		return node->parent->parent->right;
	else
		// uncle on left 
		return node->parent->parent->left;
}

int WordCompare(const char *A, const char *B)
{
	int lengthA = GetStringLength(A);
	int lengthB = GetStringLength(B);

	int min = (lengthA < lengthB) ? lengthA : lengthB;

	for (int i = 0; i < min; i++)
	{
		if (A[i] > B[i])
			return 1;
		else if (A[i] < B[i])
			return -1;
	}
	return lengthA - lengthB;
}

bool FindWord(const Node *dictionary, const char *word)
{
	int result;
	const Node *leaf = dictionary;

	do
	{	
		result = WordCompare(word, leaf->word);

		if (result == 0)
			return true;
		else
		{
			if (result > 0)
				leaf = leaf->right;
			else
				leaf = leaf->left;
		}
	} while (leaf != NULL);

	return false;
}

Node * FindNode(Node *dictionary, const char *word)
{
	int result;
	Node *leaf = dictionary;

	do
	{
		result = WordCompare(word, leaf->word);

		if (result == 0)
			return leaf;
		else
		{
			if (result > 0)
				leaf = leaf->right;
			else
				leaf = leaf->left;
		}
	} while (leaf != NULL);

	return NULL;
}

int InsertWord(const char *word, GameHandler &gameHandler)
{
	char c;
	bool vertical = false;
	int playerLettersAmount[LETTERS_AMOUNT] = { 0 };
	char buffer[MAX_INLINE_LETTERS] = { NULL_CHARACTER };
	char multiplier[MAX_MULTIPLIER_LETTERS + 1] = { NULL_CHARACTER };

	int x = wherex();
	int y = wherey();

	int length = GetStringLength(word);

	while (x + length > XORIGIN + BOARD_WIDTH)
		x--;

	do
	{
		if (gameHandler.tutorial == true)
		{
			buffer[0] = '(';

			for (int i = 1; i < MAX_INLINE_LETTERS; i++)
				buffer[i] = NULL_CHARACTER;

			for (int i = 0; i <= MAX_MULTIPLIER_LETTERS; i++)
				multiplier[i] = NULL_CHARACTER;
		}

		for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
		{
			int index;

			if (gameHandler.players[PLAYER_ID].letters[i] == EMPTY_CHARACTER)
				index = LETTERS_AMOUNT - 1;
			else
				index = gameHandler.players[PLAYER_ID].letters[i] - 'A';

			playerLettersAmount[index] = gameHandler.players[PLAYER_ID].lettersAmount[index];
		}

		length = GetStringLength(word);

		gotoxy(x, y);
		textcolor(BLACK);

		if (vertical == false)
		{
			int i = 0;
			while (*(word + i) != NULL_CHARACTER)
			{
				if (x + i > XORIGIN + BOARD_WIDTH - 1)
				{
					textbackground(RED);
					putch(*(word + i));
				}
				else
				{
					if (gameHandler.board.letters[x + i - XORIGIN][y - YORIGIN] == EMPTY_CHARACTER)
					{
						int index = *(word + i) - 'A';

						if (playerLettersAmount[index] > 0)
						{
							textbackground(GREEN);
							putch(*(word + i));
							playerLettersAmount[index]--;
						}
						else
						{
							if (playerLettersAmount[LETTERS_AMOUNT - 1] > 0)
							{
								textbackground(GREEN);
								putch(*(word + i));
								playerLettersAmount[LETTERS_AMOUNT - 1]--;
							}
							else
							{
								textbackground(RED);
								putch(*(word + i));
							}
						}

					}
					else
					{
						textbackground(GREEN);
						putch(gameHandler.board.letters[x + i - XORIGIN][y - YORIGIN]);
					}
				}
				
				if (gameHandler.tutorial == true)
				{
					char letter = *(word + i);
					FieldType field = gameHandler.board.fields[x + i - XORIGIN][y - YORIGIN];

					char points = SCORE_EXCHANGE_VALUE + GetLetterPoints(letter);
					char temp[6] = { NULL_CHARACTER };

					if (points == SCORE_DEBUG_VALUE)
					{
						temp[0] = '1';
						temp[1] = '0';
						temp[2] = '(';
						temp[3] = letter;
						temp[4] = ')';
					}
					else
					{
						temp[0] = points;
						temp[1] = '(';
						temp[2] = letter;
						temp[3] = ')';
					}

					if (i != 0)
					{
						strcat(buffer, "+");
					}
					strcat(buffer, temp);
					
					for (int i = 0; i < 5; i++)
					{
						temp[i] = NULL_CHARACTER;
					}

					if (field == FieldType::ls3)
					{
						temp[0] = '*';
						temp[1] = SCORE_EXCHANGE_VALUE + FieldValue::vls3;
					}
					else if (field == FieldType::ls2)
					{
						temp[0] = '*';
						temp[1] = SCORE_EXCHANGE_VALUE + FieldValue::vls2;
					}
					else if (field == FieldType::ws3)
					{
						int index = GetStringLength(multiplier);
						multiplier[index] = '*';
						multiplier[index + 1] = SCORE_EXCHANGE_VALUE + FieldValue::vws3;
					}
					else if (field == FieldType::ws2)
					{
						int index = GetStringLength(multiplier);
						multiplier[index] = '*';
						multiplier[index + 1] = SCORE_EXCHANGE_VALUE + FieldValue::vws2;
					}

					if (GetStringLength(temp) > 0)
						strcat(buffer, temp);
				}

				i++;
			}
		}
		else
		{
			int i = 0;
			while (*(word + i) != NULL_CHARACTER)
			{
				gotoxy(x, y + i);

				if (y + i > YORIGIN + BOARD_WIDTH - 1)
				{
					textbackground(RED);
					putch(*(word + i));

				}
				else
				{
					if (gameHandler.board.letters[x - XORIGIN][y + i - YORIGIN] == EMPTY_CHARACTER)
					{
						int index = -1;
						if (*(word + i) == EMPTY_CHARACTER)
							index = LETTERS_AMOUNT - 1;
						else
							index = *(word + i) - 'A';

						if (playerLettersAmount[index] > 0)
						{
							textbackground(GREEN);
							putch(*(word + i));
							playerLettersAmount[index]--;
						}
						else
						{
							if (playerLettersAmount[LETTERS_AMOUNT - 1] > 0)
							{
								textbackground(GREEN);
								putch(*(word + i));
								playerLettersAmount[LETTERS_AMOUNT - 1]--;
							}
							else
							{
								textbackground(RED);
								putch(*(word + i));
							}
						}

					}
					else
					{
						textbackground(GREEN);
						putch(gameHandler.board.letters[x - XORIGIN][y + i - YORIGIN]);
					}
				}

				if (gameHandler.tutorial == true)
				{
					char letter = *(word + i);
					FieldType field = gameHandler.board.fields[x - XORIGIN][y + i - YORIGIN];

					char points = SCORE_EXCHANGE_VALUE + GetLetterPoints(letter);
					char temp[6] = { NULL_CHARACTER };

					if (points == SCORE_DEBUG_VALUE)
					{
						temp[0] = '1';
						temp[1] = '0';
						temp[2] = '(';
						temp[3] = letter;
						temp[4] = ')';
					}
					else
					{
						temp[0] = points;
						temp[1] = '(';
						temp[2] = letter;
						temp[3] = ')';
					}

					if (i != 0)
					{
						strcat(buffer, "+");
					}
					strcat(buffer, temp);

					for (int i = 0; i < 5; i++)
					{
						temp[i] = NULL_CHARACTER;
					}

					if (field == FieldType::ls3)
					{
						temp[0] = '*';
						temp[1] = SCORE_EXCHANGE_VALUE + FieldValue::vls3;
					}
					else if (field == FieldType::ls2)
					{
						temp[0] = '*';
						temp[1] = SCORE_EXCHANGE_VALUE + FieldValue::vls2;
					}
					else if (field == FieldType::ws3)
					{
						int index = GetStringLength(multiplier);
						multiplier[index] = '*';
						multiplier[index + 1] = SCORE_EXCHANGE_VALUE + FieldValue::vws3;
					}
					else if (field == FieldType::ws2)
					{
						int index = GetStringLength(multiplier);
						multiplier[index] = '*';
						multiplier[index + 1] = SCORE_EXCHANGE_VALUE + FieldValue::vws2;
					}

					if (GetStringLength(temp) > 0)
						strcat(buffer, temp);
				}

				i++;
			}
		}


		if (gameHandler.tutorial == true)
		{
			int k = GetStringLength(buffer);
			buffer[k] = ')';

			if (GetStringLength(multiplier) > 0)
			{
				strcat(buffer, multiplier);
			}

			PrintWordValue(buffer);
		}


		gotoxy(x, y);

		c = getch();

		if (c == IS_ARROW_KEY)
		{
			textbackground(gameHandler.board.fields[wherex() - XORIGIN][wherey() - YORIGIN]);
			putch(gameHandler.board.letters[wherex()][wherey()]);

			c = getch();		// the next code knowing that this will be a special key
			if (c == ARROW_UP && y > YORIGIN)							y--;
			else if (c == ARROW_DOWN && y < YORIGIN + BOARD_WIDTH - 1)  y++;
			else if (c == ARROW_LEFT && x > XORIGIN)				    x--;
			else if (c == ARROW_RIGHT && x < XORIGIN + BOARD_WIDTH - 1) x++;

			PrintCoords(x, y);
			ClearOffBoard();
			PrintLegend(gameHandler);
			PrintBoard(gameHandler);
		}
		else if (c == INSERT_ROTATE_KEY)
		{
			vertical = !vertical;

			ClearOffBoard();
			PrintBoard(gameHandler);
			PrintLegend(gameHandler);
		}
		else if (c == INSERT_ACCEPT_KEY)
		{
			if (wherex() + length > XORIGIN + BOARD_WIDTH || wherey() + length > YORIGIN + BOARD_WIDTH)
			{
				PrintMessage("Typed word has to be on the board.");
				return false;
			}
			else
			{
				bool linked = false;
				bool filled = true;

				for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
				{
					int index;

					if (gameHandler.players[PLAYER_ID].letters[i] == EMPTY_CHARACTER)
						index = LETTERS_AMOUNT - 1;
					else
						index = gameHandler.players[PLAYER_ID].letters[i] - 'A';

					playerLettersAmount[index] = gameHandler.players[PLAYER_ID].lettersAmount[index];
				}


				if (gameHandler.firstWord == true)
				{
					for (int i = 0; i < length; i++)
					{
						if (vertical == false)
						{
							if (wherex() + i == XORIGIN + BOARD_WIDTH / 2 && wherey() == YORIGIN + BOARD_WIDTH / 2)
							{
								linked = true;
							}

							int index = *(word + i) - 'A';

							if (playerLettersAmount[index] <= 0)
							{
								if (playerLettersAmount[LETTERS_AMOUNT - 1] <= 0)
									filled = false;
								else
									playerLettersAmount[LETTERS_AMOUNT - 1]--;
							}
							else
								playerLettersAmount[index]--;
						}
						else
						{
							if (wherex() == XORIGIN + BOARD_WIDTH / 2 && wherey() + i == YORIGIN + BOARD_WIDTH / 2)
							{
								linked = true;
							}

							int index = *(word + i) - 'A';

							if (playerLettersAmount[index] <= 0)
							{
								if (playerLettersAmount[LETTERS_AMOUNT - 1] <= 0)
									filled = false;
								else
									playerLettersAmount[LETTERS_AMOUNT - 1]--;
							}
							else
								playerLettersAmount[index]--;
						}
					}

					gameHandler.firstWord = false;
				}
				else
				{
					for (int i = 0; i < length; i++)
					{
						if (vertical == false)
						{
							if (gameHandler.board.letters[wherex() - XORIGIN + i][wherey() - YORIGIN] != EMPTY_CHARACTER)
							{
								if (i == 0)
								{
									if (gameHandler.board.letters[wherex() - XORIGIN - 1][wherey() - YORIGIN] != EMPTY_CHARACTER)
									{
										linked = false;
										break;
									}
								}

								if (*(word + i) == gameHandler.board.letters[wherex() - XORIGIN + i][wherey() - YORIGIN])
									linked = true;

								if (*(word + i) != gameHandler.board.letters[wherex() - XORIGIN + i][wherey() - YORIGIN])
									filled = false;
							}
							else
							{
								int index;

								if (*(word + i) != EMPTY_CHARACTER)
									index = *(word + i) - 'A';
								else
									index = LETTERS_AMOUNT - 1;

								if (playerLettersAmount[index] <= 0)
								{
									if (playerLettersAmount[LETTERS_AMOUNT - 1] <= 0)
										filled = false;
									else
										playerLettersAmount[LETTERS_AMOUNT - 1]--;
								}
								else
									playerLettersAmount[index]--;
							}
						}
						else
						{
							if (gameHandler.board.letters[wherex() - XORIGIN][wherey() - YORIGIN + i] != EMPTY_CHARACTER)
							{
								if (i == 0)
								{
									if (gameHandler.board.letters[wherex() - XORIGIN][wherey() - YORIGIN - 1] != EMPTY_CHARACTER)
									{
										linked = false;
										break;
									}
								}

								if (*(word + i) == gameHandler.board.letters[wherex() - XORIGIN][wherey() - YORIGIN + i])
									linked = true;

								if (*(word + i) != gameHandler.board.letters[wherex() - XORIGIN][wherey() - YORIGIN + i])
									filled = false;
							}
							else
							{
								int index;

								if (*(word + i) != EMPTY_CHARACTER)
									index = *(word + i) - 'A';
								else
									index = LETTERS_AMOUNT - 1;

								if (playerLettersAmount[index] <= 0)
								{
									if (playerLettersAmount[LETTERS_AMOUNT - 1] <= 0)
										filled = false;
									else
										playerLettersAmount[LETTERS_AMOUNT - 1]--;
								}
								else
									playerLettersAmount[index]--;
							}
						}
					}
				}

				if (linked && filled == true)
				{
					GrantPoints(gameHandler, word, vertical);
					
					if (gameHandler.tutorial == true)
						ClearWordValue();

					return 1;
				}
				else
				{
					if (linked == false && filled == false)
					{
						PrintMessage("Typed word do not fit a board.");
					}
					else if (linked == false)
					{
						PrintMessage("Typed word must be linked to previous words.");
					}
					else
					{
						PrintMessage("Typed word can not be completed.");
					}
					return -1;
				}
			}
		}
	} while (c != INSERT_CANCEL_KEY);
	
	if (gameHandler.tutorial == true)
		ClearWordValue();

	return 0;

}

void ClearOffBoard()
{
	int xBack = wherex();
	int yBack = wherey();

	int x = BOARD_X_OFFSET + ((1 + WINDOW_LAYOUT) % 2) * (LEGEND_WIDTH + LEGEND_X_OFFSET + WINDOW_LAYOUT_SPACING) + BOARD_WIDTH + 2;
	int y = BOARD_Y_OFFSET;

	textbackground(BLACK);
	for (int i = 0; i <= BOARD_WIDTH; i++)
	{
		gotoxy(x, y + i);
		for (int j = 0; j < PLAYER_LETTERS_AMOUNT; j++)
		{
			putch(EMPTY_CHARACTER);
		}
	}

	x = BOARD_X_OFFSET + ((1 + WINDOW_LAYOUT) % 2) * (LEGEND_WIDTH + LEGEND_X_OFFSET + WINDOW_LAYOUT_SPACING);
	y = BOARD_Y_OFFSET + BOARD_WIDTH + 2;

	for (int i = 0; i <= BOARD_WIDTH; i++)
	{
		for (int j = 0; j < PLAYER_LETTERS_AMOUNT; j++)
		{
			gotoxy(x + i, y + j);
			putch(EMPTY_CHARACTER);
		}
	}


	gotoxy(xBack, yBack);
}

void GameClose(GameHandler &gameHandler)
{
	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
					// visible after the program ends
	DictionaryClose(gameHandler);

	if(__argc == 0)
		free(gameHandler.dictionaryPath);
}

void GrantPoints(GameHandler &gameHandler, const char *word, bool vertical, bool player)
{
	int points = 0;
	int length = GetStringLength(word);

	int x = wherex();
	int y = wherey();

	int lettersUsed = 0;

	int verticalValue;

	if (vertical == true)
	{
		verticalValue = 1;
	}
	else
	{
		verticalValue = 0;
	}

	int multiplier = 1;

	for (int i = 0; i < length; i++)
	{
		if (gameHandler.board.letters[x + i * (Absolute(verticalValue - 1)) - XORIGIN][y + i * verticalValue - YORIGIN] == EMPTY_CHARACTER)
		{
			lettersUsed++;
			gameHandler.board.letters[x + i * (Absolute(verticalValue - 1)) - XORIGIN][y + i * verticalValue - YORIGIN] = *(word + i);

			if (player == true)
			{
				bool found = false;
				for (int j = 0; j < PLAYER_LETTERS_AMOUNT; j++)
				{
					if (gameHandler.players[PLAYER_ID].letters[j] == *(word + i))
					{
						int index = gameHandler.players[PLAYER_ID].letters[j] - 'A';

						gameHandler.players[PLAYER_ID].lettersAmount[index]--;
						gameHandler.players[PLAYER_ID].letters[j] = NULL_CHARACTER;

						found = true;

						break;
					}
				}

				if (found == false)
				{
					for (int j = 0; j < PLAYER_LETTERS_AMOUNT; j++)
					{
						if (gameHandler.players[PLAYER_ID].letters[j] == EMPTY_CHARACTER)
						{
							gameHandler.players[PLAYER_ID].lettersAmount[LETTERS_AMOUNT - 1]--;
							gameHandler.players[PLAYER_ID].letters[j] = NULL_CHARACTER;

							break;
						}
					}
				}
			}
			else
			{
				bool found = false;
				for (int j = 0; j < PLAYER_LETTERS_AMOUNT; j++)
				{
					if (gameHandler.players[AI_ID].letters[j] == *(word + i))
					{
						int index = 0;
						if (*(word + i) == EMPTY_CHARACTER)
							index = LETTERS_AMOUNT - 1;
						else
							index = gameHandler.players[AI_ID].letters[j] - 'A';

						gameHandler.players[AI_ID].lettersAmount[index]--;
						gameHandler.players[AI_ID].letters[j] = NULL_CHARACTER;
					}
				}

				if (found == false)
				{
					for (int j = 0; j < PLAYER_LETTERS_AMOUNT; j++)
					{
						if (gameHandler.players[AI_ID].letters[j] == EMPTY_CHARACTER)
						{
							gameHandler.players[AI_ID].lettersAmount[LETTERS_AMOUNT - 1]--;
							gameHandler.players[AI_ID].letters[j] = NULL_CHARACTER;
						}
					}
				}
			}
		}

		FieldType field = gameHandler.board.fields[x + i * (Absolute(verticalValue - 1)) - XORIGIN][y + i * verticalValue - YORIGIN];
		if (field == FieldType::ls3)
		{
			points += (int)FieldValue::vls3 * GetLetterPoints(word[i]);
		}
		else if (field == FieldType::ls2)
		{
			points += (int)FieldValue::vls2 * GetLetterPoints(word[i]);
		}
		else
		{
			points += GetLetterPoints(word[i]);

			if (field == FieldType::ws3)
			{
				multiplier *= (int)FieldValue::vws3;
			}
			else if (field == FieldType::ws2)
			{
				multiplier *= (int)FieldValue::vws2;
			}
		}
	}

	if (lettersUsed == PLAYER_LETTERS_AMOUNT)
		points += 50;

	points *= multiplier;

	if (player == true)
	{
		gameHandler.players[PLAYER_ID].points += points;
	}
	else
	{
		gameHandler.players[AI_ID].points += points;
	}

	PrintPoints(gameHandler);
}

int GetLetterAmount(char c)
{
	switch (c)
	{
	case 'A':
		return (int)LetterAmount::la_A;
	case 'B':
		return (int)LetterAmount::la_B;
	case 'C':
		return (int)LetterAmount::la_C;
	case 'D':
		return (int)LetterAmount::la_D;
	case 'E':
		return (int)LetterAmount::la_E;
	case 'F':
		return (int)LetterAmount::la_F;
	case 'G':
		return (int)LetterAmount::la_G;
	case 'H':
		return (int)LetterAmount::la_H;
	case 'I':
		return (int)LetterAmount::la_I;
	case 'J':
		return (int)LetterAmount::la_J;
	case 'K':
		return (int)LetterAmount::la_K;
	case 'L':
		return (int)LetterAmount::la_L;
	case 'M':
		return (int)LetterAmount::la_M;
	case 'N':
		return (int)LetterAmount::la_N;
	case 'O':
		return (int)LetterAmount::la_O;
	case 'Q':
		return (int)LetterAmount::la_Q;
	case 'P':
		return (int)LetterAmount::la_P;
	case 'R':
		return (int)LetterAmount::la_R;
	case 'S':
		return (int)LetterAmount::la_S;
	case 'T':
		return (int)LetterAmount::la_T;
	case 'U':
		return (int)LetterAmount::la_U;
	case 'V':
		return (int)LetterAmount::la_V;
	case 'W':
		return (int)LetterAmount::la_W;
	case 'X':
		return (int)LetterAmount::la_X;
	case 'Y':
		return (int)LetterAmount::la_Y;
	case 'Z':
		return (int)LetterAmount::la_Z;
	default:
		return (int)LetterAmount::la_PUSTY;
	}
}

int GetLetterPoints(char c)
{
	switch (c)
	{
	case 'A':
		return (int)LetterPoints::lp_A;
	case 'B':
		return (int)LetterPoints::lp_B;
	case 'C':
		return (int)LetterPoints::lp_C;
	case 'D':
		return (int)LetterPoints::lp_D;
	case 'E':
		return (int)LetterPoints::lp_E;
	case 'F':
		return (int)LetterPoints::lp_F;
	case 'G':
		return (int)LetterPoints::lp_G;
	case 'H':
		return (int)LetterPoints::lp_H;
	case 'I':
		return (int)LetterPoints::lp_I;
	case 'J':
		return (int)LetterPoints::lp_J;
	case 'K':
		return (int)LetterPoints::lp_K;
	case 'L':
		return (int)LetterPoints::lp_L;
	case 'M':
		return (int)LetterPoints::lp_M;
	case 'N':
		return (int)LetterPoints::lp_N;
	case 'O':
		return (int)LetterPoints::lp_O;
	case 'Q':
		return (int)LetterPoints::lp_Q;
	case 'P':
		return (int)LetterPoints::lp_P;
	case 'R':
		return (int)LetterPoints::lp_R;
	case 'S':
		return (int)LetterPoints::lp_S;
	case 'T':
		return (int)LetterPoints::lp_T;
	case 'U':
		return (int)LetterPoints::lp_U;
	case 'V':
		return (int)LetterPoints::lp_V;
	case 'W':
		return (int)LetterPoints::lp_W;
	case 'X':
		return (int)LetterPoints::lp_X;
	case 'Y':
		return (int)LetterPoints::lp_Y;
	case 'Z':
		return (int)LetterPoints::lp_Z;
	default :
		return 0;
	}
}

int GetStringLength(const char *string)
{
	int length;

	for (length = 0; *(string + length) != NULL_CHARACTER; length++)
		;

	return length;
}

int Absolute(int x)
{
	if (x < 0)
		return -x;
	else
		return x;
}

Player PlayerInit(GameHandler &gameHandler, bool human)
{
	Player player;
	player.points = 0;

	for (int i = 0; i < LETTERS_AMOUNT; i++)
	{
		player.lettersAmount[i] = 0;
	}

	for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
	{
		player.selected[i] = false;

		player.letters[i] = GetRandomLetter(gameHandler);

		int index = 0;
		if (player.letters[i] == EMPTY_CHARACTER)
			index = LETTERS_AMOUNT - 1;
		else
			index = player.letters[i] - 'A';

		player.lettersAmount[index]++;
	}

	return player;
}

int Random(int range, GameHandler &gameHandler)
{
	gameHandler.randomID++;

	return rand() % range;
}

char UpperCase(char c)
{
	if (c >= 'a' && c <= 'z')
		c -= EXCHANGE_UPPERLOWER_VALUE;

	return c;
}

void DrawLetters(GameHandler &gameHandler, bool human)
{
	for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
	{
		if (human == true)
		{
			if (gameHandler.players[PLAYER_ID].letters[i] == NULL_CHARACTER)
				gameHandler.players[PLAYER_ID].letters[i] = GetRandomLetter(gameHandler);


			int index = 0;
			if (gameHandler.players[PLAYER_ID].letters[i] == EMPTY_CHARACTER)
				index = LETTERS_AMOUNT - 1;
			else
				index = gameHandler.players[PLAYER_ID].letters[i] - 'A';

			gameHandler.players[PLAYER_ID].lettersAmount[index]++;
		}
		else
		{
			if (gameHandler.players[AI_ID].letters[i] == NULL_CHARACTER)
				gameHandler.players[AI_ID].letters[i] = GetRandomLetter(gameHandler);

			int index = 0;
			if (gameHandler.players[AI_ID].letters[i] == EMPTY_CHARACTER)
				index = LETTERS_AMOUNT - 1;
			else
				index = gameHandler.players[AI_ID].letters[i] - 'A';

			gameHandler.players[AI_ID].lettersAmount[index]++;
		}
	}
}

char GetRandomLetter(GameHandler &gameHandler)
{
	int x;
	char c;
	bool endGame = true;

	for (int i = 0; i < LETTERS_AMOUNT; i++)
	{
		if (gameHandler.letters[i] > 0)
		{
			endGame = false;
			break;
		}
	}

	if (endGame == true)
	{
		GameClose(gameHandler);
		exit(GAME_END);
	}

	do
	{
		x = Random(LETTERS_AMOUNT, gameHandler);
	} while (gameHandler.letters[x] == 0);

	if (x == LETTERS_AMOUNT - 1)
	{
		c = EMPTY_CHARACTER;
	}
	else
	{
		c = 'A' + x;
	}

	gameHandler.letters[x]--;

	return c;
}

bool Exchange(GameHandler &gameHandler)
{
	char c;

	do
	{
		c = getch();

		if (c >= EXCHANGE_MIN_RANGE_KEY && c <= EXCHANGE_MAX_RANGE_KEY)
		{
			gameHandler.players[PLAYER_ID].selected[c - EXCHANGE_MIN_RANGE_KEY] = !gameHandler.players[PLAYER_ID].selected[c - EXCHANGE_MIN_RANGE_KEY];
			PrintPlayerLetters(gameHandler.players[PLAYER_ID]);
		}
		else if (c == EXCHANGE_START_KEY || c == EXCHANGE_ACCEPT_KEY)
		{
			ExchangeLetters(gameHandler);

			for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
			{
				gameHandler.players[PLAYER_ID].selected[i] = false;
			}

			return true;
		}
		else if (c == EXCHANGE_CANCEL_KEY)
		{
			for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
			{
				gameHandler.players[PLAYER_ID].selected[i] = false;
			}
			return false;
		}
	} while (true == true);

}

void ExchangeLetters(GameHandler &gameHandler, bool human)
{
	if (human == true)
	{
		for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
		{
			if (gameHandler.players[PLAYER_ID].selected[i] == true)
			{
				int index = 0;

				if (gameHandler.players[PLAYER_ID].letters[i] == EMPTY_CHARACTER)
					index = LETTERS_AMOUNT - 1;
				else
					index = gameHandler.players[PLAYER_ID].letters[i] - 'A';

				gameHandler.letters[index]++;
				gameHandler.players[PLAYER_ID].lettersAmount[index]--;

				gameHandler.players[PLAYER_ID].letters[i] = NULL_CHARACTER;
			}
		}

		for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
		{
			if (gameHandler.players[PLAYER_ID].letters[i] == NULL_CHARACTER)
			{
				gameHandler.players[PLAYER_ID].letters[i] = GetRandomLetter(gameHandler);

				int index = 0;

				if (gameHandler.players[PLAYER_ID].letters[i] == EMPTY_CHARACTER)
					index = LETTERS_AMOUNT - 1;
				else
					index = gameHandler.players[PLAYER_ID].letters[i] - 'A';

				gameHandler.players[PLAYER_ID].lettersAmount[index]++;
			}
		}
	}
	else
	{
		for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
		{
			if (gameHandler.players[AI_ID].selected[i] == true)
			{
				int index = 0;

				if (gameHandler.players[AI_ID].letters[i] == EMPTY_CHARACTER)
					index = LETTERS_AMOUNT - 1;
				else
					index = gameHandler.players[AI_ID].letters[i] - 'A';

				gameHandler.letters[index]++;
				gameHandler.players[AI_ID].lettersAmount[index]--;

				gameHandler.players[AI_ID].letters[i] = NULL_CHARACTER;
			}
		}

		for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
		{
			if (gameHandler.players[AI_ID].letters[i] == NULL_CHARACTER)
			{
				gameHandler.players[AI_ID].letters[i] = GetRandomLetter(gameHandler);

				int index = 0;

				if (gameHandler.players[AI_ID].letters[i] == EMPTY_CHARACTER)
					index = LETTERS_AMOUNT - 1;
				else
					index = gameHandler.players[AI_ID].letters[i] - 'A';

				gameHandler.players[AI_ID].lettersAmount[index]++;
			}
		}
	}
}

void SaveGame(const GameHandler &gameHandler)
{
	PrintMessage("Save slot path (max 40 letters):");

	int index = 0;
	char c;
	char buffer[MAX_INLINE_LETTERS] = {NULL_CHARACTER};

	do
	{
		c = getch();

		if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) && (GetStringLength(buffer) <= PATH_MAX_LETTERS))
		{
			buffer[index] = UpperCase(c);
			buffer[index + 1] = '.';
			buffer[index + 2] = 't';
			buffer[index + 3] = 'x';
			buffer[index + 4] = 't';
			buffer[index + 5] = NULL_CHARACTER;

			PrintMessage(buffer);

			index++;
		}
		else if (c == SAVE_DELETE_KEY)
		{
			if (index > 0)
			{
				buffer[index - 1] = '.';
				buffer[index] = 't';
				buffer[index + 1] = 'x';
				buffer[index + 2] = 't';
				buffer[index + 3] = NULL_CHARACTER;

				index--;

				if (index > 0)
					PrintMessage(buffer);
				else
					PrintMessage("Save slot path (max 40 letters):");
			}
		}
		else if (c == SAVE_ACCEPT_KEY)
		{
			PrintMessage("Saving in progress...");

			FILE *file = fopen(buffer, "r");

			if (file != NULL)
			{
				PrintMessage("File currently exists. Override? (Y|N)");

				do
				{
					c = getch();
				} while (c != SAVE_OVERRIDE_YES && c != SAVE_OVERRIDE_NO);

				if (c == SAVE_OVERRIDE_NO)
				{
					PrintMessage("Saving incomplete.");
					return;
				}

				fclose(file);
			}

			file = fopen(buffer, "w");

			if (file == NULL)
			{
				PrintMessage("An error occured. Saving incomplete");
				return;
			}

			//saving

			fprintf(file, "%d\n", gameHandler.init);

			fprintf(file, "%d\n", gameHandler.firstWord);

			for (int i = 0; i < LETTERS_AMOUNT; i++)
			{
				fprintf(file, "%d ", gameHandler.letters[i]);
			}
			fprintf(file, "\n");

			for (int i = 0; i < BOARD_WIDTH; i++)
			{
				for (int j = 0; j < BOARD_WIDTH; j++)
				{
					char c;
					if (gameHandler.board.letters[i][j] == EMPTY_CHARACTER)
						c = EMPTY_CHARACTER_SAVE;
					else
						c = gameHandler.board.letters[i][j];
					fprintf(file, "%d%c ", (int)gameHandler.board.fields[i][j], c);
				}
				fprintf(file, "\n");
			}

			for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
			{
				char c;
				if (gameHandler.players[PLAYER_ID].letters[i] == EMPTY_CHARACTER)
					c = EMPTY_CHARACTER_SAVE;
				else
					c = gameHandler.players[PLAYER_ID].letters[i];
				fprintf(file, "%c ", c);
			}
			fprintf(file, "\n");

			for (int i = 0; i < LETTERS_AMOUNT; i++)
			{
				fprintf(file, "%d ", gameHandler.players[PLAYER_ID].lettersAmount[i]);
			}
			fprintf(file, "\n");

			fprintf(file, "%d\n", gameHandler.players[PLAYER_ID].points);

			if (gameHandler.AIinclude == true)
			{
				for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
				{
					char c;
					if (gameHandler.players[AI_ID].letters[i] == EMPTY_CHARACTER)
						c = EMPTY_CHARACTER_SAVE;
					else
						c = gameHandler.players[AI_ID].letters[i];
					fprintf(file, "%c ", c);
				}
				fprintf(file, "\n");

				for (int i = 0; i < LETTERS_AMOUNT; i++)
				{
					fprintf(file, "%d ", gameHandler.players[AI_ID].lettersAmount[i]);
				}
				fprintf(file, "\n");

				fprintf(file, "%d\n", gameHandler.players[AI_ID].points);
			}

			fprintf(file, "%s\n", gameHandler.dictionaryPath);

			fprintf(file, "%u\n", gameHandler.seed);

			fprintf(file, "%ld\n", gameHandler.randomID);

			fprintf(file, "%d\n", gameHandler.AIinclude);

			fprintf(file, "%d", gameHandler.tutorial);


			fclose(file);
			PrintMessage("Saving complete!");
			return;
		}

	} while (c != SAVE_CANCEL_KEY);

	ClearMessage();
}

void LoadGame(GameHandler &gameHandler)
{
	PrintMessage("Load slot path (max 40 letters):");

	int index = 0;
	char c;
	char buffer[MAX_INLINE_LETTERS] = { NULL_CHARACTER };

	do
	{
		c = getch();

		if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) && (GetStringLength(buffer) <= PATH_MAX_LETTERS))
		{
			buffer[index] = UpperCase(c);
			buffer[index + 1] = '.';
			buffer[index + 2] = 't';
			buffer[index + 3] = 'x';
			buffer[index + 4] = 't';
			buffer[index + 5] = NULL_CHARACTER;

			PrintMessage(buffer);

			index++;
		}
		else if (c == LOAD_DELETE_KEY)
		{
			if (index > 0)
			{
				buffer[index - 1] = '.';
				buffer[index] = 't';
				buffer[index + 1] = 'x';
				buffer[index + 2] = 't';
				buffer[index + 3] = NULL_CHARACTER;

				index--;

				if (index > 0)
					PrintMessage(buffer);
				else
					PrintMessage("Load slot path (max 40 letters):");

			}
		}
		else if (c == LOAD_ACCEPT_KEY)
		{
			PrintMessage("Loading in progress...");

			FILE *file = fopen(buffer, "r");

			if (file == NULL)
			{
				PrintMessage("File does not exist. Loading incomplete.");
				return;
			}

			//loading
			int result = 0;
			int boolean;

			result = fscanf(file, "%d", &boolean);
			if (boolean != 0)
				gameHandler.init = true;
			else
				gameHandler.init = false;

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			result = fscanf(file, "%d", &boolean);
			if (boolean != 0)
				gameHandler.firstWord = true;
			else
				gameHandler.firstWord = false;

			for (int i = 0; i < LETTERS_AMOUNT; i++)
			{
				result = fscanf(file, "%d ", &gameHandler.letters[i]);
			}

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			for (int i = 0; i < BOARD_WIDTH; i++)
			{
				for (int j = 0; j < BOARD_WIDTH; j++)
				{
					int field;
					char c;
					result = fscanf(file, "%d%c ", &field, &c);
					gameHandler.board.fields[i][j] = (FieldType)field;

					if (c == EMPTY_CHARACTER_SAVE)
						gameHandler.board.letters[i][j] = EMPTY_CHARACTER;
					else
						gameHandler.board.letters[i][j] = c;
				}
			}

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
			{
				char c;
				result = fscanf(file, "%c ", &c);

				if (c == EMPTY_CHARACTER_SAVE)
					gameHandler.players[PLAYER_ID].letters[i] = EMPTY_CHARACTER;
				else
					gameHandler.players[PLAYER_ID].letters[i] = c;
			}

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			for (int i = 0; i < LETTERS_AMOUNT; i++)
			{
				result = fscanf(file, "%d ", &gameHandler.players[PLAYER_ID].lettersAmount[i]);
			}

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			result = fscanf(file, "%d", &gameHandler.players[PLAYER_ID].points);

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			if (gameHandler.AIinclude == true)
			{
				for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
				{
					char c;
					result = fscanf(file, "%c ", &c);

					if (c == EMPTY_CHARACTER_SAVE)
						gameHandler.players[AI_ID].letters[i] = EMPTY_CHARACTER;
					else
						gameHandler.players[AI_ID].letters[i] = c;
				}

				if (result == EOF)
				{
					PrintMessage("File damaged! Please restart the game");
					return;
				}

				for (int i = 0; i < LETTERS_AMOUNT; i++)
				{
					result = fscanf(file, "%d ", &gameHandler.players[AI_ID].lettersAmount[i]);
				}

				if (result == EOF)
				{
					PrintMessage("File damaged! Please restart the game");
					return;
				}

				result = fscanf(file, "%d", &gameHandler.players[AI_ID].points);

				if (result == EOF)
				{
					PrintMessage("File damaged! Please restart the game");
					return;
				}
			}

			char buffer[MAX_INLINE_LETTERS];
			result = fscanf(file, "%s", buffer);

			free(gameHandler.dictionary);
			int lenght = GetStringLength(buffer);

			gameHandler.dictionaryPath = (char *)malloc(lenght);

			for (int i = 0; i < lenght; i++)
			{
				*(gameHandler.dictionaryPath + i) = *(buffer + i);
			}
			*(gameHandler.dictionaryPath + lenght) = NULL_CHARACTER;

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			result = fscanf(file, "%u", &gameHandler.seed);

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			result = fscanf(file, "%ld", &gameHandler.randomID);

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			result = fscanf(file, "%d", &boolean);
			if (boolean != 0)
				gameHandler.AIinclude = true;
			else
				gameHandler.AIinclude = false;

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			result = fscanf(file, "%d", &boolean);
			if (boolean != 0)
				gameHandler.tutorial = true;
			else
				gameHandler.tutorial = false;

			if (result == EOF)
			{
				PrintMessage("File damaged! Please restart the game");
				return;
			}

			fclose(file);
			PrintMessage("Loading complete!");
			return;
		}

	} while (c != LOAD_CANCEL_KEY);

	ClearMessage();
}

void AITurn(GameHandler &gameHandler)
{
	PrintMessage("AI's turn.");

	char *word;
	bool vertical = CreateWord(gameHandler, word);

	if (word != NULL)
	{
		GrantPoints(gameHandler, word, vertical, false);
		DrawLetters(gameHandler, false);

		//PrintMessage(word);

		free(word);

		if (gameHandler.firstWord == true)
			gameHandler.firstWord = false;
	}
	else
	{
		for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
		{
			gameHandler.players[AI_ID].selected[i] = false;
		}

		for (int i = 0; i < Random(PLAYER_LETTERS_AMOUNT, gameHandler); i++)
		{
			int index;

			do
			{
				index = Random(PLAYER_LETTERS_AMOUNT, gameHandler);
			} while (gameHandler.players[AI_ID].selected[index] == true);

			gameHandler.players[AI_ID].selected[index] = true;
		}

		//PrintMessage("Nothing.");

		ExchangeLetters(gameHandler, false);
	}
	PrintBoard(gameHandler);

	PrintMessage("Done. Your turn!");
}

bool CreateWord(const GameHandler &gameHandler, char *&word)
{
	bool vertical = false;
	word = NULL;
	int points = 0;
	int xMax = 0;
	int yMax = 0;

	int lettersCount = PLAYER_LETTERS_AMOUNT;
	char letters[PLAYER_LETTERS_AMOUNT];

	for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
	{
		letters[i] = gameHandler.players[AI_ID].letters[i];
	}

	do
	{
		if (lettersCount < PLAYER_LETTERS_AMOUNT)
		{
			int indexMin = -1;

			for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
			{
				if (letters[i] == NULL_CHARACTER)
					continue;

				if (indexMin < 0)
				{
					indexMin = i;
				}
				else
				{
					if (GetLetterPoints(letters[i]) < GetLetterPoints(indexMin))
					{
						indexMin = i;
					}
				}
			}

			letters[indexMin] = NULL_CHARACTER;
		}

		DoPermutations(letters);

		for (int x = 0; x < BOARD_WIDTH - lettersCount - 1; x++)
		{
			for (int y = 0; y < BOARD_WIDTH; y++)
			{
				char wordLettersH[BOARD_WIDTH + 1];

				for (int i = 0; i < BOARD_WIDTH; i++)
				{
					wordLettersH[i] = EMPTY_CHARACTER_SAVE;
				}

				wordLettersH[BOARD_WIDTH] = NULL_CHARACTER;

				if (CheckFit(gameHandler, x, y, lettersCount, wordLettersH, false) == true)
				{
					if (CheckWord(gameHandler, x, y, wordLettersH, letters, word, points, false) == true)
					{
						vertical = false;
						xMax = x;
						yMax = y;
					}
				}
			}
		}

		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			for (int y = 0; y < BOARD_WIDTH - 1; y++)
			{
				char wordLettersV[BOARD_WIDTH + 1];

				for (int i = 0; i < BOARD_WIDTH; i++)
				{
					wordLettersV[i] = EMPTY_CHARACTER_SAVE;
				}

				wordLettersV[BOARD_WIDTH] = NULL_CHARACTER;

				if (CheckFit(gameHandler, x, y, lettersCount, wordLettersV, true) == true)
				{
					if (CheckWord(gameHandler, x, y, wordLettersV, letters, word, points, true) == true)
					{
						vertical = true;
						xMax = x;
						yMax = y;
					}
				}
			}
		}

		lettersCount--;
	} while (lettersCount > 0);
	
	gotoxy(xMax + XORIGIN, yMax + YORIGIN);
	PrintCoords(xMax + XORIGIN, yMax + YORIGIN);

	return vertical;
}

bool CheckFit(const GameHandler &gameHandler, int x, int y, int lettersCount, char *wordletters, bool vertical)
{
	bool fit = true;
	bool linked = false;
	int lettersUsed = 0;

	if (vertical == false)
	{
		for (int i = 0; lettersUsed < lettersCount; i++)
		{
			if (x + i > BOARD_WIDTH)
			{
				fit = false;
				break;
			}
			else
			{
				if (gameHandler.firstWord == false)
				{
					if (i == 0)
					{
						if (gameHandler.board.letters[x - 1][y] != EMPTY_CHARACTER)
						{
							linked = false;
							break;
						}
					}

					if (gameHandler.board.letters[x + i][y] == EMPTY_CHARACTER)
					{
						lettersUsed++;
					}
					else
					{
						wordletters[i] = gameHandler.board.letters[x + i][y];
						linked = true;
					}
				}
				else
				{
					lettersUsed++;

					if (x + i == BOARD_WIDTH / 2 && y == BOARD_WIDTH / 2)
						linked = true;
				}
			}
		}
	}
	else
	{
		for (int i = 0; lettersUsed < lettersCount; i++)
		{
			if (y + i > BOARD_WIDTH)
			{
				fit = false;
				break;
			}
			else
			{
				if (gameHandler.firstWord == false)
				{
					if (i == 0)
					{
						if (gameHandler.board.letters[x][y - 1] != EMPTY_CHARACTER)
						{
							linked = false;
							break;
						}
					}

					if (gameHandler.board.letters[x][y + i] == EMPTY_CHARACTER)
					{
						lettersUsed++;
					}
					else
					{
						wordletters[i] = gameHandler.board.letters[x][y + i];
						linked = true;
					}
				}
				else
				{
					lettersUsed++;

					if (y + i == BOARD_WIDTH / 2 && x == BOARD_WIDTH / 2)
						linked = true;
				}
			}
		}
	}

	return (fit && linked);
}

bool CheckWord(const GameHandler &gameHandler, int x, int y, const char* wordLetters, const char* aiLetters, char *&word, int &points, bool vertical)
{
	char buffer[BOARD_WIDTH + 1] = { NULL_CHARACTER };
	char bufferWord[BOARD_WIDTH + 1] = { NULL_CHARACTER };

	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		bufferWord[i] = wordLetters[i];
	}

	int bufferPoints = 0;
	char *letters;


	int length = 0;

	for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
	{
		if (aiLetters[i] != NULL_CHARACTER)
		{
			length++;
		}
	}

	letters = (char *)malloc(length + 1);
	char * temp = letters;

	for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
	{
		if (aiLetters[i] != NULL_CHARACTER)
		{
			*(temp) = aiLetters[i];
			temp++;
		}
	}
	*(temp) = NULL_CHARACTER;


	FILE *permutations = fopen("permutations.txt", "r");

	char permutation[PLAYER_LETTERS_AMOUNT + 1];
	while (fscanf(permutations, "%s", permutation) != EOF)
	{
		int index;
		for (int i = 0, index = 0; i < BOARD_WIDTH; i++)
		{
			if (bufferWord[i] != EMPTY_CHARACTER_SAVE)
			{
				buffer[i] = bufferWord[i];
			}
			else if (permutation[index] != NULL_CHARACTER)
			{
				buffer[i] = permutation[index];
				index++;
			}
		}


		if (FindWord(gameHandler.dictionary, buffer) == true)
		{
			int multiplier = 1;

			if (vertical == false)
			{
				int length = GetStringLength(buffer);

				for (int i = 0; i < length; i++)
				{
					FieldType field = gameHandler.board.fields[x + i][y];

					if (field == FieldType::ls3)
					{
						bufferPoints += FieldValue::vls3 * GetLetterPoints(*(buffer + i));
					}
					else if (field == FieldType::ls2)
					{
						bufferPoints += FieldValue::vls2 * GetLetterPoints(*(buffer + i));
					}
					else
					{
						bufferPoints += GetLetterPoints(*(buffer + i));

						if (field == FieldType::ws3)
						{
							multiplier *= FieldValue::vws3;
						}
						else if (field == FieldType::ws2)
						{
							multiplier *= FieldValue::vws2;
						}
					}
				}
			}
			else
			{
				int length = GetStringLength(buffer);

				for (int i = 0; i < length; i++)
				{
					FieldType field = gameHandler.board.fields[x][y + i];

					if (field == FieldType::ls3)
					{
						bufferPoints += FieldValue::vls3 * GetLetterPoints(*(buffer + i));
					}
					else if (field == FieldType::ls2)
					{
						bufferPoints += FieldValue::vls2 * GetLetterPoints(*(buffer + i));
					}
					else
					{
						bufferPoints += GetLetterPoints(*(buffer + i));

						if (field == FieldType::ws3)
						{
							multiplier *= FieldValue::vws3;
						}
						else if (field == FieldType::ws2)
						{
							multiplier *= FieldValue::vws2;
						}
					}
				}
			}

			bufferPoints *= multiplier;

			if (length == 50)
			{
				bufferPoints += 50;
			}

			if (bufferPoints > points)
			{
				points = bufferPoints;

				if (word == NULL)
				{
					word = (char *)malloc(BOARD_WIDTH + 1);
				}
				else
				{
					for (int i = 0; i < BOARD_WIDTH + 1; i++)
					{
						*(word + i) = NULL_CHARACTER;
					}
				}

				for (int i = 0; i < BOARD_WIDTH + 1; i++)
				{
					*(word + i) = *(buffer + i);
				}

				fclose(permutations);
				free(letters);

				return true;
			}
		}
	}

	fclose(permutations);
	free(letters);

	return false;
}

void Permutation(FILE *permutations, char *base, char *perm, int lengthBase, int lengthPerm)
{
	if (lengthPerm <= 2)
	{
		if (lengthPerm == 0)
		{
			return;
		}
		else if (lengthPerm == 1)
		{
			if (*perm != EMPTY_CHARACTER)
			{
				strcat(base, perm);
				fprintf(permutations, "%s\n", base);
			}
			else
			{
				for (int i = 0; i < LETTERS_AMOUNT - 1; i++)
				{
					*(base + 1) = 'A' + i;
					fprintf(permutations, "%s\n", base);
				}
			}
		}
		else
		{
			base[lengthBase] = perm[0];
			base[lengthBase + 1] = perm[1];

			if (base[lengthBase] != EMPTY_CHARACTER)
			{
				if (base[lengthBase + 1] != EMPTY_CHARACTER)
				{
					fprintf(permutations, "%s\n", base);
				}
				else
				{
					for (int i = 0; i < LETTERS_AMOUNT - 1; i++)
					{
						base[lengthBase + 1] = 'A' + i;
						fprintf(permutations, "%s\n", base);
					}
				}
			}
			else
			{
				for (int i = 0; i < LETTERS_AMOUNT - 1; i++)
				{
					base[lengthBase] = 'A' + i;


					if (base[lengthBase + 1] != EMPTY_CHARACTER)
					{
						fprintf(permutations, "%s\n", base);
					}
					else
					{
						for (int i = 0; i < LETTERS_AMOUNT - 1; i++)
						{
							base[lengthBase + 1] = 'A' + i;
							fprintf(permutations, "%s\n", base);
						}
					}
				}
			}

			base[lengthBase] = perm[1];
			base[lengthBase + 1] = perm[0];

			if (base[lengthBase] != EMPTY_CHARACTER)
			{
				if (base[lengthBase + 1] != EMPTY_CHARACTER)
				{
					fprintf(permutations, "%s\n", base);
				}
				else
				{
					for (int i = 0; i < LETTERS_AMOUNT - 1; i++)
					{
						base[lengthBase + 1] = 'A' + i;
						fprintf(permutations, "%s\n", base);
					}
				}
			}
			else
			{
				for (int i = 0; i < LETTERS_AMOUNT - 1; i++)
				{
					base[lengthBase] = 'A' + i;


					if (base[lengthBase + 1] != EMPTY_CHARACTER)
					{
						fprintf(permutations, "%s\n", base);
					}
					else
					{
						for (int i = 0; i < LETTERS_AMOUNT - 1; i++)
						{
							base[lengthBase + 1] = 'A' + i;
							fprintf(permutations, "%s\n", base);
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < lengthPerm; i++)
		{

			base[lengthBase] = perm[i];

			char newPerm[PLAYER_LETTERS_AMOUNT + 1] = { NULL_CHARACTER };

			for (int j = 0; perm[j] != NULL_CHARACTER; j++)
			{
				if (j != i)
				{
					int index = GetStringLength(newPerm);
					newPerm[index] = perm[j];
				}
			}

			if (base[lengthBase] != EMPTY_CHARACTER)
			{
				Permutation(permutations, base, newPerm, lengthBase + 1, lengthPerm - 1);
			}
			else
			{
				for (int i = 0; i < LETTERS_AMOUNT - 1; i++)
				{
					base[lengthBase] = 'A' + i;
					Permutation(permutations, base, newPerm, lengthBase + 1, lengthPerm - 1);
				}
			}
		}
	}
}

void DoPermutations(char *letters)
{
	FILE *permutations = fopen("permutations.txt", "w");

	if (permutations == NULL)
		exit(EXIT_FILE_OPEN_FAILURE);

	int length = 0;

	for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
	{
		if (letters[i] != NULL_CHARACTER)
		{
			length++;
		}
	}

	char *lettersTemp = (char *)malloc(length + 1);
	char *temp = lettersTemp;

	for (int i = 0; i < PLAYER_LETTERS_AMOUNT; i++)
	{
		if (letters[i] != NULL_CHARACTER)
		{
			*(temp) = letters[i];
			temp++;
		}
	}
	*(temp) = NULL_CHARACTER;

	for (int i = 0; i < length; i++)
	{
		char base[PLAYER_LETTERS_AMOUNT + 1] = { NULL_CHARACTER };
		char perm[PLAYER_LETTERS_AMOUNT + 1] = { NULL_CHARACTER };

		if (*(lettersTemp + i) != EMPTY_CHARACTER)
		{
			base[0] = *(lettersTemp + i);

			int index = 0;
			for (int j = 0; j < length; j++)
			{
				if (i != j)
				{
					*(perm + index) = *(lettersTemp + j);
					index++;
				}
			}

			Permutation(permutations, base, perm, 1, length - 1);
		}
		else
		{
			for (int k = 0; k < LETTERS_AMOUNT - 1; k++)
			{
				base[0] = 'A' + k;

				int index = 0;
				for (int j = 0; j < length; j++)
				{
					if (i != j)
					{
						*(perm + index) = *(lettersTemp + j);
						index++;
					}
				}

				Permutation(permutations, base, perm, 1, length - 1);
			}
		}
	}

	fclose(permutations);
	free(lettersTemp);
}