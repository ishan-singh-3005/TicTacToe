#include <stdio.h>

struct TicTacToe {
	char board[3][3];
	char playerChar;
	char computerChar;
	int turn;
};

void printBoard(char board[3][3]) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

void initializeBoard(char board[3][3]) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			board[i][j] = '_';
		}
	}
}

int checkBoard(char board[3][3]) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '_') {
				return 1;
			}
		}
	}
	return 0;
}

void computerMove(char board[3][3], char computerChar) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '_') {
				printf("Computer has played on position %d %d\n", i, j);
				board[i][j] = computerChar;
				return;
			}
		}
	}
}

int checkMove(char board[3][3], int x, int y) {
	if (board[x][y] == '_') {
		return 0;
	}
	return 1;
}

int checkWin(char board[3][3], char playerChar, char computerChar) {
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == playerChar && board[i][1] == playerChar && board[i][2] == playerChar) {
			printf("Player won!");
			return 0;
		}
		if (board[i][0] == computerChar && board[i][1] == computerChar && board[i][2] == computerChar) {
			printf("Computer won!");
			return 0;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == playerChar && board[1][i] == playerChar && board[2][i] == playerChar) {
			printf("Player won!");
			return 0;
		}
		if (board[0][i] == computerChar && board[1][i] == computerChar && board[2][i] == computerChar) {
			printf("Computer won!");
			return 0;
		}
	}

	if (board[0][0] == playerChar && board[1][1] == playerChar && board[2][2] == playerChar) {
		printf("Player won!");
		return 0;
	}
	if (board[0][2] == computerChar && board[1][1] == computerChar && board[2][0] == computerChar) {
		printf("Computer won!");
		return 0;
	}
	return -1;
}

void playerFirst(struct TicTacToe game) {
	int xVal;
	int yVal;
	int gameState = checkBoard(game.board);
	int turn;

	while (gameState == 1) {
		printf("Enter coordinate value: ");
		scanf_s("%d %d", &xVal, &yVal);
		int validMove = checkMove(game.board, xVal, yVal);
		while (validMove == 1) {
			printf("The spot is not free! \nEnter coordinate value: ");
			scanf_s("%d %d", &xVal, &yVal);
			validMove = checkMove(game.board, xVal, yVal);
		}
		printf("You placed X in position %d, %d\n", xVal, yVal);
		game.board[xVal][yVal] = game.playerChar;
		printBoard(game.board);
		int winner = checkWin(game.board, game.playerChar, game.computerChar);
		if (winner != -1) {
			break;
		}
		gameState = checkBoard(game.board);
		if (gameState == 0) {
			break;
		}
		computerMove(game.board, game.computerChar);
		printBoard(game.board);
		winner = checkWin(game.board, game.playerChar, game.computerChar);
		if (winner != -1) {
			break;
		}
	}
	printf("Game finished!");
}

void computerFirst(struct TicTacToe game) {
	int xVal;
	int yVal;
	int gameState = checkBoard(game.board);
	int turn;

	while (gameState == 1) {
		computerMove(game.board, game.computerChar);
		printBoard(game.board);
		int winner = checkWin(game.board, game.playerChar, game.computerChar);
		if (winner != -1) {
			break;
		}
		printf("Enter coordinate value: ");
		scanf_s("%d %d", &xVal, &yVal);
		int validMove = checkMove(game.board, xVal, yVal);
		while (validMove == 1) {
			printf("The spot is not free! \nEnter coordinate value: ");
			scanf_s("%d %d", &xVal, &yVal);
			validMove = checkMove(game.board, xVal, yVal);
		}
		printf("You placed X in position %d, %d\n", xVal, yVal);
		game.board[xVal][yVal] = game.playerChar;
		printBoard(game.board);
		winner = checkWin(game.board, game.playerChar, game.computerChar);
		if (winner != -1) {
			break;
		}
		gameState = checkBoard(game.board);
		if (gameState == 0) {
			break;
		}
	}
	printf("Game finished!");
}

int main() {
	struct TicTacToe game;
	initializeBoard(game.board);
	printf("Welcome to TicTacToe \n");
	printBoard(game.board);
	printf("Choose your symbol: ");
	scanf_s("%c", &game.playerChar);
	if (game.playerChar == 'O') {
		game.computerChar = 'X';
	}
	else {
		game.computerChar = 'O';
	}

	printf("Do you want to go first? 0 for yes, 1 for no: ");
	scanf_s("%d", &game.turn);
	if (game.turn == 0) {
		playerFirst(game);
	}
	else {
		computerFirst(game);
	}
	return 0;
}