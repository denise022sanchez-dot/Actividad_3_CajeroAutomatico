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


	const int TOTAL_CUENTAS = 3;
	Cuenta cuentas[TOTAL_CUENTAS] = {
		{1001, 1234, 5000.00, "Juan Perez"},
		{1002, 4321, 1500.50, "Maria Lopez"},
		{1003, 1111, 300.00,  "Carlos Ruiz"}
	};

	int opcion = 0;
	int numCuentaIngresado, nipIngresado;

	Cuenta* cuentaActual = nullptr;



	return 0;


}

Cuenta* buscarCuenta(Cuenta cuentas[], int tamano, int numCuenta) {
	for (int i = 0; i < tamano; i++) {
		if (cuentas[i].numeroCuenta == numCuenta) {
			return &cuentas[i];
		}

	}
}


