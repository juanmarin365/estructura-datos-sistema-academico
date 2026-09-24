#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_ESTUDIANTES = 10;
const int NUM_ASIGNATURAS = 3;

void limpiarEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int buscarEstudiante(
    string codigos[],
    int cantidadEstudiantes,
    string codigo
) {

    for (int i = 0; i < cantidadEstudiantes; i++) {

        if (codigos[i] == codigo) {
            return i;
        }
    }

    return -1;
}

void registrarEstudiante(
    string nombres[],
    string codigos[],
    float notas[][NUM_ASIGNATURAS],
    string asignaturas[],
    int& cantidadEstudiantes
) {

    if (cantidadEstudiantes >= MAX_ESTUDIANTES) {

        cout << "\nNo hay espacio para registrar mas estudiantes." << endl;
        return;
    }

    int i = cantidadEstudiantes;

    cout << "\nIngrese el nombre del estudiante: ";
    getline(cin, nombres[i]);

    cout << "Ingrese el codigo del estudiante: ";
    getline(cin, codigos[i]);

    for (int j = 0; j < NUM_ASIGNATURAS; j++) {

        cout << "Ingrese la nota de "
             << asignaturas[j]
             << ": ";

        cin >> notas[i][j];
    }

    limpiarEntrada();

    cantidadEstudiantes++;

    cout << "\nEstudiante registrado correctamente." << endl;
}

void mostrarEstudiantes(
    string nombres[],
    string codigos[],
    float notas[][NUM_ASIGNATURAS],
    string asignaturas[],
    int cantidadEstudiantes
) {

    if (cantidadEstudiantes == 0) {

        cout << "\nNo hay estudiantes registrados." << endl;
        return;
    }

    cout << "\n=== ESTUDIANTES REGISTRADOS ===" << endl;

    for (int i = 0; i < cantidadEstudiantes; i++) {

        cout << "\nNombre: " << nombres[i] << endl;
        cout << "Codigo: " << codigos[i] << endl;

        cout << "Notas:" << endl;

        for (int j = 0; j < NUM_ASIGNATURAS; j++) {

            cout << "- "
                 << asignaturas[j]
                 << ": "
                 << notas[i][j]
                 << endl;
        }
    }
}

void consultarEstudiante(
    string nombres[],
    string codigos[],
    float notas[][NUM_ASIGNATURAS],
    string asignaturas[],
    int cantidadEstudiantes
) {

    string codigo;

    cout << "\nIngrese el codigo del estudiante: ";
    getline(cin, codigo);

    int posicion =
        buscarEstudiante(codigos, cantidadEstudiantes, codigo);

    if (posicion == -1) {

        cout << "\nEstudiante no encontrado." << endl;
        return;
    }

    cout << "\n=== ESTUDIANTE ENCONTRADO ===" << endl;

    cout << "Nombre: "
         << nombres[posicion]
         << endl;

    cout << "Codigo: "
         << codigos[posicion]
         << endl;

    for (int j = 0; j < NUM_ASIGNATURAS; j++) {

        cout << asignaturas[j]
             << ": "
             << notas[posicion][j]
             << endl;
    }
}

void actualizarEstudiante(
    string nombres[],
    string codigos[],
    float notas[][NUM_ASIGNATURAS],
    string asignaturas[],
    int cantidadEstudiantes
) {

    string codigo;

    cout << "\nIngrese el codigo del estudiante que desea actualizar: ";
    getline(cin, codigo);

    int posicion =
        buscarEstudiante(codigos, cantidadEstudiantes, codigo);

    if (posicion == -1) {

        cout << "\nEstudiante no encontrado." << endl;
        return;
    }

    cout << "\nIngrese el nuevo nombre: ";
    getline(cin, nombres[posicion]);

    cout << "Ingrese el nuevo codigo: ";
    getline(cin, codigos[posicion]);

    for (int j = 0; j < NUM_ASIGNATURAS; j++) {

        cout << "Ingrese la nueva nota de "
             << asignaturas[j]
             << ": ";

        cin >> notas[posicion][j];
    }

    limpiarEntrada();

    cout << "\nEstudiante actualizado correctamente." << endl;
}

void eliminarEstudiante(
    string nombres[],
    string codigos[],
    float notas[][NUM_ASIGNATURAS],
    int& cantidadEstudiantes
) {

    string codigo;

    cout << "\nIngrese el codigo del estudiante que desea eliminar: ";
    getline(cin, codigo);

    int posicion =
        buscarEstudiante(codigos, cantidadEstudiantes, codigo);

    if (posicion == -1) {

        cout << "\nEstudiante no encontrado." << endl;
        return;
    }

    for (int i = posicion; i < cantidadEstudiantes - 1; i++) {

        nombres[i] = nombres[i + 1];
        codigos[i] = codigos[i + 1];

        for (int j = 0; j < NUM_ASIGNATURAS; j++) {

            notas[i][j] = notas[i + 1][j];
        }
    }

    cantidadEstudiantes--;

    cout << "\nEstudiante eliminado correctamente." << endl;
}

float calcularPromedio(
    float notas[][NUM_ASIGNATURAS],
    int estudiante
) {

    float suma = 0;

    for (int j = 0; j < NUM_ASIGNATURAS; j++) {

        suma += notas[estudiante][j];
    }

    return suma / NUM_ASIGNATURAS;
}

void mostrarPromedios(
    string nombres[],
    float notas[][NUM_ASIGNATURAS],
    int cantidadEstudiantes
) {

    if (cantidadEstudiantes == 0) {

        cout << "\nNo hay estudiantes registrados." << endl;
        return;
    }

    cout << "\n=== PROMEDIOS ===" << endl;

    for (int i = 0; i < cantidadEstudiantes; i++) {

        cout << nombres[i]
             << ": "
             << calcularPromedio(notas, i)
             << endl;
    }
}

