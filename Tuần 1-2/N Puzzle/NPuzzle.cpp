#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <queue>

using namespace std;

int cost_move;
int n;

struct NPuzzle
{
    vector< vector<int> > BoardGame; 
    int index_length;
    int index_width;
    int heuristic;

    NPuzzle(vector< vector<int> > BoardGame, int x, int y, int z)
    {
        this->BoardGame = BoardGame;
        this->index_length = x;
        this->index_width = y;
        this->heuristic = z;
    }

    bool operator>(const NPuzzle& orther) const 
    {
        return this->heuristic > orther.heuristic;
    }
};


void Input(vector<vector<int>>& BroadGame, int& index_length_start, int& index_width_start)
{
    cout << "Nhap kich thuoc ma tran n (n < 10): ";
    cin >> n;
    BroadGame.resize(n, vector<int>(n, 0));

    vector<int> values;
    for (int i = 0; i < n * n; ++i)
    {
        values.push_back(i);
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(values.begin(), values.end(), g);

    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            BroadGame[i][j] = values[index++];

            if (BroadGame[i][j] == 0)
            {
                index_length_start = i;
                index_width_start = j;
            }
        }
    }
}

void PrintBoardGame(vector<vector<int>> BroadGame)
{
    for (int i = 0; i < n; i++)
    {
        cout << "| ";
        for (int j = 0; j < n; j++)
        {
            cout << BroadGame[i][j] << " | ";
        }
        cout << endl;
    }

    cout << endl;
}

int CalculateHeuristic(vector< vector<int> > BoardGame)
{
    int Heuristic = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) 
        {
            int index_x = BoardGame[i][j] % n - 1;
            int index_y = BoardGame[i][j] / n;

            Heuristic += abs(index_x - i) + abs(index_y - j);
        }
    }

    return Heuristic;
}

bool isValidToMove(int x, int y)
{
    return (x < n && x >= 0) && (y < n && y >= 0);
}

vector< vector<int> > UpdateBoardGame(vector< vector<int> > BoardGame, int x, int y, int x_, int y_)
{
    vector< vector<int> > BoardGame_ = BoardGame;
    int value = BoardGame_[x][y];
    BoardGame_[x][y] = BoardGame_[x_][y_];
    BoardGame_[x_][y_] = value;

    return BoardGame_;
}

bool StatusGame(vector< vector<int> > BoardGame)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (BoardGame[n - 1][n - 1] == 0)
            {
                return true;
            }

            if (BoardGame[i][j] != (i * n + j + 1))
            {
                return false;
            }
        }
    }

    return false;
}

void A_Star(vector< vector<int> > BoardGame, int index_length_start, int index_width_start)
{
    vector<int> x_ = {-1, 0, 1, 0};
    vector<int> y_ = {0, -1, 0, 1};
    priority_queue< NPuzzle, vector<NPuzzle>, greater<NPuzzle> > p;
    p.push(NPuzzle(BoardGame, index_length_start, index_width_start, CalculateHeuristic(BoardGame) + cost_move));
    NPuzzle q = p.top();
    p.pop();

    for (int i = 0; i < 4; i++)
    {
        if (isValidToMove(q.index_length + y_[i], q.index_width + x_[i]))
        {
            vector<vector<int>> BoardGame_ = UpdateBoardGame(q.BoardGame, q.index_length, q.index_width, q.index_length + y_[i], q.index_width + x_[i]);
            int Heuristic_ = CalculateHeuristic(BoardGame_);
            p.push(NPuzzle(BoardGame_, q.index_length + y_[i], q.index_width + x_[i], Heuristic_ + cost_move + 1));
        }
    }

    while(!p.empty())
    {
        NPuzzle q_ = p.top(); p.pop();
        cost_move++;

        PrintBoardGame(q.BoardGame);
        
        if (StatusGame(q_.BoardGame))
        {
            cout << cost_move;
        }

        for (int i = 0; i < 4; i++)
        {
            if (isValidToMove(q.index_length + y_[i], q.index_width + x_[i]))
            {
                vector<vector<int>> BoardGame_ = UpdateBoardGame(q.BoardGame, q.index_length, q.index_width, q.index_length + y_[i], q.index_width + x_[i]);
                int Heuristic = CalculateHeuristic(BoardGame_);
                p.push(NPuzzle(BoardGame_, q.index_length + y_[i], q.index_width + x_[i], Heuristic + cost_move + 1));
            }
        }
    }
}

int main()
{
    vector<vector<int>> BroadGame;
    int index_length_start, index_width_start;

    Input(BroadGame, index_length_start, index_width_start);

    cout << "Initial Puzzle State:\n";
    PrintBoardGame(BroadGame);

    A_Star(BroadGame, index_length_start, index_width_start);

    return 0;
}
