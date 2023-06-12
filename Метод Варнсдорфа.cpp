#include <iostream> 
#include <vector>
#define Size_Of_Chess_Board (8) 
using namespace std;
int Chess[Size_Of_Chess_Board][Size_Of_Chess_Board];
int step[8][2]{ {1, -2}, { 1, 2}, {-1, 2}, {-1, -2}, {2, 1}, {-2, -1}, {2, -1}, {-2, 1} };
int Horse = 0;
void Initialization(int x, int y)
{
    for (int i = 0; i < Size_Of_Chess_Board; i++)
    {
        for (int j = 0; j < Size_Of_Chess_Board; j++)
        {
            Chess[i][j] = 0;
            if (i == y && j == x)
                Chess[i][j] = ++Horse;
        }
    }
}
void Print(int arr[][Size_Of_Chess_Board])
{
    for (int i = 0; i < Size_Of_Chess_Board; i++)
    {
        for (int j = 0; j < Size_Of_Chess_Board; j++)
            cout << arr[i][j] << "\t  ";
        cout << endl;
    }
    cout << endl;
}
int ProbablyStep(int x, int y)
{
    int count = 0;
    if (x < Size_Of_Chess_Board && x >= 0 && y < Size_Of_Chess_Board && y >= 0 && Chess[y][x] == 0)
    {
        for (int i = 0; i < Size_Of_Chess_Board; i++)
            if (x + step[i][0] < Size_Of_Chess_Board && x + step[i][0] >= 0 && y + step[i][1] < Size_Of_Chess_Board && y + step[i][1] >= 0 && Chess[y + step[i][1]][x + step[i][0]] == 0)
                count++;
    }
    else return INT_MAX;
    return count;
}
void Vandsdorf(int& x, int& y)
{
    vector <int> temp;
    int count = INT_MAX;
    for (int i = 0; i < Size_Of_Chess_Board; i++)
    {
        int x1, y1;
        x1 = x;
        y1 = y;
        x1 = step[i][0] + x;
        y1 = step[i][1] + y;
        temp.push_back(ProbablyStep(x1, y1));
        for (int j = 0; j < temp.size(); j++)
            count = min(temp[j], count);

    }
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] == count && Chess[y + step[i][1]][x + step[i][0]] == 0)
        {
            x += step[i][0];
            y += step[i][1];
            Chess[y][x] = ++Horse;
            break;
        }
    }
}
int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
#pragma region 1 
    int x, y;
    cout << "Введите координаты клетки: " << endl;
    cin >> x >> y;
    Initialization(x, y);
    while (Horse != Size_Of_Chess_Board * Size_Of_Chess_Board)
        Vandsdorf(x, y);
    Print(Chess);
#pragma endregion 
}