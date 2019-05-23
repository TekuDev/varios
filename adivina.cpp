#include <iostream>
#include <cstdlib>
using namespace std;



int main() {
	int secret, count, n;
	bool trobat = false;
	count = 1;
	srand(time(NULL));
	secret = rand()%51;	
 
	cout << "Adivina el numero secreto, está entre 0 y 50" << endl;
	cin >> n;
	
	while(not trobat) {
		if (n < secret) cout << "El numero secreto es más grande, vuelve a probar:" << endl;
		
		else if (n > secret) cout << "El numero secreto es más pequeño, vuelve a probar:" << endl;
		
		else trobat = true;

		if(not trobat) {
			cin >> n;
			++count;
		}	
	}

	cout << "Lo has encontrado! El numero secreto es: " << secret << " y lo has adivinado en " << count << " intentos." << endl;
}
