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
void consultarSaldo(const Cuenta* cuenta);
void depositar(Cuenta* cuenta);
void retirar(Cuenta* cuenta);
void transferir(Cuenta* origen, Cuenta cuentas[], int tamano);
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

// Busca una cuenta en el arreglo y devuelve su puntero o nullptr si no existe
Cuenta* buscarCuenta(Cuenta cuentas[], int tamano, int numCuenta) {
	for (int i = 0; i < tamano; i++) {
		if (cuentas[i].numeroCuenta == numCuenta) {
			return &cuentas[i]; //Devuelve la dirección de memoria de la cuenta
		}

	}
	return nullptr;
}

//Simplemnte se muestra el menu
void mostrarMenu() {
	cout << "\n--- MENU PRINCIPAL ---" << endl;
	cout << "1. Consultar Saldo" << endl;
	cout << "2. Retirar Efectivo" << endl;
	cout << "3. Depositar Fondos" << endl;
	cout << "4. Transferir a otra cuenta" << endl;
	cout << "5. Cerrar Sesion" << endl;
	cout << "6. Salir del Sistema" << endl;
}

//Esta funcion recibe un puntero constante "cuenta", asegurando que NO se modificará el saldo por accidente aquí
void consultarSaldo(const Cuenta* cuenta) {
	cout << "\n--- ESTADO DE CUENTA ---" << endl;
	cout << "Titular: " << cuenta->nombreTitular << endl;
	cout << "Saldo actual: $" << cuenta->saldo << endl;
}

void depositar(Cuenta* cuenta) {
	double monto;
	cout << "\nIngrese monto a depositar: $";
	if (!(cin >> monto) || monto <= 0) {
		//'throw' lanza el error hacia el bloque catch en el main.
		throw runtime_error("Monto invalido. Debe ser un numero positivo.");
	}

	cuenta->saldo += monto; // Modifica el saldo original en memoria
	cout << "Deposito exitoso. Nuevo saldo: $" << cuenta->saldo << endl;
}


//Se valida que el monto a retirar este dentro del rango del slado
//Si el monto a retirar es mayor que el saldo, muestra mensaje de error
void retirar(Cuenta* cuenta) {
	double monto;
	cout << "\nIngrese monto a retirar: $";
	if (!(cin >> monto) || monto <= 0) {
		throw runtime_error("Monto invalido.");
	}

	if (monto > cuenta->saldo) {
		throw runtime_error("Saldo insuficiente para realizar el retiro.");
	}

	cuenta->saldo -= monto;
	cout << "Retiro exitoso. Nuevo saldo: $" << cuenta->saldo << endl;
}

//En esta funcion se manejan dos punteros Origen y Destino
void transferir(Cuenta* origen, Cuenta cuentas[], int tamano) {
	int numDestino;
	double monto;

	cout << "\n--- TRANSFERENCIA ---" << endl;
	cout << "Ingrese numero de cuenta destino: ";
	if (!(cin >> numDestino)) throw runtime_error("Numero de cuenta invalido.");

	if (numDestino == origen->numeroCuenta) {
		throw runtime_error("No puede transferirse dinero a si mismo.");
	}

	//Llamamos a buscarCuenta para obtener el puntero del destino.
	Cuenta* destino = buscarCuenta(cuentas, tamano, numDestino);

	if (destino == nullptr) {
		throw runtime_error("La cuenta destino no existe.");
	}

	cout << "Cuenta encontrada: " << destino->nombreTitular << endl;
	cout << "Ingrese monto a transferir: $";
	if (!(cin >> monto) || monto <= 0) throw runtime_error("Monto invalido.");

	if (monto > origen->saldo) {
		throw runtime_error("Saldo insuficiente.");
	}

	//Se reliza la transferencia, se resta de una cuenta y sumamos a la otrani
	origen->saldo -= monto;
	destino->saldo += monto;

	cout << "Transferencia exitosa." << endl;
	cout << "Su nuevo saldo es: $" << origen->saldo << endl;
}

//Función auxiliar para limpiar cin cuando el usuario ingresa letras en vez de números
void limpiarBuffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}