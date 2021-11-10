
/*
tesztinput:

6 7
0 1
1 4
3 1
3 5
2 0
2 3
1 2

*/





#include <iostream>

#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

#include <algorithm>

class CsucslistasGraf
{
public:
	vector<vector<int>>* csucslista;
	int N;
	int M;

	CsucslistasGraf()
	{
		cin >> N >> M;

		csucslista = new vector<vector<int>>(N, vector<int>());


		for (int i = 0; i < M; i++)
		{
			int honnan;
			int hova;
			cin >> honnan >> hova;

			csucslista->at(honnan).push_back(hova);
			if (honnan != hova)
			{
				(*csucslista)[hova].push_back(honnan);
			}
		}
	}

	void diagnostics()
	{
		for (int i = 0; i < N; i++)
		{
			cout << i << ": [ ";
			for (auto& szomszed : csucslista->at(i))
			{
				cout << szomszed << " ";
			}
			cout << "]\n";
		}
	}

	bool van_el(int a, int b) // sebesség: <=n
	{
		int i = 0;
		while (i < csucslista->at(a).size() && csucslista->at(a)[i] != b)
		{
			i++;
		}
		return i != csucslista->at(a).size();

		/* ezt nem én írtam
		for (auto& elem : csucslista->at(a))
		{
			if (elem == b) { return true; }
		}
		return false;
		*/
	}

	void add_edge(int a, int b) // <=n 
	{
		if (!van_el(a, b))
		{
			(*csucslista)[a].push_back(b);
			if (a != b)
			{
				(*csucslista)[b].push_back(a);
			}
			M++;
		}
	}



	void remove_edge(int a, int b)
	{
		pair<int, int> ittvannak = helye(a, b);
		if (ittvannak.first < csucslista->at(a).size())
		{
			remove_vektorbol(csucslista->at(a), ittvannak.first);
			if (a != b)
			{
				remove_vektorbol(csucslista->at(b), ittvannak.second);
			}
			M--;
		}
		else
		{
			cerr << "nincs is ilyen el!";
		}
	}

	void add_node()
	{
		csucslista->push_back(vector<int>());
		N++;
	};
	// void remove_node_with_edges(int a); // nem csináljuk meg, mert nagyon összezavar mindent. Meg kell változtatni a node-ok számozását!
	int degree(int a); // pont fokszáma
	bool loop(int a); // hurokél
	bool isolated(int a);
	int find_melysegi(int csucs, bool (*predicate)(int))
	{
		vector<string> szin(N, "feher");
		stack<int> tennivalok;
		tennivalok.push(csucs);

		while (!tennivalok.empty())
		{
			int tennivalo = tennivalok.top();
			tennivalok.pop();
			if (predicate(tennivalo)) // feldolgozás = feketére színezés
				return tennivalo;
			szin[tennivalo] = "fekete";

			for (int& szomszed : csucslista->at(tennivalo))
			{
				if (szin[szomszed] == "feher")
				{
					tennivalok.push(szomszed);
					szin[szomszed] = "szurke";
				}
			}
		}

		return -1;
	};

	int find_szelessegi(int csucs, bool (*predicate)(int))
	{
		vector<string> szin(N, "feher");
		queue<int> tennivalok;
		tennivalok.push(csucs);

		while (!tennivalok.empty())
		{
			int tennivalo = tennivalok.front();
			tennivalok.pop();
			if (predicate(tennivalo)) // feldolgozás = feketére színezés
				return tennivalo;
			szin[tennivalo] = "fekete";

			for (int& szomszed : csucslista->at(tennivalo))
			{
				if (szin[szomszed] == "feher")
				{
					tennivalok.push(szomszed);
					szin[szomszed] = "szurke";
				}
			}
		}

		return -1;
	};

	int distance(int csucs, bool (*predicate)(int))
	{
		vector<int> dist(N, -1);
		dist[csucs] = 0; // azt kötjük ki, hogy saját magától 0 távolságra van.
		vector<string> szin(N, "feher");
		queue<int> tennivalok;
		tennivalok.push(csucs);

		while (!tennivalok.empty())
		{
			int tennivalo = tennivalok.front();
			tennivalok.pop();
			if (predicate(tennivalo)) // feldolgozás = feketére színezés
				return dist[tennivalo];
			szin[tennivalo] = "fekete";

			for (int& szomszed : csucslista->at(tennivalo))
			{
				if (szin[szomszed] == "feher")
				{
					tennivalok.push(szomszed);
					dist[szomszed] = dist[tennivalo] + 1;
					szin[szomszed] = "szurke";
				}
			}
		}

		return -1;
	};

	vector<int> utvonal(int end, const vector<int>& honnan)
	{
		stack<int> verem;
		while (honnan[end]!=-2)
		{
			verem.push(end);
			end = honnan[end];
		}
		vector<int> result;
		while (!verem.empty())
		{
			result.push_back(verem.top());
			verem.pop();
		}
		return result;
	}


