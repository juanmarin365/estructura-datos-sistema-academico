#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Asignatura {
    string nombre;
    Asignatura* siguiente;
};

struct Inscripcion {
    Asignatura* asignatura;
    float nota;
    Inscripcion* siguiente;
};

struct Estudiante {
    string nombre;
    string codigo;
    Inscripcion* inscripciones;
    Estudiante* siguiente;
};

struct ListaAsignaturas {
    Asignatura* inicio;
    Asignatura* fin;

    ListaAsignaturas() {
        inicio = nullptr;
        fin = nullptr;
    }
};

struct ListaEstudiantes {
    Estudiante* inicio;
    Estudiante* fin;

    ListaEstudiantes() {
        inicio = nullptr;
        fin = nullptr;
    }
};

struct SolicitudCola {
    Estudiante* estudiante;
    string motivo;
    SolicitudCola* siguiente;
};

struct ColaSolicitudes {
    SolicitudCola* frente;
    SolicitudCola* final;

    ColaSolicitudes() {
        frente = nullptr;
        final = nullptr;
    }
};

struct SolicitudPila {
    Estudiante* estudiante;
    string motivo;
    SolicitudPila* siguiente;
};

struct PilaSolicitudes {
    SolicitudPila* cima;

    PilaSolicitudes() {
        cima = nullptr;
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

float leerNota(const string& mensaje) {
    float nota;

    while (true) {
        cout << mensaje;

        if (cin >> nota) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nota;
        }

        cout << "Entrada no valida. Ingresa una nota numerica.\n";
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
            cout << "Este campo no puede quedar vacio.\n";
        }
    } while (texto.empty());

    return texto;
}

// ==================== ASIGNATURAS ====================
Asignatura* buscarAsignatura(
    const ListaAsignaturas& lista,
    const string& nombre
) {
    Asignatura* actual = lista.inicio;

    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            return actual;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}


void agregarAsignatura(
    ListaAsignaturas& lista,
    const string& nombre
) {
    Asignatura* nueva = new Asignatura;
    nueva->nombre = nombre;
    nueva->siguiente = nullptr;

    if (lista.fin == nullptr) {
        lista.inicio = nueva;
        lista.fin = nueva;
    } else {
        lista.fin->siguiente = nueva;
        lista.fin = nueva;
    }
}

Asignatura* obtenerAsignaturaPorNumero(
    const ListaAsignaturas& lista,
    int numero
) {
    Asignatura* actual = lista.inicio;
    int posicion = 1;

    while (actual != nullptr) {
        if (posicion == numero) {
            return actual;
        }

        actual = actual->siguiente;
        posicion++;
    }

    return nullptr;
}

void registrarAsignaturasIniciales(ListaAsignaturas& lista) {
    cout << "=== REGISTRO DE ASIGNATURAS ===\n";

    for (int i = 1; i <= 3; i++) {
        string nombre;

        while (true) {
            nombre = leerTexto(
                "Nombre de la asignatura " + to_string(i) + ": "
            );

            if (buscarAsignatura(lista, nombre) == nullptr) {
                break;
            }

            cout << "Esa asignatura ya fue registrada. "
                 << "Ingresa un nombre diferente.\n";
        }

        agregarAsignatura(lista, nombre);
    }
}


void mostrarAsignaturas(const ListaAsignaturas& lista) {
    Asignatura* actual = lista.inicio;
    int posicion = 1;

    cout << "\n=== ASIGNATURAS DISPONIBLES ===\n";

    while (actual != nullptr) {
        cout << posicion << ". " << actual->nombre << '\n';
        actual = actual->siguiente;
        posicion++;
    }
}

