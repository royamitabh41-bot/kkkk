/*
 * Rock Paper Scissors vs Computer
 * -------------------------------
 * The player picks Rock, Paper or Scissors, the computer picks randomly,
 * and the program decides the winner. Scores are tracked over many rounds
 * until the player chooses to quit.
 *
 * Flow:  show menu -> get choices -> decide winner -> update score -> repeat
 */

#include <stdio.h>
#include <stdlib.h>   /* rand(), srand() */
#include <time.h>     /* time() - used to seed the random generator */

/* Give each choice a readable name instead of a "magic number" */
#define ROCK     1
#define PAPER    2
#define SCISSORS 3

/* Results of a round */
#define DRAW         0
#define PLAYER_WINS  1
#define COMPUTER_WINS 2

/* ---------- FUNCTIONS ---------- */

/* Computer picks a random number: 1, 2 or 3 */
int getComputerChoice()
{
    return rand() % 3 + 1;
}

/* Ask the player for a choice. Keeps asking until the input is valid.
   Returns 1, 2, 3, or 0 if the player wants to quit. */
int getPlayerChoice()
{
    int choice;
    int status;
    int c;

    while (1)   /* loop until we get a valid answer */
    {
        printf("\nChoose your move:\n");
        printf("  1 - Rock\n");
        printf("  2 - Paper\n");
        printf("  3 - Scissors\n");
        printf("  0 - Quit\n");
        printf("Your choice: ");

        /* scanf returns 1 if it successfully read a number */
        status = scanf("%d", &choice);

        if (status == EOF)
        {
            return 0;   /* input ended (e.g. Ctrl+D) - treat as quit */
        }
        else if (status != 1)
        {
            /* The user typed letters - throw away the bad input */
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Please type a NUMBER between 0 and 3.\n");
        }
        else if (choice < 0 || choice > 3)
        {
            printf("Invalid choice. Try again.\n");
        }
        else
        {
            return choice;   /* valid input, send it back */
        }
    }
}

/* Turn the number into text so we can print it */
const char *choiceName(int choice)
{
    switch (choice)
    {
        case ROCK:     return "Rock";
        case PAPER:    return "Paper";
        case SCISSORS: return "Scissors";
        default:       return "Unknown";
    }
}

/* The game rules live in ONE place.
   Rock beats Scissors, Scissors beats Paper, Paper beats Rock. */
int decideWinner(int player, int computer)
{
    if (player == computer)
    {
        return DRAW;
    }
    else if ((player == ROCK     && computer == SCISSORS) ||
             (player == SCISSORS && computer == PAPER)    ||
             (player == PAPER    && computer == ROCK))
    {
        return PLAYER_WINS;
    }
    else
    {
        return COMPUTER_WINS;
    }
}

/* Print the current scores */
void showScoreboard(int playerScore, int computerScore, int draws)
{
    printf("\n------------- SCOREBOARD -------------\n");
    printf("  You: %d    Computer: %d    Draws: %d\n",
           playerScore, computerScore, draws);
    printf("--------------------------------------\n");
}

/* ---------- MAIN ---------- */

int main()
{
    int playerScore = 0, computerScore = 0, draws = 0;
    int round = 0;
    int player, computer, result;

    /* Seed the random generator with the current time,
       so the computer plays differently every run */
    srand(time(NULL));

    printf("======================================\n");
    printf("   ROCK  -  PAPER  -  SCISSORS\n");
    printf("         You vs Computer\n");
    printf("======================================\n");

    while (1)   /* game loop: one pass = one round */
    {
        player = getPlayerChoice();

        if (player == 0)   /* player chose to quit */
        {
            break;
        }

        round++;
        computer = getComputerChoice();

        printf("\n--- Round %d ---\n", round);
        printf("You chose:      %s\n", choiceName(player));
        printf("Computer chose: %s\n", choiceName(computer));

        result = decideWinner(player, computer);

        if (result == DRAW)
        {
            printf(">> It's a draw!\n");
            draws++;
        }
        else if (result == PLAYER_WINS)
        {
            printf(">> You win this round!\n");
            playerScore++;
        }
        else
        {
            printf(">> Computer wins this round!\n");
            computerScore++;
        }

        showScoreboard(playerScore, computerScore, draws);
    }

    /* ---------- GAME OVER ---------- */
    printf("\n======================================\n");
    printf("            GAME OVER\n");
    printf("======================================\n");
    printf("Rounds played: %d\n", round);
    showScoreboard(playerScore, computerScore, draws);

    if (playerScore > computerScore)
    {
        printf("Final result: YOU WIN THE MATCH!\n");
    }
    else if (computerScore > playerScore)
    {
        printf("Final result: Computer wins the match. Better luck next time!\n");
    }
    else
    {
        printf("Final result: The match is a tie!\n");
    }

    return 0;
}
