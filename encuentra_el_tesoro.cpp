#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef vector<char> Row;
typedef vector<Row> Matrix;

char squares[] = {'*','+','|','t'};

Matrix generateMap(int dif, pair<int,int> &initialPos, bool randAct = false) {

	Matrix map;

	initialPos = make_pair<int, int>(0, 0);

	if (randAct) {
		// generació aleatoria del mapa.
		bool assignat = false;
		bool assignap = false;

		srand(time(NULL));
		int azar;

		char c;

		for (int i = 0; i < map.size(); ++i)
		{
			for(int j = 0; j < map[0].size(); ++j) {
				if(not assignat and not assignap) {
					azar = rand()%4;
					c = squares[azar];
					map[i][j] = c;
					if(c == 't') assignat = true;
					else if (c == '+') assignap = true;
				}
				else if(not assignat and assignap){
					azar = rand()%4;
					c = squares[azar];

					if(azar == '+') c = '*';

					map[i][j] = c;
					if(c == 't') assignat = true;
				}
				else if(not assignap and assignat) {
					azar = rand()%4;
					c = squares[azar];

					if(azar == 't') c = '*';

					map[i][j] = c;
					if(c == '+') assignap = true;
				}
				else {
					azar = rand()%4;
					c = squares[azar];

					if(azar == '+') c = '*';
					else if(azar == 't') c = '|';

					map[i][j] = c;
				}
			}
		}
	}

	else {
		//generació standard de mapa:
		if (dif == 0) {

			map = {{'+','*','|','t'},
					{'*','|','*','*'},
					{'*','*','*','|'},
					{'|','|','*','*'}};
			
			initialPos = make_pair<int, int>(0, 0);

		} else if (dif == 1) {

			map = {{'|','|','*','|'},
				{'|','|','*','*'},
				{'|','*','*','*'},
				{'|','*','|','|'},
				{'|','*','|','|'},
				{'*','*','*','*'},
				{'*','|','|','*'},
				{'*','|','|','+'},
				{'*','*','t','|'}};
			
			initialPos = make_pair<int, int>(7, 3);

		} else {  // maximum difficulty. 
			map = {{'|','|','+','|'},
				{'|','|','*','*'},
				{'|','*','*','*'},
				{'|','*','|','|'},
				{'|','*','|','|'},
				{'|','*','*','*'},
				{'|','|','|','*'},
				{'|','|','*','*'},
				{'*','*','*','*'},
				{'*','|','|','*'},
				{'*','*','|','*'},
				{'|','*','|','*'},
				{'|','*','t','|'}};
			
			initialPos = make_pair<int, int>(0, 2);
		}
	}

	return map;
}

bool correctOrden(char orden) {
	return (orden == 'a' or orden == 'w' or orden == 's' or orden == 'd' or orden == 'x');
}

bool posibleMovimiento(pair<int,int> pos, Matrix &map) {
	return (pos.first >= 0 and pos.first < map.size() and pos.second >= 0 and 
	pos.second < map[0].size() and 
	(map[pos.first][pos.second] == '*' or map[pos.first][pos.second] == 't'));
}

void pintaMap(Matrix map) {

	for(int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
} 

void ejecuta(Matrix &map, char orden, pair<int,int> &pos) {
	pair<int,int> newpos;

	if(orden == 'a') {
		newpos.second = pos.second-1;
		newpos.first = pos.first;
	}
	
	else if(orden == 's') {
		newpos.first = pos.first+1;
		newpos.second = pos.second;
	}

	else if(orden == 'd') {
		newpos.second = pos.second+1;
		newpos.first = pos.first;
	}

	else {
		newpos.first = pos.first-1;
		newpos.second = pos.second;
	}


	if(posibleMovimiento(newpos,map)) {

		map[pos.first][pos.second] = '*';

		if (map[newpos.first][newpos.second] == 't') map[newpos.first][newpos.second] = 'T';
		else map[newpos.first][newpos.second] = '+';

		pos = newpos;
	}
}


int main() {
	
	bool trobat = false;
	char orden;
	pair<int,int> pos;
	int count = 0;
	int dificultad;

	cout << "Primero escoga la dificultad: 0-facil, 1-medio y 2-dificil" << endl;
	cin >> dificultad;

	Matrix map = generateMap(dificultad, pos);

	pintaMap(map);

	cout << "Usted es '+' y tiene que llegar al tesoro, muevase con las teclas w,a,s,d o x " <<
	"para finalizar." << endl;
	cin >> orden;
	while(orden != 'x' and not trobat) {

		while(not correctOrden(orden)) {
			cout << "Muevase con las teclas w,a,s,d o X para finalizar" << endl;
			cin >> orden;
		}

		ejecuta(map,orden,pos);

		++count;
		if(map[pos.first][pos.second] == 'T') trobat = true;

		pintaMap(map);

		if(not trobat) {
			cout << "Usted es '+' y tiene que llegar al tesoro, " << 
			"muevase con las teclas w,a,s,d o x para finalizar." << endl;
			cin >> orden;
		}
	}

	if(trobat) 
		cout << "Muy bien! Has encontrado el tesoro!! Y en tan solo " << count << " pasos."	<< endl;
}