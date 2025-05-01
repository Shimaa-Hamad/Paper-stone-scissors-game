#include <iostream>
#include <cstdlib>

using namespace std; 

enum enChoice {Stone =1 , Paper=2 , Scissors=3};
enum enWinner {player1=1 , Computer=2 , Draw=3};

struct stRoundInfo
{
	short RoundNumber = 0;
	enChoice Player1Choice;
	enChoice ComputerChoice; 
	enWinner Winner; 
	string WinnerName;
};
struct stGameResult
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner; 
	string FinalWinner="";
};

int RandomNumber(int From, int To)
{
	int RandNum = rand()%(To-From +1 )+From ;
	return RandNum; 
}

enChoice GetComputerChoice()
{
	return (enChoice)RandomNumber(1, 3);
}

enChoice ReadPlayer1Choice()
{
	short Choice = 1;
	do
	{
		cout << "Your Choice [1]Stone , [2]Paper , [3]Scissors : ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enChoice)Choice; 
}

string ChoiceName(enChoice Choice)
{
	string ArrChoiceName[3] = { "Stone" , "Paper" , "Scissors" };
	return ArrChoiceName[Choice-1];
}

string WinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = { "Player1" , "Computer" , "NoWinner" };
	return ArrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo )
{
	if (RoundInfo.ComputerChoice == RoundInfo.Player1Choice)
		return enWinner::Draw;
	switch (RoundInfo.Player1Choice)
	{
	case(enChoice ::Stone):
		if (RoundInfo.ComputerChoice == enChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case(enChoice::Paper):
		if (RoundInfo.ComputerChoice == enChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case(enChoice::Scissors):
		if (RoundInfo.ComputerChoice == enChoice::Stone)
		{
			return enWinner::Computer;
		}
		break; 
	}
	return enWinner::player1;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::player1;
	else if (Player1WinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

void SetScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::player1:
		system("color 2F");
		break; 
	case enWinner ::Computer:
		system("color 4F");
		cout << "\a";
		break; 
	default:
		system("color 6F");
		break;
	}
		
}

void PrintRoundInfo(stRoundInfo RoundInfo)
{
	cout << "\n------------Round[" << RoundInfo.RoundNumber << "]-------------\n\n";
	cout << "Player1Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "ComputerChoice : " << ChoiceName(RoundInfo.ComputerChoice) << endl; 
	cout << "Winner Name : " << RoundInfo.WinnerName << endl; 
	cout << "------------------------------------------\n" << endl;
	SetScreenColor(RoundInfo.Winner);
}

stGameResult FillGameResults(short Rounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResult GameResult;
	GameResult.GameRounds = Rounds; 
	GameResult.Player1WinTimes=Player1WinTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResult.FinalWinner = WinnerName(GameResult.GameWinner);
	return GameResult;
}

stGameResult PlayGame(short Rounds)
{
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	stRoundInfo RoundInfo; 
	for (short GameRound = 1; GameRound <= Rounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins \n";
		RoundInfo.RoundNumber = GameRound; 
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
		PrintRoundInfo(RoundInfo);
		SetScreenColor(RoundInfo.Winner);
		if (RoundInfo.Winner == enWinner::player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;
	}
	return FillGameResults(Rounds , Player1WinTimes , ComputerWinTimes , DrawTimes);
}

string Tab(short NumOfTabs)
{
	string t = "";
	for (short i = 1; i <= NumOfTabs; i++)
	{
		t = t + "\t";
	}
	return t; 
}

void PrintGameResult(stGameResult GameResult )
{
	cout <<Tab(2) <<  "-------------GameResult------------------\n\n";
	cout << Tab(2) << "Game Rounds :" << GameResult.GameRounds << endl;
	cout << Tab(2) << "Player Won Times : " << GameResult.Player1WinTimes << endl;
	cout << Tab(2) << "Computer Won Times : " << GameResult.ComputerWinTimes << endl;
	cout << Tab(2) << "FinalWinner : " << GameResult.FinalWinner << endl;
	cout << Tab(2) << "------------------------------------------\n";
}

short ReadHowManyRounds()
{
	short Rounds = 1;
	do
	{
		cout << "How Many Rounds Do You Want To Play From 1 To 10 : ";
		cin >> Rounds; 
	} while (Rounds < 1 || Rounds >10);
	return Rounds;

}

void GameOverScreen()
{
	cout << Tab(2) << "--------------------------\n\n";
	cout << Tab(2) << "+++G A M E O V E R +++\n";
	cout << Tab(2) << "-----------------------------\n\n";
}

void ResetGame()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'y';
	do
	{
		ResetGame();
		stGameResult GameResult = PlayGame(ReadHowManyRounds());
		GameOverScreen();
		PrintGameResult(GameResult);
		SetScreenColor(GameResult.GameWinner);
		cout << "Do You Want To Play Again (Y/N) : ";
		cin >> PlayAgain; 
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}