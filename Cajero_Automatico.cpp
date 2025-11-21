#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>


using namespace std;

struct Cuenta {
	int numeroCuenta;
	int nip;
	double saldo;
	string nombreTitular;
};

Cuenta* buscarCuenta(Cuenta cuentas[], int tamano, int numCuenta);




int main() {





	return 0;


}

Cuenta* buscarCuenta(Cuenta cuentas[], int tamano, int numCuenta) {
	for (int i = 0; i < tamano; i++) {
		if (cuentas[i].numeroCuenta == numCuenta) {
			return &cuentas[i];
		}

	}
}


