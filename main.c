#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];

const char PLAYER = 'X';
const char COMPUTER = 'O';

void result_print(char winner);

void board_resetting()
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void board_printing()
{

    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int isSafe() /// Checks how many free spaces there are left in the matrix.
{
    int safe = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                safe--;
            }
        }
    }

    return safe;
}

void move_player() /// This function places a 'X' on the given coordinates where the player wanted to play.
{
    int x;
    int y;

    do
    {
        printf("Enter the row and column number: ");
        scanf("%d %d", &x, &y);
        x--;
        y--;

        if (board[x][y] == ' ')
        {
            board[x][y] = PLAYER;
            break;
        }
        else
        {
            printf("You have entered the already filled space, please try again.\n");
        }
    } while (board[x][y] != ' ');
}

void move_computer() /// This function places a 'O' on the given coordinates where the computer generated the coordinates.
{
    /// Setting the seed to a current computer time.
    srand(time(0));

    int x;
    int y;

    if (isSafe > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else
    {
        result_print(' ');
    }
}

char winner_checker()
{
    /// Checking to see if there is a 3 in a row of either X or O.

    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    /// Checking to see if there is a 3 in a column of either X or O.

    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == board[1][j] && board[0][j] == board[2][j])
        {
            return board[0][j];
        }
    }

    /// Checking to see if there is a 3 in a main diagonal of either X or O.

    int m = 0;

    if (board[m][m] == board[m + 1][m + 1] && board[m][m] == board[m + 2][m + 2])
    {
        return board[m][m];
    }

    /// Checking to see if there is a 3 in a side diagonal of either X or O.

    int s = 0;

    if (board[s][2] == board[s + 1][1] && board[s][2] == board[2][s])
    {
        return board[s][2];
    }

    return ' ';
}

void result_print(char winner)
{
    if (winner == PLAYER)
    {
        printf("Congratulations! You win!\n");
    }
    else if (winner == COMPUTER)
    {
        printf("Better luck next time!\n");
    }
    else
    {
        printf("It's a tie!\n");
    }
}

int main()
{
    char winner = ' ';

    board_resetting();

    while (winner == ' ' && isSafe)
    {
        board_printing();

        move_player();

        winner = winner_checker();

        if (winner != ' ' || !isSafe)
        {
            break;
        }

        move_computer();

        winner = winner_checker();

        if (winner != ' ' || !isSafe)
        {
            break;
        }

        system("clear");
    }

    board_printing();
    result_print(winner);

    return 0;
}