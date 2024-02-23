#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <queue>
#include <unordered_set>

using namespace std;

int cost_move;
int n;

struct NPuzzleState
{
    vector<vector<int>> BoardGame;
    int index_length;
    int index_width;

    NPuzzleState(vector<vector<int>> board, int length, int width)
        : BoardGame(board), index_length(length), index_width(width) {}

    // Hàm băm tùy chỉnh để biểu diễn trạng thái
    string hash() const
    {
        string hashStr;
        for (const auto &row : BoardGame)
        {
            for (int val : row)
            {
                hashStr += to_string(val) + ",";
            }
        }
        return hashStr;
    }
};

bool operator>(const NPuzzleState &lhs, const NPuzzleState &rhs)
{
    return lhs.index_length > rhs.index_length;
}

void Input(vector<vector<int>> &BroadGame, int &index_length_start, int &index_width_start)
{
    cout << "Nhap kich thuoc ma tran n (n < 10): ";
    cin >> n;
    BroadGame.resize(n, vector<int>(n, 0));

    int index = 1;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> BroadGame[i][j];

            if (BroadGame[i][j] == 0)
            {
                index_length_start = i;
                index_width_start = j;
            }
        }
    }
}

void PrintBoardGame(const vector<vector<int>> &BroadGame)
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

int CalculateHeuristic(const vector<vector<int>> &BoardGame)
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

vector<vector<int>> UpdateBoardGame(const vector<vector<int>> &BoardGame, int x, int y, int x_, int y_)
{
    vector<vector<int>> BoardGame_ = BoardGame;
    int value = BoardGame_[x][y];
    BoardGame_[x][y] = BoardGame_[x_][y_];
    BoardGame_[x_][y_] = value;

    return BoardGame_;
}

bool StatusGame(const vector<vector<int>> &BoardGame)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (BoardGame[i][j] != (i * n + j + 1))
            {
                return false;
            }
        }
    }

    return true;
}

bool hasVisited(const unordered_set<string> &visited, const NPuzzleState &state)
{
    return visited.count(state.hash()) > 0;
}

void A(vector<vector<int>> BoardGame, int index_length_start, int index_width_start)
{
    if (StatusGame(BoardGame))
    {
        cout << "Win.....\n" << endl;
        PrintBoardGame(BoardGame);
        cout << endl;
        cout << cost_move;
        exit(0);
    }

    vector<int> x_ = {-1, 0, 1, 0};
    vector<int> y_ = {0, -1, 0, 1};
    priority_queue<NPuzzleState, vector<NPuzzleState>, greater<NPuzzleState>> p;
    unordered_set<string> visited;

    p.push(NPuzzleState(BoardGame, index_length_start, index_width_start));

    while (!p.empty())
    {
        NPuzzleState q = p.top();
        p.pop();

        if (StatusGame(q.BoardGame))
        {
            cout << "Win.....\n" << endl;
            PrintBoardGame(q.BoardGame);
            cout << endl;
            cout << cost_move;
            break;
        }

        if (hasVisited(visited, q))
        {
            continue; // Trạng thái đã thăm, bỏ qua
        }

        visited.insert(q.hash());

        for (int i = 0; i < 4; i++)
        {
            if (isValidToMove(q.index_length + y_[i], q.index_width + x_[i]))
            {
                vector<vector<int>> BoardGame_ = UpdateBoardGame(q.BoardGame, q.index_length, q.index_width, q.index_length + y_[i], q.index_width + x_[i]);
                int Heuristic_ = CalculateHeuristic(BoardGame_);
                p.push(NPuzzleState(BoardGame_, q.index_length + y_[i], q.index_width + x_[i]));
            }
        }

        cost_move++;

        PrintBoardGame(q.BoardGame);

        BoardGame = q.BoardGame;
    }

    if (StatusGame(BoardGame))
    {
        cout << "Win.....\n" << endl;
        PrintBoardGame(BoardGame);
        cout << endl;
        cout << cost_move;
    } else 
    {
        cout << "Không thể xếp được";
    }
}

int main()
{
    vector<vector<int>> BroadGame;
    int index_length_start, index_width_start;

    Input(BroadGame, index_length_start, index_width_start);

    cout << "Initial Puzzle State:\n";
    PrintBoardGame(BroadGame);

    // Call A* algorithm
    A(BroadGame, index_length_start, index_width_start);



    return 0;
}
