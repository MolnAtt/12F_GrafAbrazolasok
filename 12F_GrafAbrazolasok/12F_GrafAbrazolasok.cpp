
#include <iostream>

#include <vector>
using namespace std;

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




	~CsucslistasGraf()
	{
	}

private:

};


int main()
{
	CsucslistasGraf cslgraf;

	cslgraf.diagnostics();
		
		
		
	
}
