#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Paciente {
    string nombre;
    int edad;
    string motivo;
    bool urgente;
    Paciente* siguiente;
};

struct ListaPacientes {
    Paciente* inicio;
    Paciente* fin;

    ListaPacientes() {
        inicio = nullptr;
        fin = nullptr;
    }
};


int leerEntero(const string& mensaje) {
    int valor;

    while (true) {
        cout << mensaje;

        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }

        cout << "Entrada no valida. Ingresa un numero entero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


string leerTexto(const string& mensaje) {
    string texto;

    do {
        cout << mensaje;
        getline(cin, texto);

        if (texto.empty()) {
            cout << "El dato no puede estar vacio.\n";
        }
    } while (texto.empty());

    return texto;
}


void insertarPaciente(
    ListaPacientes& lista,
    const string& nombre,
    int edad,
    const string& motivo,
    bool urgente
) {
    Paciente* nuevo = new Paciente;

    nuevo->nombre = nombre;
    nuevo->edad = edad;
    nuevo->motivo = motivo;
    nuevo->urgente = urgente;
    nuevo->siguiente = nullptr;

    if (urgente) {
        nuevo->siguiente = lista.inicio;
        lista.inicio = nuevo;

        if (lista.fin == nullptr) {
            lista.fin = nuevo;
        }
    } else {
        if (lista.fin == nullptr) {
            lista.inicio = nuevo;
            lista.fin = nuevo;
        } else {
            lista.fin->siguiente = nuevo;
            lista.fin = nuevo;
        }
    }

    cout << "Paciente registrado correctamente.\n";
}


void mostrarPaciente(const Paciente* paciente) {
    cout << "\nNombre: " << paciente->nombre << '\n';
    cout << "Edad: " << paciente->edad << '\n';
    cout << "Motivo: " << paciente->motivo << '\n';
    cout << "Prioridad: "
         << (paciente->urgente ? "Urgente" : "Normal")
         << '\n';
}


void mostrarPacientes(const ListaPacientes& lista) {
    if (lista.inicio == nullptr) {
        cout << "\nNo hay pacientes pendientes.\n";
        return;
    }

    cout << "\n=== PACIENTES PENDIENTES ===\n";

    const Paciente* actual = lista.inicio;
    int posicion = 1;

    while (actual != nullptr) {
        cout << "\nPaciente " << posicion << '\n';
        mostrarPaciente(actual);

        actual = actual->siguiente;
        posicion++;
    }
}


void atenderPrimerPaciente(ListaPacientes& lista) {
    if (lista.inicio == nullptr) {
        cout << "\nNo hay pacientes pendientes para atender.\n";
        return;
    }

    Paciente* atendido = lista.inicio;

    cout << "\nSe atendera al siguiente paciente:";
    mostrarPaciente(atendido);

    lista.inicio = lista.inicio->siguiente;

    if (lista.inicio == nullptr) {
        lista.fin = nullptr;
    }

    delete atendido;
}


Paciente* buscarPaciente(const ListaPacientes& lista, const string& nombre) {
    Paciente* actual = lista.inicio;

    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            return actual;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}


void consultarPaciente(const ListaPacientes& lista) {
    string nombre = leerTexto("\nNombre del paciente que deseas buscar: ");
    Paciente* encontrado = buscarPaciente(lista, nombre);

    if (encontrado == nullptr) {
        cout << "No se encontro un paciente con ese nombre.\n";
        return;
    }

    cout << "\nPaciente encontrado:";
    mostrarPaciente(encontrado);
}


void eliminarPacientePorNombre(ListaPacientes& lista) {
    string nombre = leerTexto("\nNombre del paciente que deseas eliminar: ");

    Paciente* actual = lista.inicio;
    Paciente* anterior = nullptr;

    while (actual != nullptr && actual->nombre != nombre) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "No se encontro un paciente con ese nombre.\n";
        return;
    }

    if (anterior == nullptr) {
        // El paciente eliminado era el primero.
        lista.inicio = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    if (actual == lista.fin) {
        lista.fin = anterior;
    }

    cout << "Paciente eliminado de la lista de espera: "
         << actual->nombre << '\n';

    delete actual;
}


void liberarLista(ListaPacientes& lista) {
    Paciente* actual = lista.inicio;

    while (actual != nullptr) {
        Paciente* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    lista.inicio = nullptr;
    lista.fin = nullptr;
}


int main() {
    ListaPacientes lista;
    int opcion;

    do {
        cout << "\n===== LISTA DE ESPERA DE LA CLINICA =====\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Mostrar pacientes pendientes\n";
        cout << "3. Atender al primer paciente\n";
        cout << "4. Buscar paciente por nombre\n";
        cout << "5. Eliminar paciente por nombre\n";
        cout << "6. Salir\n";

        opcion = leerEntero("Selecciona una opcion: ");

        switch (opcion) {
            case 1: {
                string nombre = leerTexto("Nombre: ");

                int edad;
                do {
                    edad = leerEntero("Edad: ");

                    if (edad <= 0) {
                        cout << "La edad debe ser mayor que cero.\n";
                    }
                } while (edad <= 0);

                string motivo = leerTexto("Motivo de consulta: ");

                int opcionPrioridad;
                do {
                    cout << "Prioridad:\n";
                    cout << "1. Normal\n";
                    cout << "2. Urgente\n";
                    opcionPrioridad = leerEntero("Selecciona la prioridad: ");

                    if (opcionPrioridad != 1 && opcionPrioridad != 2) {
                        cout << "Selecciona 1 o 2.\n";
                    }
                } while (opcionPrioridad != 1 && opcionPrioridad != 2);

                bool urgente = (opcionPrioridad == 2);

                insertarPaciente(
                    lista,
                    nombre,
                    edad,
                    motivo,
                    urgente
                );
                break;
            }

            case 2:
                mostrarPacientes(lista);
                break;

            case 3:
                atenderPrimerPaciente(lista);
                break;

            case 4:
                consultarPaciente(lista);
                break;

            case 5:
                eliminarPacientePorNombre(lista);
                break;

            case 6:
                cout << "Programa finalizado.\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 6);

    liberarLista(lista);
    return 0;
}