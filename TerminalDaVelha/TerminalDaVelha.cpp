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

	TestAIPlayer();

	return 0;

};