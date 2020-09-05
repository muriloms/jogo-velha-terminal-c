#include <iostream>

class ABoard 
{
public:
	ABoard()
	{
		for (int RowIndex = 0; RowIndex < 3; ++RowIndex)
		{
			for (int ColumnIndex = 0; ColumnIndex < 3; ++ColumnIndex)
			{
				Board[RowIndex][ColumnIndex] = ' ';
			}
		}
	}

	char GetValue(int Row, int Column) const
	{
		return Board[Row][Column];
	}

	void SetValue(int Row, int Columns, char Value)
	{
		Board[Row][Columns] = Value;
	}

	bool IsFull() const
	{
		for (int RowIndex = 0; RowIndex < 3; ++RowIndex)
		{
			for (int ColumnIndex = 0; ColumnIndex < 3; ++ColumnIndex)
			{
				if (Board[RowIndex][ColumnIndex] == ' ')
				{
					return false;
				}
			}
			return true;
		}
	}

	bool IsEmpty() const
	{
		for (int RowIndex = 0; RowIndex < 3; ++RowIndex)
		{
			for (int ColumnIndex = 0; ColumnIndex < 3; ++ColumnIndex)
			{
				if (Board[RowIndex][ColumnIndex] != ' ')
				{
					return false;
				}
			}
			return true;
		}
	}

	void Print() const
	{
		for (int RowIndex = 0; RowIndex < 3; ++RowIndex)
		{
			std::cout << "\t\t";
			for (int ColumnIndex = 0; ColumnIndex < 3; ++ColumnIndex)
			{
				std::cout << Board[RowIndex][ColumnIndex];

				if (ColumnIndex < 2)
				{
					std::cout << " | ";
				}
			}
			std::cout << std::endl;

			if (RowIndex < 2)
			{
				std::cout << "\t\t----------" << std::endl;
			}
		}
		std::cout << std::endl;
	}

private: 
	char Board[3][3];
};

class APlayer
{
public:
	virtual const char* GetName() = 0;
	virtual void MakeMove(const ABoard* Board, int& Row, int& Columns) = 0;
};

class AHumanPlayer : public APlayer
{
public:
	const char* GetName() override
	{
		return "Player";
	}

	void MakeMove(const ABoard* Board, int& Row, int& Column) override
	{
		int Input = ReadInput();

		Row = 2 - (Input - 1) / 3;
		Column = (Input - 1) % 3;
	}

private:
	
	int ReadInput()
	{

		while (true)
		{
			std::cout << "Faça sua jogada [1...9]: ";

			int Input;
			std::cin >> Input;

			if (1 <= Input && Input <= 9)
			{
				return Input;
			}
			else
			{
				std::cout << "Jogada invalida, tente novamente" << std::endl;
			}
		}
		
	}
};


class AAIPlayer : public APlayer
{
public:
	const char* GetName() override
	{
		return "Jogador IA";
	}

	void MakeMove(const ABoard* Board, int& Row, int& Column) override
	{
		for (int RowIndex = 0; RowIndex < 3; ++RowIndex)
		{
			for (int ColumnIndex = 0; ColumnIndex < 3; ++ColumnIndex)
			{
				if (Board->GetValue(RowIndex, ColumnIndex) == ' ')
				{
					Row = RowIndex;
					Column = ColumnIndex;
					return;
				}
			}
		}
	}
};

class AGame
{
public:

	enum class GameResult
	{
		NotOver,
		Player1,
		Player2,
		Draw
	};

	AGame()
	{
		Player1 = new AHumanPlayer;
		Player2 = new AAIPlayer;
	}

	~AGame()
	{
		delete Player1;
		delete Player2;
	}

	bool IsALine(char A, char B, char C)
	{
		return A != ' ' && A == B && B == C;
	}

	void SetGameOver()
	{
		bIsGameOver = true;
		if (bIsPlayer1Turn)
		{
			Result = GameResult::Player1;
		}
		else
		{
			Result = GameResult::Player2;
		}
	}

