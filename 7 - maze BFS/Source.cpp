#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

struct cond {
	pair<int, int> point;
	int distance;
};

void clearMemory(int**& a, int n, int m);
void searchInMatrix(int** a, int n, int m, int who, int& xi, int& yi);
int minOrMax(int** a, int n, int m, char x);
int existsInMatrix(int l, int c, int n, int m);
void afisare(int** a, int n, int m);
void citire(int**& a, int& n, int& m);
void solutie(int** a, pair<int, int>start, pair<int, int>stop, int n, int m);

int main()
{
	int** a, n, m;
	citire(a, n, m);
	//afisare(a, n, m);
	pair<int, int> start;
	pair<int, int> stop;
	int x, y, xS, yS;
	cout << "coordonate Soricel(x, y): "; cin >> x >> y;
	cout << "coordonate Branzica(x, y): "; cin >> xS >> yS;
	//cout << "Plecam de la " << a[x][y] << " sa ajungem la " << a[xS][yS] << "\n";
	solutie(a, make_pair(x, y), make_pair(xS, yS), n, m);

	return 0;
}


void clearMemory(int**& a, int n, int m)
{
	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[] a;
}
void solutie(int** a, pair<int, int>start, pair<int, int>stop, int n, int m) {
	int neigN[] = { -1, 0, 0, 1 };
	int neigM[] = { 0, -1, 1, 0 };
	if (a[start.first][start.second] || a[stop.first][stop.second])
		cout << "Branzica este stricata\n";
	else {
		int** road; bool** freq; int ok = 0;
		freq = new bool* [n];
		for (int i = 0; i < n; i++)
			freq[i] = new bool[m] {};
		road = new int* [n];
		for (int i = 0; i < n; i++)
			road[i] = new int[m] {};
		freq[start.first][start.second] = true;
		int cityBlockDistance = abs(start.first - stop.first) + abs(start.second - stop.second);
		road[start.first][start.second] = cityBlockDistance;
		queue<cond> q;
		q.push({ start, cityBlockDistance });
		while (!q.empty()) {
			cond temp;
			temp = q.front();
			road[temp.point.first][temp.point.second] = temp.distance;
			q.pop();
			if (temp.point.first == stop.first && temp.point.second == stop.second) {
				ok = 1;
				cout << "Matricea drumului: \n";
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++)
						if (road[i][j] <= 9)
							cout << " " << road[i][j] << " ";
						else
							cout << road[i][j] << " ";
					cout << "\n";
				}
				int min, max = road[stop.first][stop.second];
				min = minOrMax(road, n, m, 'm'); // search min=m, search max=x 
				int line, col, copymax = max;
				int corX = stop.first, corY = stop.second;
				stack<pair<int, int>>s;
				s.push(make_pair(corX, corY));
				while (copymax - 1 > min) {
					for (int i = 0; i < 4; i++) {
						int linn = corX + neigN[i];
						int coll = corY + neigM[i];
						if (existsInMatrix(linn, coll, n, m))
							if (copymax - 1 == road[linn][coll])
							{
								corX = linn;
								corY = coll;
								s.push(make_pair(linn, coll));
								break;
							}
					}
					copymax--;
				}
				cout << "Coordonatele drumului: \n";
				while (!s.empty())
					cout << "(" << s.top().first << ", " << s.top().second << ")\n", s.pop();

				clearMemory(road, n, m);
				clearMemory(a, n, m);
				for (int i = 0; i < n; i++)
					delete[] freq[i];
				delete[] freq;
				break;
			}
			else {
				int l, c, min = INT_MAX, xl, xc, intrat = 0;
				for (int i = 0; i < 4; i++) {
					l = temp.point.first + neigN[i];
					c = temp.point.second + neigM[i];
					if (existsInMatrix(l, c, n, m) && !a[l][c] && !freq[l][c]) {
						cityBlockDistance = abs(l - stop.first) + abs(c - stop.second);
						if (cityBlockDistance <= min) {
							intrat = 1;
							min = cityBlockDistance;
							xl = l;
							xc = c;x
						}
						freq[xl][xc] = true;
					}
				}
				if (intrat) q.push({ make_pair(xl, xc), temp.distance + 1 });
				else {
					cout << "Drum blocat, soricelul a murit infometat\n";
					break;
				}
			}
		}
	}
}
int minOrMax(int** a, int n, int m, char x)
{
	if (x == 'm') {
		int min = INT_MAX;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (a[i][j] <= min)
					min = a[i][j];
		return min;
	}
	else if (x == 'x') {
		int max = INT_MIN;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (a[i][j] >= max)
					max = a[i][j];
		return max;
	}

}
void searchInMatrix(int** a, int n, int m, int who, int& xi, int& yi)
{
	xi = -1; yi = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (a[i][j] == who)
			{
				xi = i;
				yi = j;
				return;
			}
	}
}
int existsInMatrix(int l, int c, int n, int m)
{
	if (l >= 0 && l < n && c >= 0 && c < m)
		return 1;
	return 0;
}
void citire(int**& a, int& n, int& m) {
	fstream f("data.in", ios::in);
	f >> n >> m;
	a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			f >> a[i][j];
}
void afisare(int** a, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (a[i][j] == -1) cout << a[i][j] << " ";
			else if (a[i][j] == 0) cout << " " << a[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
}