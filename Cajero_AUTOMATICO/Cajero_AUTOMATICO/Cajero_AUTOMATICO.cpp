#include <iostream> //Se declaran las librerias
#include <string>
#include <stdexcept> //Se utiliza para hacer las excepciones
#include <limits> //Para limpiar el buffer de entrada


using namespace std;

//Esta sección define el tipo de los datos.
//La estructura 'Cuenta' agrupa toda la información relacionada con un usuario
//su número de cuenta, contraseña, dinero y nombre en una sola estructura
struct Cuenta {
	int numeroCuenta;
	int nip;
	double saldo;
	string nombreTitular;
};

//Se muestran las funciones que se van a utlizar en la funcion principal y que se desarrollarán mas adelante
Cuenta* buscarCuenta(Cuenta cuentas[], int tamano, int numCuenta);
void mostrarMenu();
void consultarSaldo(const Cuenta* cuenta);
void depositar(Cuenta* cuenta);
void retirar(Cuenta* cuenta);
void transferir(Cuenta* origen, Cuenta cuentas[], int tamano);
void limpiarBuffer();


//inicia la funcion principal
int main() {

	//Se incializn los datos de las 3 cuentas
   //Se crea la base de datos local usando un arreglo de estructuras.
   //Los primero 4 digitos son del numero de cuenta, los segundos del NIP, y el tecero la cantidad
   //de dinero disponible en cada cuenta
	const int TOTAL_CUENTAS = 3;
	Cuenta cuentas[TOTAL_CUENTAS] = {
		{1001, 1234, 5000.00, "Juan Perez"},
		{1002, 4321, 1500.50, "Maria Lopez"},
		{1003, 1111, 300.00,  "Carlos Ruiz"}
	};

	int opcion = 0;
	int numCuentaIngresado, nipIngresado;

	//Se inicializa el puntero 'cuentaActual" que guardará la dirección de memoria
	// de la cuenta que ha iniciado la sesión. Si es nullptr, nadie ha entrado.
	Cuenta* cuentaActual = nullptr;// Puntero para manejar la sesión

	//El ciclo do-while mantiene el programa encendido indefinidamente
	do { 

		system("cls");

		cout << "================================" << endl;
		cout << "  SISTEMA DE CAJERO AUTOMATICO  " << endl;
		cout << "================================" << endl;

		////Esta condicional se ejecuta solo si no hay usuario dentro de la sesion. Pide cuenta y NIP.
		if (cuentaActual == nullptr) {
			cout << "\n--- INICIO DE SESION ---" << endl;
			cout << "Ingrese su numero de cuenta: ";

			//Se hace validacion, por si meten letras en lugar de numeros
			if (!(cin >> numCuentaIngresado)) {
				cout << "Error: Entrada no valida. " << endl;
				limpiarBuffer();
				system("pause");
				continue;
			}

			//Se utilizan los punteros para buscar cuenta y devuelve una dirección
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

		//Cuando el usuario ingresa sus datos correctamente muestra el menu de operaciones.
		// Contiene el manejo de excepciones y el switch de opciones.
		else {
			mostrarMenu();
			cout << "Seleccione una opcion: ";

			// Try catch envuelve las operaciones críticas. Si algo falla saldo insuficiente, entrada mala
			// se lanza una excepción que es capturada abajo para no cerrar el programa.
			try {
				if (!(cin >> opcion)) {
					throw runtime_error("La opcion debe ser un numero.");
				}

				//Segun la variable opcion, se ejcuta lo que el usuario desea hacer
				switch (opcion) {
				case 1:
					consultarSaldo(cuentaActual);
					break;

				case 2:
					retirar(cuentaActual);
					break;

				case 3:
					depositar(cuentaActual);
					break;

				case 4:
					transferir(cuentaActual, cuentas, TOTAL_CUENTAS);
					break;

				case 5:
					cout << "Cerrando sesion..." << endl;
					cuentaActual = nullptr; // Desconectar usuario
					break;

				case 6:
					cout << "Apagando sistema. Hasta luego." << endl;
					return 0; // Salir del programa
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