	vector<int> shortest_path(int csucs, bool (*predicate)(int))
	{
		vector<int> honnan(N, -1); // Amikor beszürkült, HONNAN szürkítettük be a szelessegi bejaras;
		vector<string> szin(N, "feher");
		queue<int> tennivalok;
		tennivalok.push(csucs);

		while (!tennivalok.empty())
		{
			int tennivalo = tennivalok.front();
			tennivalok.pop();
			if (predicate(tennivalo)) // feldolgozás = feketére színezés
				return utvonal(tennivalo, honnan);
			szin[tennivalo] = "fekete";

			for (int& szomszed : csucslista->at(tennivalo))
			{
				if (szin[szomszed] == "feher")
				{
					tennivalok.push(szomszed);
					honnan[szomszed] = tennivalo; // útvonalvektor
					szin[szomszed] = "szurke";
				}
			}
		}

		return vector<int>();
	};





	int count(int csucs, bool (*predicate)(int))
	{
		int db = 0;
		vector<string> szin(N, "feher");
		stack<int> tennivalok;
		tennivalok.push(csucs);

		while (!tennivalok.empty())
		{
			int tennivalo = tennivalok.top();
			tennivalok.pop();
			if (predicate(tennivalo))
				db++;
			szin[tennivalo] = "fekete";

			for (int& szomszed : csucslista->at(tennivalo))
			{
				if (szin[szomszed] == "feher")
				{
					tennivalok.push(szomszed);
					szin[szomszed] = "szurke";
				}
			}
		}
		return db;
	}
	
	vector<int> where(int csucs, bool (*predicate)(int)) 
	{
		vector<int> result;
		vector<string> szin(N, "feher");
		stack<int> tennivalok;
		tennivalok.push(csucs);

		while (!tennivalok.empty())
		{
			int tennivalo = tennivalok.top();
			tennivalok.pop();
			if (predicate(tennivalo))
				result.push_back(tennivalo);
			szin[tennivalo] = "fekete";

			for (int& szomszed : csucslista->at(tennivalo))
			{
				if (szin[szomszed] == "feher")
				{
					tennivalok.push(szomszed);
					szin[szomszed] = "szurke";
				}
			}
		}
		return result;
	}
	bool connected()
	{
		return N = 0 || (N == count(0, [](int x) {return x == x; }));

	}
	vector<int> shortest_path(int a, int b);








	~CsucslistasGraf()
	{
	}

	void remove_vektorbol(vector<int>& v, int i) {
		v.erase(v.begin() + i);
	}


private:

	pair<int, int> helye(int a, int b)
	{
		int i = 0;
		while (i < csucslista->at(a).size() && csucslista->at(a)[i] != b)
		{
			i++;
		}

		int j = 0;
		while (j < csucslista->at(b).size() && csucslista->at(b)[j] != a)
		{
			j++;
		}

		pair<int, int> p{ i,j };
		return p;
	}
};

string to_string(vector<int> v) 
{
	string sum = "[";
	for (int& i : v)
	{
		sum += " " + to_string(i);
	}
	return sum + " ]";
}

int main()
{
	CsucslistasGraf cslgraf;

	cslgraf.diagnostics();
	/*
	cout << cslgraf.van_el(0, 1)<<endl;
	
	cslgraf.add_edge(0, 3);
	cslgraf.diagnostics();

	cslgraf.add_edge(0, 1);
	cslgraf.diagnostics();


	vector<int> v{8,9,10,80,45,31,60};
	cslgraf.remove_vektorbol(v, 2);
	cerr << "[ ";
	for (auto& item : v)
	{
		cerr << item << " ";
	}
	cerr << "]\n";

	cslgraf.remove_edge(1, 3);
	cslgraf.diagnostics();

	cslgraf.remove_edge(1, 3);
	cslgraf.diagnostics();

	cout << cslgraf.find(6, [](int x) {return x == 9; }); // C# lambda, cslgraf.Where(5, x => True) // Python-lambda: cslgraf.where(5, lambda x: True)

	cout << cslgraf.count(10, [](int x) {return x%2 == 1; });

	cout << to_string(cslgraf.where(0, [](int x) {return x % 2 == 1; }));

	cout << to_string(vector<int>{7, 9, 8, 25, 96, 7, 6, 2});

	cout << cslgraf.connected();

	cout << cslgraf.distance(0, [](int n) { return n == 2; });
	*/
	cout << to_string(cslgraf.shortest_path(0, [](int n) { return n == 2; }));

}


/*
tesztinput
11 11
0 1
0 2
1 3
1 5
2 3
2 4
2 5
6 7
7 8
7 9
8 9

*/