// ==================== ESTUDIANTES ====================
Estudiante* buscarEstudiante(
    const ListaEstudiantes& lista,
    const string& codigo
) {
    Estudiante* actual = lista.inicio;

    while (actual != nullptr) {
        if (actual->codigo == codigo) {
            return actual;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void registrarEstudiante(ListaEstudiantes& lista) {
    string codigo = leerTexto("Codigo del estudiante: ");

    if (buscarEstudiante(lista, codigo) != nullptr) {
        cout << "Ya existe un estudiante con ese codigo.\n";
        return;
    }

    string nombre = leerTexto("Nombre del estudiante: ");

    Estudiante* nuevo = new Estudiante;
    nuevo->nombre = nombre;
    nuevo->codigo = codigo;
    nuevo->inscripciones = nullptr;
    nuevo->siguiente = nullptr;

    if (lista.fin == nullptr) {
        lista.inicio = nuevo;
        lista.fin = nuevo;
    } else {
        lista.fin->siguiente = nuevo;
        lista.fin = nuevo;
    }

    cout << "Estudiante registrado correctamente.\n";
}

bool yaEstaInscrito(
    const Estudiante* estudiante,
    const Asignatura* asignatura
) {
    Inscripcion* actual = estudiante->inscripciones;

    while (actual != nullptr) {
        if (actual->asignatura == asignatura) {
            return true;
        }

        actual = actual->siguiente;
    }

    return false;
}

void inscribirAsignatura(
    ListaEstudiantes& estudiantes,
    const ListaAsignaturas& asignaturas
) {
    if (estudiantes.inicio == nullptr) {
        cout << "Primero debes registrar un estudiante.\n";
        return;
    }

    string codigo = leerTexto("Codigo del estudiante: ");
    Estudiante* estudiante = buscarEstudiante(estudiantes, codigo);

    if (estudiante == nullptr) {
        cout << "No se encontro un estudiante con ese codigo.\n";
        return;
    }

    mostrarAsignaturas(asignaturas);

    int numero = leerEntero("Numero de la asignatura que desea inscribir: ");
    Asignatura* asignatura =
        obtenerAsignaturaPorNumero(asignaturas, numero);

    if (asignatura == nullptr) {
        cout << "El numero de asignatura no es valido.\n";
        return;
    }

    if (yaEstaInscrito(estudiante, asignatura)) {
        cout << "El estudiante ya esta inscrito en esa asignatura.\n";
        return;
    }

    float nota = leerNota("Nota del estudiante en la asignatura: ");

    Inscripcion* nueva = new Inscripcion;
    nueva->asignatura = asignatura;
    nueva->nota = nota;
    nueva->siguiente = nullptr;

    if (estudiante->inscripciones == nullptr) {
        estudiante->inscripciones = nueva;
    } else {
        Inscripcion* ultima = estudiante->inscripciones;

        while (ultima->siguiente != nullptr) {
            ultima = ultima->siguiente;
        }

        ultima->siguiente = nueva;
    }

    cout << estudiante->nombre << " quedo inscrito en "
         << asignatura->nombre << ".\n";
}

void mostrarInscripciones(const Estudiante* estudiante) {
    Inscripcion* actual = estudiante->inscripciones;

    if (actual == nullptr) {
        cout << "  No tiene asignaturas inscritas.\n";
        return;
    }

    cout << "  Asignaturas y notas:\n";

    while (actual != nullptr) {
        cout << "  - " << actual->asignatura->nombre
             << ": " << actual->nota << '\n';

        actual = actual->siguiente;
    }
}

void mostrarUnEstudiante(const Estudiante* estudiante) {
    cout << "\nNombre: " << estudiante->nombre << '\n';
    cout << "Codigo: " << estudiante->codigo << '\n';
    mostrarInscripciones(estudiante);
}

void mostrarTodosLosEstudiantes(const ListaEstudiantes& lista) {
    if (lista.inicio == nullptr) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "\n=== ESTUDIANTES E INSCRIPCIONES ===\n";

    Estudiante* actual = lista.inicio;

    while (actual != nullptr) {
        mostrarUnEstudiante(actual);
        actual = actual->siguiente;
    }
}

void consultarEstudiante(const ListaEstudiantes& lista) {
    string codigo = leerTexto("Codigo del estudiante que deseas consultar: ");
    Estudiante* estudiante = buscarEstudiante(lista, codigo);

    if (estudiante == nullptr) {
        cout << "No se encontro un estudiante con ese codigo.\n";
        return;
    }

    cout << "\n=== ESTUDIANTE ENCONTRADO ===\n";
    mostrarUnEstudiante(estudiante);
}

bool calcularPromedio(
    const Estudiante* estudiante,
    float& promedio
) {
    Inscripcion* actual = estudiante->inscripciones;
    float suma = 0;
    int cantidad = 0;

    while (actual != nullptr) {
        suma += actual->nota;
        cantidad++;
        actual = actual->siguiente;
    }

    if (cantidad == 0) {
        return false;
    }

    promedio = suma / cantidad;
    return true;
}

void mostrarPromedios(const ListaEstudiantes& lista) {
    if (lista.inicio == nullptr) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "\n=== PROMEDIOS POR ESTUDIANTE ===\n";

    Estudiante* actual = lista.inicio;
    bool hayPromedios = false;

    while (actual != nullptr) {
        float promedio;

        cout << actual->nombre << " (" << actual->codigo << "): ";

        if (calcularPromedio(actual, promedio)) {
            cout << promedio << '\n';
            hayPromedios = true;
        } else {
            cout << "sin notas registradas\n";
        }

        actual = actual->siguiente;
    }

    if (!hayPromedios) {
        cout << "Todavia no hay notas para calcular promedios.\n";
    }
}

void mostrarMayorPromedio(const ListaEstudiantes& lista) {
    Estudiante* actual = lista.inicio;
    Estudiante* mejorEstudiante = nullptr;
    float mayorPromedio = 0;

    while (actual != nullptr) {
        float promedio;

        if (calcularPromedio(actual, promedio)) {
            if (mejorEstudiante == nullptr || promedio > mayorPromedio) {
                mejorEstudiante = actual;
                mayorPromedio = promedio;
            }
        }

        actual = actual->siguiente;
    }

    if (mejorEstudiante == nullptr) {
        cout << "No hay notas registradas para comparar.\n";
        return;
    }

    cout << "Estudiante con mayor promedio: "
         << mejorEstudiante->nombre << '\n';
    cout << "Promedio: " << mayorPromedio << '\n';
}

void mostrarMenorPromedio(const ListaEstudiantes& lista) {
    Estudiante* actual = lista.inicio;
    Estudiante* menorEstudiante = nullptr;
    float menorPromedio = 0;

    while (actual != nullptr) {
        float promedio;

        if (calcularPromedio(actual, promedio)) {
            if (menorEstudiante == nullptr || promedio < menorPromedio) {
                menorEstudiante = actual;
                menorPromedio = promedio;
            }
        }

        actual = actual->siguiente;
    }

    if (menorEstudiante == nullptr) {
        cout << "No hay notas registradas para comparar.\n";
        return;
    }

    cout << "Estudiante con menor promedio: "
         << menorEstudiante->nombre << '\n';
    cout << "Promedio: " << menorPromedio << '\n';
}

// ==================== SOLICITUDES: COLA FIFO ====================
void encolarSolicitud(
    ColaSolicitudes& cola,
    Estudiante* estudiante,
    const string& motivo
) {
    SolicitudCola* nueva = new SolicitudCola;
    nueva->estudiante = estudiante;
    nueva->motivo = motivo;
    nueva->siguiente = nullptr;

    if (cola.final == nullptr) {
        cola.frente = nueva;
        cola.final = nueva;
    } else {
        cola.final->siguiente = nueva;
        cola.final = nueva;
    }
}

void atenderSiguienteSolicitud(ColaSolicitudes& cola) {
    if (cola.frente == nullptr) {
        cout << "No hay solicitudes pendientes para atender.\n";
        return;
    }

    SolicitudCola* atendida = cola.frente;

    cout << "\nSe atendera la solicitud de:\n";
    cout << "Estudiante: " << atendida->estudiante->nombre << '\n';
    cout << "Codigo: " << atendida->estudiante->codigo << '\n';
    cout << "Motivo: " << atendida->motivo << '\n';

    cola.frente = cola.frente->siguiente;

    if (cola.frente == nullptr) {
        cola.final = nullptr;
    }

    delete atendida;
}

void mostrarSolicitudesPendientes(const ColaSolicitudes& cola) {
    if (cola.frente == nullptr) {
        cout << "No hay solicitudes pendientes.\n";
        return;
    }

    cout << "\n=== SOLICITUDES PENDIENTES (ORDEN DE LLEGADA) ===\n";

    SolicitudCola* actual = cola.frente;
    int posicion = 1;

    while (actual != nullptr) {
        cout << "\nSolicitud " << posicion << '\n';
        cout << "Estudiante: " << actual->estudiante->nombre << '\n';
        cout << "Codigo: " << actual->estudiante->codigo << '\n';
        cout << "Motivo: " << actual->motivo << '\n';

        actual = actual->siguiente;
        posicion++;
    }
}

// ==================== HISTORIAL: PILA LIFO ====================
void apilarHistorial(
    PilaSolicitudes& pila,
    Estudiante* estudiante,
    const string& motivo
) {
    SolicitudPila* nueva = new SolicitudPila;
    nueva->estudiante = estudiante;
    nueva->motivo = motivo;
    nueva->siguiente = pila.cima;

    pila.cima = nueva;
}

void mostrarHistorial(const PilaSolicitudes& pila) {
    if (pila.cima == nullptr) {
        cout << "Todavia no hay solicitudes en el historial.\n";
        return;
    }

    cout << "\n=== HISTORIAL (ULTIMA SOLICITUD PRIMERO) ===\n";

    SolicitudPila* actual = pila.cima;
    int posicion = 1;

    while (actual != nullptr) {
        cout << "\nRegistro " << posicion << '\n';
        cout << "Estudiante: " << actual->estudiante->nombre << '\n';
        cout << "Codigo: " << actual->estudiante->codigo << '\n';
        cout << "Motivo: " << actual->motivo << '\n';

        actual = actual->siguiente;
        posicion++;
    }
}

void solicitarAsesoria(
    ListaEstudiantes& estudiantes,
    ColaSolicitudes& cola,
    PilaSolicitudes& historial
) {
    if (estudiantes.inicio == nullptr) {
        cout << "Primero debes registrar un estudiante.\n";
        return;
    }

    string codigo = leerTexto("Codigo del estudiante que solicita asesoria: ");
    Estudiante* estudiante = buscarEstudiante(estudiantes, codigo);

    if (estudiante == nullptr) {
        cout << "No se encontro un estudiante con ese codigo.\n";
        return;
    }

    string motivo = leerTexto("Motivo de la solicitud: ");

    // Se guarda una copia de la solicitud en la cola y otra en el historial.
    encolarSolicitud(cola, estudiante, motivo);
    apilarHistorial(historial, estudiante, motivo);

    cout << "Solicitud registrada. Se atendera por orden de llegada.\n";
}

// ==================== LIBERACION DE MEMORIA ====================
void liberarCola(ColaSolicitudes& cola) {
    while (cola.frente != nullptr) {
        SolicitudCola* eliminar = cola.frente;
        cola.frente = cola.frente->siguiente;
        delete eliminar;
    }

    cola.final = nullptr;
}

void liberarPila(PilaSolicitudes& pila) {
    while (pila.cima != nullptr) {
        SolicitudPila* eliminar = pila.cima;
        pila.cima = pila.cima->siguiente;
        delete eliminar;
    }
}

void liberarEstudiantes(ListaEstudiantes& lista) {
    Estudiante* estudianteActual = lista.inicio;

    while (estudianteActual != nullptr) {
        Inscripcion* inscripcionActual = estudianteActual->inscripciones;

        while (inscripcionActual != nullptr) {
            Inscripcion* siguienteInscripcion =
                inscripcionActual->siguiente;

            delete inscripcionActual;
            inscripcionActual = siguienteInscripcion;
        }

        Estudiante* siguienteEstudiante = estudianteActual->siguiente;
        delete estudianteActual;
        estudianteActual = siguienteEstudiante;
    }

    lista.inicio = nullptr;
    lista.fin = nullptr;
}

void liberarAsignaturas(ListaAsignaturas& lista) {
    Asignatura* actual = lista.inicio;

    while (actual != nullptr) {
        Asignatura* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    lista.inicio = nullptr;
    lista.fin = nullptr;
}

int main() {
    ListaAsignaturas asignaturas;
    ListaEstudiantes estudiantes;
    ColaSolicitudes colaSolicitudes;
    PilaSolicitudes historialSolicitudes;

    registrarAsignaturasIniciales(asignaturas);

    int opcion;

    do {
        cout << "\n===== SISTEMA ACADEMICO: ENTREGA 4 =====\n";
        cout << "1. Registrar estudiante\n";
        cout << "2. Inscribir estudiante en una asignatura\n";
        cout << "3. Mostrar estudiantes e inscripciones\n";
        cout << "4. Buscar estudiante por codigo\n";
        cout << "5. Mostrar promedios\n";
        cout << "6. Mostrar estudiante con mayor promedio\n";
        cout << "7. Mostrar estudiante con menor promedio\n";
        cout << "8. Solicitar asesoria academica\n";
        cout << "9. Atender siguiente solicitud (cola)\n";
        cout << "10. Mostrar solicitudes pendientes\n";
        cout << "11. Mostrar historial de solicitudes (pila)\n";
        cout << "12. Salir\n";

        opcion = leerEntero("Selecciona una opcion: ");

        switch (opcion) {
            case 1:
                registrarEstudiante(estudiantes);
                break;

            case 2:
                inscribirAsignatura(estudiantes, asignaturas);
                break;

            case 3:
                mostrarTodosLosEstudiantes(estudiantes);
                break;

            case 4:
                consultarEstudiante(estudiantes);
                break;

            case 5:
                mostrarPromedios(estudiantes);
                break;

            case 6:
                mostrarMayorPromedio(estudiantes);
                break;

            case 7:
                mostrarMenorPromedio(estudiantes);
                break;

            case 8:
                solicitarAsesoria(
                    estudiantes,
                    colaSolicitudes,
                    historialSolicitudes
                );
                break;

            case 9:
                atenderSiguienteSolicitud(colaSolicitudes);
                break;

            case 10:
                mostrarSolicitudesPendientes(colaSolicitudes);
                break;

            case 11:
                mostrarHistorial(historialSolicitudes);
                break;

            case 12:
                cout << "Programa finalizado.\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 12);

    liberarCola(colaSolicitudes);
    liberarPila(historialSolicitudes);

    liberarEstudiantes(estudiantes);
    liberarAsignaturas(asignaturas);

    return 0;
}