	void CheckIsGameOver()
	{
		if (Board.IsEmpty())
		{
			return;
		}

		// Verificar as linhas
		for (int RowIndex = 0; RowIndex < 3; ++RowIndex)
		{
			char Col0 = Board.GetValue(RowIndex, 0);
			char Col1 = Board.GetValue(RowIndex, 1);
			char Col2 = Board.GetValue(RowIndex, 2);

			if (IsALine(Col0, Col1, Col2))
			{
				
				SetGameOver();
				return;
			}
		}

		// Verificar as colunas
		for (int ColumnIndex = 0; ColumnIndex < 3; ++ColumnIndex)
		{
			char Row0 = Board.GetValue(0, ColumnIndex);
			char Row1 = Board.GetValue(1, ColumnIndex);
			char Row2 = Board.GetValue(2, ColumnIndex);

			if (IsALine(Row0, Row1, Row2))
			{

				SetGameOver();
				return;
			}
		}

		// Verificar as diagonais
		char Diag0 = Board.GetValue(0, 0);
		char Diag1 = Board.GetValue(1, 1);
		char Diag2 = Board.GetValue(2, 2);

		if (IsALine(Diag0, Diag1, Diag2)) {
			SetGameOver();
			return;
		}

		Diag0 = Board.GetValue(0, 2);
		Diag2 = Board.GetValue(2, 0);

		if (IsALine(Diag0, Diag1, Diag2)) {
			SetGameOver();
			return;
		}

		if (Board.IsFull())
		{
			bIsGameOver = true;
			Result = GameResult::Draw;
			return;
		}
	}

	void PrintResult()
	{
		switch (Result)
		{
			case GameResult::Draw:
				std::cout << "Empate" << std::endl;
				break;

			case GameResult::Player1:
				std::cout << Player1->GetName() <<" Ganhou" << std::endl;
				break;

			case GameResult::Player2:
				std::cout << Player2->GetName()<< " Ganhu" << std::endl;
				break; 

			default:
				break;

		}
	}

	bool Play(int Row, int Column, char Value)
	{
		if (Board.GetValue(Row, Column) == ' ')
		{
			Board.SetValue(Row, Column, Value);
			return true;
		}
		else
		{
			return false;
		}
	}
	void NextMove()
	{
		int Row, Column;
		if (bIsPlayer1Turn)
		{
			Player1->MakeMove(&Board, Row, Column);
		}
		else
		{
			Player2->MakeMove(&Board, Row, Column);
		}

		bool bIsMoveValid = Play(Row, Column, bIsPlayer1Turn ? 'X' : 'O');

		if (bIsMoveValid)
		{
			CheckIsGameOver();

			bIsPlayer1Turn = !bIsPlayer1Turn;
		}
	}

	APlayer* Player1;
	APlayer* Player2;
	ABoard Board;
	bool bIsGameOver = false;
	bool bIsPlayer1Turn = true;

	GameResult Result = GameResult::NotOver;
};

void TestBoard()
{
	ABoard Board;

	Board.Print();

	Board.SetValue(2, 2, 'o');
	Board.Print();
}


void TestHumanPlayer()
{
	AHumanPlayer Player;
	ABoard Board;

	int Row, Column;
	Player.MakeMove(&Board, Row, Column);

	std::cout << "Row: " << Row << " Column: " << Column << std::endl;
}

void TestAIPlayer()
{
	AAIPlayer Player;
	ABoard Board;

	int Row, Column;
	Player.MakeMove(&Board, Row, Column);

	std::cout << "Row: " << Row << " Column: " << Column << std::endl;
}

int main()
{

	AGame Game;

	while (!Game.bIsGameOver)
	{
		Game.Board.Print();

		Game.NextMove();
	}

	Game.Board.Print();
	Game.PrintResult();

	return 0;

};