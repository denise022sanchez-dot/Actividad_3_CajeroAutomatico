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
void mostrarMenu();


void limpiarBuffer();



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

	do {

		system("cls");

		cout << "================================" << endl;
		cout << "  SISTEMA DE CAJERO AUTOMATICO  " << endl;
		cout << "================================" << endl;

		if (cuentaActual == nullptr) {
			cout << "\n--- INICIO DE SESION ---" << endl;
			cout << "Ingrese su numero de cuenta: ";

			if (!(cin >> numCuentaIngresado)) {
				cout << "Error: Entrada no valida. " << endl;
				limpiarBuffer();
				system("pause");
				continue;
			}

			cuentaActual = buscarCuenta(cuentas, TOTAL_CUENTAS, numCuentaIngresado);

			if (cuentaActual != nullptr) {
				cout << "Ingrese su NIP: ";
				if (!(cin >> nipIngresado)) {
					cout << "Error: NIP no valido." << endl;
					limpiarBuffer();
					cuentaActual = nullptr;
				}
				else {
					//Se verifica que la contraseña sea la correcta
					if (cuentaActual->nip != nipIngresado) {
						cout << "NIP incorrecto." << endl;
						cuentaActual = nullptr; // Resetear sesión
					}
					else {
						cout << "\nBienvenido/a " << cuentaActual->nombreTitular << endl;
					}
				}
			}
			else {
				cout << "La cuenta no existe." << endl;
			}
			system("pause");
		}

		else {
			mostrarMenu();
			cout << "Seleccione una opcion: ";


			try {
				if (!(cin >> opcion)) {
					throw runtime_error("La opcion debe ser un numero.");
				}

				switch (opcion) {
				case 1:
					break;

				case 2:
					break;

				case 3:
					break;

				case 4:
					break;

				case 5:
					break;

				case 6:
					break;

				default:
					cout << "Opcion no reconocida." << endl;
				}

			}
			catch (const exception& e) {
				// Captura errores de lógica (saldo insuficiente) o entrada
				cout << "\n>>> ERROR DEL SISTEMA: " << e.what() << " <<<" << endl;
				limpiarBuffer();
			}

			system("pause");
		}
	} while (true);

	return 0;


}

Cuenta* buscarCuenta(Cuenta cuentas[], int tamano, int numCuenta) {
	for (int i = 0; i < tamano; i++) {
		if (cuentas[i].numeroCuenta == numCuenta) {
			return &cuentas[i];
		}

	}
}

void mostrarMenu() {
	cout << "\n--- MENU PRINCIPAL ---" << endl;
	cout << "1. Consultar Saldo" << endl;
	cout << "2. Retirar Efectivo" << endl;
	cout << "3. Depositar Fondos" << endl;
	cout << "4. Transferir a otra cuenta" << endl;
	cout << "5. Cerrar Sesion" << endl;
	cout << "6. Salir del Sistema" << endl;
}



void limpiarBuffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}