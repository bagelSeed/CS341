#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

typedef vector<int> ivec;
typedef vector<ivec> a_list;

a_list adj_list;

//0=white
//1=grey
//2=black
ivec color;
ivec pi;
ivec d;
ivec f;

int cur_time;

void DFSvisit(int vertex) {
	color[vertex]=1;
	cur_time++;
	d[vertex]=cur_time;
	for (int i = 0; i < adj_list[vertex-1].size(); i++) {
		if (color[adj_list[vertex-1][i]] == 0) {
			cout << vertex << " " << adj_list[vertex-1][i] <<endl;
			pi[adj_list[vertex-1][i]]=vertex;
			DFSvisit(adj_list[vertex-1][i]);
		}
	}
	color[vertex]=2;
	cur_time++;
	f[vertex]=cur_time;
}

int main(int argc, char const *argv[])
{
	/* code */
	int vertices = 0;
	cin >> vertices;
	for (int i = 0; i < vertices + 1; i++) {
		string line;
		getline(cin,line);

		// Parse
		ivec temp_list;
		int index=0;
		string num_str="";
		for (int j = 0; j < line.length(); j++) {
			if (line[j]==' ') {
				if (num_str!="") {
					int temp;
					stringstream(num_str) >> temp;
					if (!index) {
						index = temp;
					} else {
						temp_list.push_back(temp);
					}
					num_str="";
				}
				continue;
			}
			if (line[j]!=':') {
				num_str+=line[j];
				if (j == line.length()-1) {
					int temp;
					stringstream(num_str) >> temp;
					temp_list.push_back(temp);
				}
			}
		}
		if (i != 0) {
			adj_list.push_back(temp_list);
		}
	}

	for (int i = 0; i < vertices+1; i++) {
		color.push_back(0);
		pi.push_back(0);
		d.push_back(0);
		f.push_back(0);
	}
	cur_time = 0;

	for (int i = 1; i < vertices; i++) {
		if (color[i] == 0) {
			cout << i << " " << "root" << endl;
			DFSvisit(i);
		}
	}

	return 0;
}


