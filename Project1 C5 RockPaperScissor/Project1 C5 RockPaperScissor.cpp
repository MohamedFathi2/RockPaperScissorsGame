#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// Enums and Structures
enum enRockPaperScissor { Rock = 1, Paper = 2, Scissor = 3 };

struct stChoices
{
    enRockPaperScissor enPlayerChoice, enComputerChoice;
};

struct stGameResults
{
    short ComputerCounter = 0, PlayerCounter = 0, DrawCounter = 0;
};

// Function Declarations
void StartGame();
void PlayNRounds(int RoundsNumber, stChoices& Choices, stGameResults& GameResults);
void ShowFinalGameResults(stGameResults GameResults, int NumberOfRounds, string Winner);
void PrintNRound(int i, stChoices Choices, stGameResults& GameResults);
bool ContinueOrNot();
short ReadHowManyRounds();
int ReadPositiveNumber(string Message);
int ReadNumber(string Message);
int RandomNumber(int From, int To);
string WhoWins(stChoices Choices, stGameResults& CounterResult);
string Winner(stGameResults GameResults);
void ResetScreen();
string StringState(enRockPaperScissor state);

void StartGame()
{
    short RoundsNumber = ReadHowManyRounds();
    stChoices Choices;
    stGameResults GameResults;
    cout << endl;
    PlayNRounds(RoundsNumber, Choices, GameResults);
    string WinnerOfTheGame = Winner(GameResults);
    ShowFinalGameResults(GameResults, RoundsNumber, WinnerOfTheGame);
    if (ContinueOrNot())
    {
        ResetScreen();
        StartGame();
    }
    else
    {
        system("color 0F");
        exit(0);
    }
}

void PlayNRounds(int RoundsNumber, stChoices& Choices, stGameResults& GameResults)
{
    for (int i = 0; i < RoundsNumber; i++)
    {
        cout << "Round [" << i + 1 << "] begins\n\n";
        string Message = "Your choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        Choices.enPlayerChoice = enRockPaperScissor(ReadNumber(Message));
        Choices.enComputerChoice = enRockPaperScissor(RandomNumber(1, 3));
        cout << "\n\n";
        PrintNRound(i, Choices, GameResults);
    }
}

void PrintNRound(int i, stChoices Choices, stGameResults& GameResults)
{
    string WhatToTypeComputer = "", WhatToTypePlayer = "";
    WhatToTypeComputer = StringState(Choices.enComputerChoice);
    WhatToTypePlayer = StringState(Choices.enPlayerChoice);
    string WhoIsTheWinner = WhoWins(Choices, GameResults);
    if (WhoIsTheWinner == " [Computer] ")
    {
        system("color 4F");
        cout << "\a";
    }
    else if (WhoIsTheWinner == " [Player1] ")
        system("color 2F");
    else
        system("color 6F");
    cout << "_____________Round [" << i + 1 << "]_____________" << endl;
    cout << "Player1  Choice: " << WhatToTypePlayer << endl;
    cout << "Computer Choice: " << WhatToTypeComputer << endl;
    cout << "Round Winner   :" << WhoIsTheWinner << endl;
    cout << "___________________________________\n" << endl;
}

string WhoWins(stChoices Choices, stGameResults& CounterResult)
{
    if (Choices.enComputerChoice == enRockPaperScissor::Paper && Choices.enPlayerChoice == enRockPaperScissor::Rock)
    {
        CounterResult.ComputerCounter += 1;
        return " [Computer] ";
    }
    else if (Choices.enComputerChoice == enRockPaperScissor::Rock && Choices.enPlayerChoice == enRockPaperScissor::Paper)
    {
        CounterResult.PlayerCounter += 1;
        return " [Player1] ";
    }
    else if (Choices.enComputerChoice == enRockPaperScissor::Scissor && Choices.enPlayerChoice == enRockPaperScissor::Paper)
    {
        CounterResult.ComputerCounter += 1;
        return " [Computer] ";
    }
    else if (Choices.enComputerChoice == enRockPaperScissor::Paper && Choices.enPlayerChoice == enRockPaperScissor::Scissor)
    {
        CounterResult.PlayerCounter += 1;
        return " [Player1] ";
    }
    else if (Choices.enComputerChoice == enRockPaperScissor::Rock && Choices.enPlayerChoice == enRockPaperScissor::Scissor)
    {
        CounterResult.ComputerCounter += 1;
        return " [Computer] ";
    }
    else if (Choices.enComputerChoice == enRockPaperScissor::Scissor && Choices.enPlayerChoice == enRockPaperScissor::Rock)
    {
        CounterResult.PlayerCounter += 1;
        return " [Player1] ";
    }
    else
    {
        CounterResult.DrawCounter += 1;
        return " [No Winner] ";
    }
}

string Winner(stGameResults GameResults)
{
    if (GameResults.ComputerCounter > GameResults.PlayerCounter)
        return "Computer";
    else if (GameResults.ComputerCounter < GameResults.PlayerCounter)
        return "Player1";
    else
        return "Draw";
}

void ShowFinalGameResults(stGameResults GameResults, int NumberOfRounds, string Winner)
{
    //if (Winner = "Computer")
    if (Winner == "Computer")
    {
        system("color 4F");
        cout << "\a";
    }
    else if (Winner == "Player1")
        system("color 2F");
    else
        system("color 6F");
    cout << "\t\t\t---------------------------------------------------------------------\n\n";
    cout << "\t\t\t\t\t\t+++ G a m e O v e r +++\n\n";
    cout << "\t\t\t---------------------------------------------------------------------\n\n";
    cout << "\t\t\t\t\t------------[Game Results]------------\n\n";

    cout << left;  // Align text to the left
    cout << "\t\t\tGame Rounds:" << NumberOfRounds << endl;
    cout << "\t\t\tPlayer1 won times:" << GameResults.PlayerCounter << endl;
    cout << "\t\t\tComputer won times:" << GameResults.ComputerCounter << endl;
    cout << "\t\t\tDraw times:" << GameResults.DrawCounter << endl;
    cout << "\t\t\tFinal Winner:" << Winner << endl;
    cout << "\t\t\t---------------------------------------------------------------------\n\n";
}

bool ContinueOrNot()
{
    char state;
    cout << "\nDo you want to play again? Y/N ";
    cin >> state;
    return (state == 'Y' || state == 'y');
}

short ReadHowManyRounds()
{
    return ReadPositiveNumber("How Many Rounds 1 to 10?");
}

int ReadPositiveNumber(string Message)
{
    int Number = 0;
    do
    {
        cout << Message << endl;
        cin >> Number;
    } while (Number <= 0);
    return Number;
}
int ReadNumber(string Message)
{
    int Number = 0;
    do
    {
        cout << Message << endl;
        cin >> Number;
    } while (Number < 1 || Number > 3);
    return Number;
}
int RandomNumber(int From, int To)
{
    // Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}
string StringState(enRockPaperScissor state)
{
    switch (state)
    {
    case enRockPaperScissor::Paper:
        return "Paper";
    case enRockPaperScissor::Rock:
        return "Rock";
    case enRockPaperScissor::Scissor:
        return "Scissor";
    default:
        return "";
    }
}
void ResetScreen()
{
    system("color 0F");
    system("cls");
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}