#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Pair_er
{
    int wide_index;
    int length_index;
    int price;

    Pair_er(int b, int n, int m)
    {
        wide_index = n;
        length_index = b;
        price = m;
    }

    bool operator>(const Pair_er &other) const
    {
        return price > other.price;
    }
};

class Algorithm
{
private:
    int length;
    int wide;
    vector<string> ArrayList;
    vector<int> hang = {-1, 0, 0, 1};
    vector<int> cot = {0, 1, -1, 0};

public:
    void input()
    {
        cout << "So hang can nhap: ";
        cin >> this->length;
        cout << "So cot can nhap: ";
        cin >> this->wide;

        cin.ignore();

        for (int i = 0; i < length; i++)
        {
            string x;
            getline(cin, x);
            this->ArrayList.push_back(x);
        }
    }

    void output()
    {
        for (int i = 0; i < length; i++)
        {
            cout << this->ArrayList[i] << endl;
        }
    }

    void DFS(int n, int m)
    {
        if (this->ArrayList[n][m] == ' ')
        {
            this->ArrayList[n][m] = 'o';

            for (int i = 0; i < 4; i++)
            {
                if (((n + this->hang[i] >= 0) && (n + this->hang[i] < length)) && ((m + this->cot[i] >= 0) && (m + this->cot[i] < wide)))
                {
                    int k = n + this->hang[i];
                    int l = m + this->cot[i];

                    if (this->ArrayList[k][l] == ' ')
                    {
                        DFS(k, l);
                    }
                }
            }
        }
    }

    void BFS(int n, int m)
    {
        queue<pair<int, int>> ListQueue;
        ListQueue.push({n, m});

        while (!ListQueue.empty())
        {
            pair<int, int> q = ListQueue.front();
            ListQueue.pop();

            if (this->ArrayList[q.first][q.second] == 'S')
            {
                break;
            }

            this->ArrayList[q.first][q.second] = 'o';

            for (int i = 0; i < 4; i++)
            {
                if (q.first + this->hang[i] >= 0 && q.first + this->hang[i] < length &&
                    q.second + this->cot[i] >= 0 && q.second + this->cot[i] < wide)
                {
                    int k = q.first + this->hang[i];
                    int l = q.second + this->cot[i];

                    if (this->ArrayList[k][l] != 'x')
                    {
                        ListQueue.push({k, l});
                    }
                }
            }
        }
    }

    void USC(int n, int m)
    {
        priority_queue<Pair_er, vector<Pair_er>, greater<Pair_er>> p;
        p.push({n, m, rand() % 100 + 1});

        while(!p.empty())
        {
            Pair_er q = p.top();
            p.pop();

            if (this->ArrayList[q.length_index][q.wide_index] == 'S')
            {
                break;
            }

            this->ArrayList[q.length_index][q.wide_index] = 'o';

            for (int i = 0; i < 4; i++)
            {
                if (q.length_index + this->hang[i] >= 0 && q.length_index + this->hang[i] < length &&
                    q.wide_index + this->cot[i] >= 0 && q.wide_index + this->cot[i] < wide)
                {
                    int f = q.length_index + this->hang[i];
                    int g = q.wide_index + this->cot[i];

                    if (this->ArrayList[f][g] != 'x')
                    {
                        p.push({f, g, rand() % 100 + 1});
                    }
                }
            }
        }
    }
};

int main()
{
    Algorithm Test;
    Test.input();

    Test.USC(1, 1);

    Test.output();

    return 0;
}