void mostrarMayorPromedio(
    string nombres[],
    float notas[][NUM_ASIGNATURAS],
    int cantidadEstudiantes
) {

    if (cantidadEstudiantes == 0) {

        cout << "\nNo hay estudiantes registrados." << endl;
        return;
    }

    int posicionMayor = 0;

    for (int i = 1; i < cantidadEstudiantes; i++) {

        if (
            calcularPromedio(notas, i)
            >
            calcularPromedio(notas, posicionMayor)
        ) {

            posicionMayor = i;
        }
    }

    cout << "\nEstudiante con mayor promedio: "
         << nombres[posicionMayor]
         << endl;

    cout << "Promedio: "
         << calcularPromedio(notas, posicionMayor)
         << endl;
}

void mostrarMenorPromedio(
    string nombres[],
    float notas[][NUM_ASIGNATURAS],
    int cantidadEstudiantes
) {

    if (cantidadEstudiantes == 0) {

        cout << "\nNo hay estudiantes registrados." << endl;
        return;
    }

    int posicionMenor = 0;

    for (int i = 1; i < cantidadEstudiantes; i++) {

        if (
            calcularPromedio(notas, i)
            <
            calcularPromedio(notas, posicionMenor)
        ) {

            posicionMenor = i;
        }
    }

    cout << "\nEstudiante con menor promedio: "
         << nombres[posicionMenor]
         << endl;

    cout << "Promedio: "
         << calcularPromedio(notas, posicionMenor)
         << endl;
}

void ordenarEstudiantes(
    string nombres[],
    string codigos[],
    float notas[][NUM_ASIGNATURAS],
    int cantidadEstudiantes
) {

    for (int i = 0; i < cantidadEstudiantes - 1; i++) {

        for (int j = 0; j < cantidadEstudiantes - i - 1; j++) {

            if (nombres[j] > nombres[j + 1]) {

                // Intercambiar nombres
                string nombreTemporal = nombres[j];

                nombres[j] = nombres[j + 1];
                nombres[j + 1] = nombreTemporal;


                // Intercambiar codigos
                string codigoTemporal = codigos[j];

                codigos[j] = codigos[j + 1];
                codigos[j + 1] = codigoTemporal;


                // Intercambiar notas
                for (int k = 0; k < NUM_ASIGNATURAS; k++) {

                    float notaTemporal = notas[j][k];

                    notas[j][k] = notas[j + 1][k];

                    notas[j + 1][k] = notaTemporal;
                }
            }
        }
    }

    cout << "\nEstudiantes ordenados correctamente." << endl;
}

int main() {

    string nombres[MAX_ESTUDIANTES];
    string codigos[MAX_ESTUDIANTES];

    string asignaturas[NUM_ASIGNATURAS];

    float notas[MAX_ESTUDIANTES][NUM_ASIGNATURAS];

    int cantidadEstudiantes = 0;

    int opcion;


    cout << "=== SISTEMA DE GESTION ACADEMICA ===" << endl;


    // Registrar las asignaturas una sola vez
    cout << "\nIngrese las asignaturas" << endl;

    for (int j = 0; j < NUM_ASIGNATURAS; j++) {

        cout << "Asignatura "
             << j + 1
             << ": ";

        getline(cin, asignaturas[j]);
    }


    do {

        cout << "\n====================================" << endl;
        cout << "   SISTEMA DE GESTION ACADEMICA" << endl;
        cout << "====================================" << endl;

        cout << "1. Registrar estudiante" << endl;
        cout << "2. Mostrar estudiantes" << endl;
        cout << "3. Buscar estudiante" << endl;
        cout << "4. Actualizar estudiante" << endl;
        cout << "5. Eliminar estudiante" << endl;
        cout << "6. Mostrar promedios" << endl;
        cout << "7. Mostrar mayor promedio" << endl;
        cout << "8. Mostrar menor promedio" << endl;
        cout << "9. Ordenar estudiantes por nombre" << endl;
        cout << "10. Salir" << endl;

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        limpiarEntrada();


        switch (opcion) {

            case 1:

                registrarEstudiante(
                    nombres,
                    codigos,
                    notas,
                    asignaturas,
                    cantidadEstudiantes
                );

                break;


            case 2:

                mostrarEstudiantes(
                    nombres,
                    codigos,
                    notas,
                    asignaturas,
                    cantidadEstudiantes
                );

                break;


            case 3:

                consultarEstudiante(
                    nombres,
                    codigos,
                    notas,
                    asignaturas,
                    cantidadEstudiantes
                );

                break;


            case 4:

                actualizarEstudiante(
                    nombres,
                    codigos,
                    notas,
                    asignaturas,
                    cantidadEstudiantes
                );

                break;


            case 5:

                eliminarEstudiante(
                    nombres,
                    codigos,
                    notas,
                    cantidadEstudiantes
                );

                break;


            case 6:

                mostrarPromedios(
                    nombres,
                    notas,
                    cantidadEstudiantes
                );

                break;


            case 7:

                mostrarMayorPromedio(
                    nombres,
                    notas,
                    cantidadEstudiantes
                );

                break;


            case 8:

                mostrarMenorPromedio(
                    nombres,
                    notas,
                    cantidadEstudiantes
                );

                break;


            case 9:

                ordenarEstudiantes(
                    nombres,
                    codigos,
                    notas,
                    cantidadEstudiantes
                );

                break;


            case 10:

                cout << "\nPrograma finalizado." << endl;

                break;


            default:

                cout << "\nOpcion no valida." << endl;
        }


    } while (opcion != 10);


    return 0;
}