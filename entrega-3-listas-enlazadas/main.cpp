#include <iostream>
#include <string>
#include <limits>

using namespace std;

const float NOTA_APROBACION = 3.0;

struct Asignatura {
    string nombre;
    Asignatura *siguiente;
};

struct Inscripcion {
    Asignatura *asignatura;
    float nota;
    Inscripcion *siguiente;
};

struct Estudiante {
    string nombre;
    string codigo;
    Inscripcion *inscripciones;
    Estudiante *siguiente;
};

struct ListaAsignaturas {
    Asignatura *inicio;
    Asignatura *fin;

    ListaAsignaturas() {
        inicio = nullptr;
        fin = nullptr;
    }
};

struct ListaEstudiantes {
    Estudiante *inicio;
    Estudiante *fin;

    ListaEstudiantes() {
        inicio = nullptr;
        fin = nullptr;
    }
};

int leerEntero(const string &mensaje) {
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

float leerNota(const string &mensaje) {
    float nota;

    while (true) {
        cout << mensaje;

        if (cin >> nota) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (nota >= 0 && nota <= 5) {
                return nota;
            }

            cout << "La nota debe estar entre 0 y 5.\n";
        } else {
            cout << "Entrada no valida. Ingresa una nota numerica.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string leerTexto(const string &mensaje) {
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

Asignatura *buscarAsignatura(
    const ListaAsignaturas &lista,
    const string &nombre
) {
    Asignatura *actual = lista.inicio;

    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            return actual;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void agregarAsignatura(
    ListaAsignaturas &lista,
    const string &nombre
) {
    if (buscarAsignatura(lista, nombre) != nullptr) {
        cout << "La asignatura ya existe.\n";
        return;
    }

    Asignatura *nueva = new Asignatura;

    nueva->nombre = nombre;
    nueva->siguiente = nullptr;

    if (lista.fin == nullptr) {
        lista.inicio = nueva;
        lista.fin = nueva;
    } else {
        lista.fin->siguiente = nueva;
        lista.fin = nueva;
    }

    cout << "Asignatura agregada correctamente.\n";
}

void registrarAsignatura(ListaAsignaturas &lista) {
    string nombre = leerTexto("Nombre de la asignatura: ");
    agregarAsignatura(lista, nombre);
}

void mostrarAsignaturas(const ListaAsignaturas &lista) {
    if (lista.inicio == nullptr) {
        cout << "No hay asignaturas registradas.\n";
        return;
    }

    cout << "\n=== ASIGNATURAS DISPONIBLES ===\n";

    Asignatura *actual = lista.inicio;
    int posicion = 1;

    while (actual != nullptr) {
        cout << posicion << ". " << actual->nombre << '\n';

        actual = actual->siguiente;
        posicion++;
    }
}

void consultarAsignatura(const ListaAsignaturas &lista) {
    string nombre = leerTexto(
        "Nombre de la asignatura que deseas buscar: "
    );

    Asignatura *asignatura = buscarAsignatura(lista, nombre);

    if (asignatura == nullptr) {
        cout << "Asignatura no encontrada.\n";
        return;
    }

    cout << "Asignatura encontrada: "
            << asignatura->nombre
            << '\n';
}

void modificarAsignatura(ListaAsignaturas &lista) {
    string nombreActual = leerTexto(
        "Nombre de la asignatura que deseas modificar: "
    );

    Asignatura *asignatura =
            buscarAsignatura(lista, nombreActual);

    if (asignatura == nullptr) {
        cout << "Asignatura no encontrada.\n";
        return;
    }

    string nuevoNombre = leerTexto(
        "Nuevo nombre de la asignatura: "
    );

    if (buscarAsignatura(lista, nuevoNombre) != nullptr) {
        cout << "Ya existe una asignatura con ese nombre.\n";
        return;
    }

    asignatura->nombre = nuevoNombre;

    cout << "Asignatura modificada correctamente.\n";
}

bool asignaturaTieneInscripciones(
    const ListaEstudiantes &estudiantes,
    Asignatura *asignatura
) {
    Estudiante *estudianteActual = estudiantes.inicio;

    while (estudianteActual != nullptr) {
        Inscripcion *inscripcionActual =
                estudianteActual->inscripciones;

        while (inscripcionActual != nullptr) {
            if (inscripcionActual->asignatura == asignatura) {
                return true;
            }

            inscripcionActual = inscripcionActual->siguiente;
        }

        estudianteActual = estudianteActual->siguiente;
    }

    return false;
}

void eliminarInscripcionesDeAsignatura(
    ListaEstudiantes &estudiantes,
    Asignatura *asignatura
) {
    Estudiante *estudianteActual = estudiantes.inicio;

    while (estudianteActual != nullptr) {
        while (
            estudianteActual->inscripciones != nullptr &&
            estudianteActual->inscripciones->asignatura == asignatura
        ) {
            Inscripcion *eliminar =
                    estudianteActual->inscripciones;

            estudianteActual->inscripciones =
                    eliminar->siguiente;

            delete eliminar;
        }

        Inscripcion *actual =
                estudianteActual->inscripciones;

        while (
            actual != nullptr &&
            actual->siguiente != nullptr
        ) {
            if (
                actual->siguiente->asignatura == asignatura
            ) {
                Inscripcion *eliminar = actual->siguiente;

                actual->siguiente = eliminar->siguiente;

                delete eliminar;
            } else {
                actual = actual->siguiente;
            }
        }

        estudianteActual = estudianteActual->siguiente;
    }
}

void eliminarAsignatura(
    ListaAsignaturas &lista,
    ListaEstudiantes &estudiantes
) {
    string nombre = leerTexto(
        "Nombre de la asignatura que deseas eliminar: "
    );

    Asignatura *actual = lista.inicio;
    Asignatura *anterior = nullptr;

    while (
        actual != nullptr &&
        actual->nombre != nombre
    ) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Asignatura no encontrada.\n";
        return;
    }

    eliminarInscripcionesDeAsignatura(
        estudiantes,
        actual
    );

    if (anterior == nullptr) {
        lista.inicio = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    if (lista.fin == actual) {
        lista.fin = anterior;
    }

    delete actual;

    cout << "Asignatura eliminada correctamente.\n";
}

Asignatura *obtenerAsignaturaPorNumero(
    const ListaAsignaturas &lista,
    int numero
) {
    Asignatura *actual = lista.inicio;
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

Estudiante *buscarEstudiante(
    const ListaEstudiantes &lista,
    const string &codigo
) {
    Estudiante *actual = lista.inicio;

    while (actual != nullptr) {
        if (actual->codigo == codigo) {
            return actual;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void registrarEstudiante(ListaEstudiantes &lista) {
    string codigo = leerTexto(
        "Codigo del estudiante: "
    );

    if (
        buscarEstudiante(lista, codigo) != nullptr
    ) {
        cout << "Ya existe un estudiante con ese codigo.\n";
        return;
    }

    string nombre = leerTexto(
        "Nombre del estudiante: "
    );

    Estudiante *nuevo = new Estudiante;

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

void mostrarInscripciones(
    const Estudiante *estudiante
) {
    Inscripcion *actual =
            estudiante->inscripciones;

    if (actual == nullptr) {
        cout << "  No tiene asignaturas inscritas.\n";
        return;
    }

    cout << "  Asignaturas y notas:\n";

    while (actual != nullptr) {
        cout << "  - "
                << actual->asignatura->nombre
                << ": "
                << actual->nota
                << '\n';

        actual = actual->siguiente;
    }
}

void mostrarUnEstudiante(
    const Estudiante *estudiante
) {
    cout << "\nNombre: "
            << estudiante->nombre
            << '\n';

    cout << "Codigo: "
            << estudiante->codigo
            << '\n';

    mostrarInscripciones(estudiante);
}

void mostrarTodosLosEstudiantes(
    const ListaEstudiantes &lista
) {
    if (lista.inicio == nullptr) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    cout << "\n=== ESTUDIANTES E INSCRIPCIONES ===\n";

    Estudiante *actual = lista.inicio;

    while (actual != nullptr) {
        mostrarUnEstudiante(actual);
        actual = actual->siguiente;
    }
}

void consultarEstudiante(
    const ListaEstudiantes &lista
) {
    string codigo = leerTexto(
        "Codigo del estudiante que deseas consultar: "
    );

    Estudiante *estudiante =
            buscarEstudiante(lista, codigo);

    if (estudiante == nullptr) {
        cout << "No se encontro un estudiante con ese codigo.\n";
        return;
    }

    cout << "\n=== ESTUDIANTE ENCONTRADO ===\n";

    mostrarUnEstudiante(estudiante);
}

void modificarEstudiante(
    ListaEstudiantes &lista
) {
    string codigo = leerTexto(
        "Codigo del estudiante que deseas modificar: "
    );

    Estudiante *estudiante =
            buscarEstudiante(lista, codigo);

    if (estudiante == nullptr) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    string nuevoNombre = leerTexto(
        "Nuevo nombre del estudiante: "
    );

    estudiante->nombre = nuevoNombre;

    cout << "Estudiante modificado correctamente.\n";
}

void liberarInscripciones(
    Estudiante *estudiante
) {
    Inscripcion *actual =
            estudiante->inscripciones;

    while (actual != nullptr) {
        Inscripcion *siguiente =
                actual->siguiente;

        delete actual;

        actual = siguiente;
    }

    estudiante->inscripciones = nullptr;
}

void eliminarEstudiante(
    ListaEstudiantes &lista
) {
    string codigo = leerTexto(
        "Codigo del estudiante que deseas eliminar: "
    );

    Estudiante *actual = lista.inicio;
    Estudiante *anterior = nullptr;

    while (
        actual != nullptr &&
        actual->codigo != codigo
    ) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    liberarInscripciones(actual);

    if (anterior == nullptr) {
        lista.inicio = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    if (lista.fin == actual) {
        lista.fin = anterior;
    }

    delete actual;

    cout << "Estudiante eliminado correctamente.\n";
}

bool yaEstaInscrito(
    const Estudiante *estudiante,
    const Asignatura *asignatura
) {
    Inscripcion *actual =
            estudiante->inscripciones;

    while (actual != nullptr) {
        if (actual->asignatura == asignatura) {
            return true;
        }

        actual = actual->siguiente;
    }

    return false;
}

void inscribirAsignatura(
    ListaEstudiantes &estudiantes,
    const ListaAsignaturas &asignaturas
) {
    if (estudiantes.inicio == nullptr) {
        cout << "Primero debes registrar un estudiante.\n";
        return;
    }

    if (asignaturas.inicio == nullptr) {
        cout << "Primero debes registrar una asignatura.\n";
        return;
    }

    string codigo = leerTexto(
        "Codigo del estudiante: "
    );

    Estudiante *estudiante =
            buscarEstudiante(estudiantes, codigo);

    if (estudiante == nullptr) {
        cout << "No se encontro un estudiante con ese codigo.\n";
        return;
    }

    mostrarAsignaturas(asignaturas);

    int numero = leerEntero(
        "Numero de la asignatura que desea inscribir: "
    );

    Asignatura *asignatura =
            obtenerAsignaturaPorNumero(
                asignaturas,
                numero
            );

    if (asignatura == nullptr) {
        cout << "El numero de asignatura no es valido.\n";
        return;
    }

    if (yaEstaInscrito(estudiante, asignatura)) {
        cout << "El estudiante ya esta inscrito en esa asignatura.\n";
        return;
    }

    float nota = leerNota(
        "Nota del estudiante en la asignatura: "
    );

    Inscripcion *nueva = new Inscripcion;

    nueva->asignatura = asignatura;
    nueva->nota = nota;
    nueva->siguiente = nullptr;

    if (estudiante->inscripciones == nullptr) {
        estudiante->inscripciones = nueva;
    } else {
        Inscripcion *ultima =
                estudiante->inscripciones;

        while (ultima->siguiente != nullptr) {
            ultima = ultima->siguiente;
        }

        ultima->siguiente = nueva;
    }

    cout << estudiante->nombre
            << " quedo inscrito en "
            << asignatura->nombre
            << ".\n";
}

Inscripcion *buscarInscripcion(
    Estudiante *estudiante,
    const string &nombreAsignatura
) {
    Inscripcion *actual =
            estudiante->inscripciones;

    while (actual != nullptr) {
        if (
            actual->asignatura->nombre
            == nombreAsignatura
        ) {
            return actual;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

void consultarNota(
    ListaEstudiantes &estudiantes
) {
    string codigo = leerTexto(
        "Codigo del estudiante: "
    );

    Estudiante *estudiante =
            buscarEstudiante(
                estudiantes,
                codigo
            );

    if (estudiante == nullptr) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    string asignatura = leerTexto(
        "Nombre de la asignatura: "
    );

    Inscripcion *inscripcion =
            buscarInscripcion(
                estudiante,
                asignatura
            );

    if (inscripcion == nullptr) {
        cout << "Nota no encontrada.\n";
        return;
    }

    cout << "Estudiante: "
            << estudiante->nombre
            << '\n';

    cout << "Asignatura: "
            << inscripcion->asignatura->nombre
            << '\n';

    cout << "Nota: "
            << inscripcion->nota
            << '\n';
}

void modificarNota(
    ListaEstudiantes &estudiantes
) {
    string codigo = leerTexto(
        "Codigo del estudiante: "
    );

    Estudiante *estudiante =
            buscarEstudiante(
                estudiantes,
                codigo
            );

    if (estudiante == nullptr) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    string asignatura = leerTexto(
        "Nombre de la asignatura: "
    );

    Inscripcion *inscripcion =
            buscarInscripcion(
                estudiante,
                asignatura
            );

    if (inscripcion == nullptr) {
        cout << "Nota no encontrada.\n";
        return;
    }

    float nuevaNota =
            leerNota("Nueva nota: ");

    inscripcion->nota = nuevaNota;

    cout << "Nota modificada correctamente.\n";
}

void eliminarNota(
    ListaEstudiantes &estudiantes
) {
    string codigo = leerTexto(
        "Codigo del estudiante: "
    );

    Estudiante *estudiante =
            buscarEstudiante(
                estudiantes,
                codigo
            );

    if (estudiante == nullptr) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    string asignatura = leerTexto(
        "Nombre de la asignatura: "
    );

    Inscripcion *actual =
            estudiante->inscripciones;

    Inscripcion *anterior = nullptr;

    while (
        actual != nullptr &&
        actual->asignatura->nombre != asignatura
    ) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Nota no encontrada.\n";
        return;
    }

    if (anterior == nullptr) {
        estudiante->inscripciones =
                actual->siguiente;
    } else {
        anterior->siguiente =
                actual->siguiente;
    }

    delete actual;

    cout << "Nota eliminada correctamente.\n";
}

void mostrarAprobados(
    const ListaEstudiantes &estudiantes,
    const ListaAsignaturas &asignaturas
) {
    string nombreAsignatura = leerTexto(
        "Nombre de la asignatura: "
    );

    Asignatura *asignatura =
            buscarAsignatura(
                asignaturas,
                nombreAsignatura
            );

    if (asignatura == nullptr) {
        cout << "Asignatura no encontrada.\n";
        return;
    }

    cout << "\n=== APROBADOS EN "
            << asignatura->nombre
            << " ===\n";

    Estudiante *estudianteActual =
            estudiantes.inicio;

    bool encontrado = false;

    while (estudianteActual != nullptr) {
        Inscripcion *inscripcionActual =
                estudianteActual->inscripciones;

        while (inscripcionActual != nullptr) {
            if (
                inscripcionActual->asignatura
                == asignatura &&
                inscripcionActual->nota
                >= NOTA_APROBACION
            ) {
                cout << estudianteActual->nombre
                        << " - "
                        << inscripcionActual->nota
                        << '\n';

                encontrado = true;
            }

            inscripcionActual =
                    inscripcionActual->siguiente;
        }

        estudianteActual =
                estudianteActual->siguiente;
    }

    if (!encontrado) {
        cout << "No hay estudiantes aprobados.\n";
    }
}

void mostrarReprobados(
    const ListaEstudiantes &estudiantes,
    const ListaAsignaturas &asignaturas
) {
    string nombreAsignatura = leerTexto(
        "Nombre de la asignatura: "
    );

    Asignatura *asignatura =
            buscarAsignatura(
                asignaturas,
                nombreAsignatura
            );

    if (asignatura == nullptr) {
        cout << "Asignatura no encontrada.\n";
        return;
    }

    cout << "\n=== REPROBADOS EN "
            << asignatura->nombre
            << " ===\n";

    Estudiante *estudianteActual =
            estudiantes.inicio;

    bool encontrado = false;

    while (estudianteActual != nullptr) {
        Inscripcion *inscripcionActual =
                estudianteActual->inscripciones;

        while (inscripcionActual != nullptr) {
            if (
                inscripcionActual->asignatura
                == asignatura &&
                inscripcionActual->nota
                < NOTA_APROBACION
            ) {
                cout << estudianteActual->nombre
                        << " - "
                        << inscripcionActual->nota
                        << '\n';

                encontrado = true;
            }

            inscripcionActual =
                    inscripcionActual->siguiente;
        }

        estudianteActual =
                estudianteActual->siguiente;
    }

    if (!encontrado) {
        cout << "No hay estudiantes reprobados.\n";
    }
}

void liberarEstudiantes(
    ListaEstudiantes &lista
) {
    Estudiante *estudianteActual =
            lista.inicio;

    while (estudianteActual != nullptr) {
        liberarInscripciones(
            estudianteActual
        );

        Estudiante *siguiente =
                estudianteActual->siguiente;

        delete estudianteActual;

        estudianteActual = siguiente;
    }

    lista.inicio = nullptr;
    lista.fin = nullptr;
}

void liberarAsignaturas(
    ListaAsignaturas &lista
) {
    Asignatura *actual = lista.inicio;

    while (actual != nullptr) {
        Asignatura *siguiente =
                actual->siguiente;

        delete actual;

        actual = siguiente;
    }

    lista.inicio = nullptr;
    lista.fin = nullptr;
}

int main() {
    ListaAsignaturas asignaturas;
    ListaEstudiantes estudiantes;

    int opcion;

    do {
        cout << "\n====================================\n";
        cout << "   SISTEMA DE GESTION ACADEMICA\n";
        cout << "====================================\n";

        cout << "1. Registrar estudiante\n";
        cout << "2. Mostrar estudiantes\n";
        cout << "3. Buscar estudiante\n";
        cout << "4. Modificar estudiante\n";
        cout << "5. Eliminar estudiante\n";

        cout << "\n6. Agregar asignatura\n";
        cout << "7. Mostrar asignaturas\n";
        cout << "8. Buscar asignatura\n";
        cout << "9. Modificar asignatura\n";
        cout << "10. Eliminar asignatura\n";

        cout << "\n11. Inscribir estudiante y agregar nota\n";
        cout << "12. Buscar nota\n";
        cout << "13. Modificar nota\n";
        cout << "14. Eliminar nota\n";

        cout << "\n15. Mostrar aprobados por asignatura\n";
        cout << "16. Mostrar reprobados por asignatura\n";

        cout << "\n17. Salir\n";

        opcion = leerEntero(
            "Selecciona una opcion: "
        );

        switch (opcion) {
            case 1:
                registrarEstudiante(estudiantes);
                break;

            case 2:
                mostrarTodosLosEstudiantes(
                    estudiantes
                );
                break;

            case 3:
                consultarEstudiante(estudiantes);
                break;

            case 4:
                modificarEstudiante(estudiantes);
                break;

            case 5:
                eliminarEstudiante(estudiantes);
                break;

            case 6:
                registrarAsignatura(asignaturas);
                break;

            case 7:
                mostrarAsignaturas(asignaturas);
                break;

            case 8:
                consultarAsignatura(asignaturas);
                break;

            case 9:
                modificarAsignatura(asignaturas);
                break;

            case 10:
                eliminarAsignatura(
                    asignaturas,
                    estudiantes
                );
                break;

            case 11:
                inscribirAsignatura(
                    estudiantes,
                    asignaturas
                );
                break;

            case 12:
                consultarNota(estudiantes);
                break;

            case 13:
                modificarNota(estudiantes);
                break;

            case 14:
                eliminarNota(estudiantes);
                break;

            case 15:
                mostrarAprobados(
                    estudiantes,
                    asignaturas
                );
                break;

            case 16:
                mostrarReprobados(
                    estudiantes,
                    asignaturas
                );
                break;

            case 17:
                cout << "Programa finalizado.\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 17);

    liberarEstudiantes(estudiantes);
    liberarAsignaturas(asignaturas);

    return 0;
}
