#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector < vector < vector <int> > > pi;
vector < vector < vector <int> > > d;

int v_num, e_num, i, j;

void create_pi() {
	cin >> v_num;
	cin >> e_num;

	for (int i = 0; i <= v_num; i++) {
		vector < vector <int> > temp;
		for (int j = 0; j <= v_num; j++) {
			vector < int > temp_temp;
			for (int k = 0; k <= v_num; k++) {
				temp_temp.push_back(101);
			}
			temp.push_back(temp_temp);
		}
		pi.push_back(temp);
		d.push_back(temp);
	}

	for (int i = 0; i < e_num; i++) {
		int tail, head, weight;
		cin >> tail >> head >> weight;
		d[0][tail][head] = weight;
	}

	for (int i = 1; i <= v_num; i++) {
		for (int j = 1; j <= v_num; j++) {
			if (i == j || d[0][i][j] == 101) {
				pi[0][i][j] = -1;
			} else {
				pi[0][i][j] = i;
			}
		}
	}

	for (int i = 1; i <= v_num; i++) {
		for (int j = 1; j <= v_num; j++) {
			for (int k = 1; k <=v_num; k++) {

				d[i][j][k] = min(d[i-1][j][k],
								 d[i-1][j][i] + d[i-1][i][k]);
				
				if (d[i-1][j][k] <= d[i-1][j][i] + d[i-1][i][k]) {
					pi[i][j][k] = pi[i-1][j][k];
				} else {
					pi[i][j][k] = pi[i-1][i][k];
				}
			}
		}
	}
}

void print_path() {
	int first, end;
	cin >> first >> end;
	if (first == end) {
		cout << first << endl;
		cout << 0 << endl;
		return;
	}
	// cout << "first: " << first << ". end: " << end <<endl;
	int sum=d[v_num][first][end];
	vector <int> array;

	while (pi[v_num][first][end] != -1) {
		array.push_back(end);
		// cout <<"cur weight: "<<d[v_num][first][end]<<endl;
		end = pi[v_num][first][end];
	}
	array.push_back(first);

	for (int i = array.size() - 1; i >=0; i--) {
		cout << array[i] << endl;
	}
	if (array.size() < 2 && sum == 101) {
		cout << "INFINITY" <<endl;
		return;
	}
	cout << sum <<endl;
}

int main(int argc, char const *argv[])
{
	create_pi();
	print_path();
	return 0;
}