
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
		if (!van_el(a,b))
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
	bool connected();
	int find(bool (*predicate)(int));
	int count(bool (*predicate)(int));
	int where(bool (*predicate)(int));
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


int main()
{
	CsucslistasGraf cslgraf;

	cslgraf.diagnostics();
		
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

}
