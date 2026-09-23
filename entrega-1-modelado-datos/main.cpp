#include <iostream>
#include <string>

using namespace std;

int main() {

    const int NUM_ESTUDIANTES = 3;
    const int NUM_ASIGNATURAS = 3;

    string nombres[NUM_ESTUDIANTES];
    string codigos[NUM_ESTUDIANTES];
    string asignaturas[NUM_ASIGNATURAS];

    float notas[NUM_ESTUDIANTES][NUM_ASIGNATURAS];

    cout << "=== SISTEMA DE GESTION ACADEMICA ===" << endl;

    cout << "\nIngreso de asignaturas" << endl;

    for (int j = 0; j < NUM_ASIGNATURAS; j++) {

        cout << "Ingrese el nombre de la asignatura "
             << j + 1
             << ": ";

        getline(cin, asignaturas[j]);
    }

    cout << "\nIngreso de estudiantes" << endl;

    for (int i = 0; i < NUM_ESTUDIANTES; i++) {

        cout << "\nEstudiante " << i + 1 << endl;

        cout << "Ingrese el nombre: ";
        getline(cin, nombres[i]);

        cout << "Ingrese el codigo: ";
        getline(cin, codigos[i]);
    }

    cout << "\nIngreso de notas" << endl;

    for (int i = 0; i < NUM_ESTUDIANTES; i++) {

        cout << "\nNotas de " << nombres[i] << endl;

        for (int j = 0; j < NUM_ASIGNATURAS; j++) {

            cout << "Ingrese la nota de "
                 << asignaturas[j]
                 << ": ";

            cin >> notas[i][j];
        }
    }

    cout << "\n\n=== INFORMACION REGISTRADA ===" << endl;

    for (int i = 0; i < NUM_ESTUDIANTES; i++) {

        cout << "\nEstudiante: " << nombres[i] << endl;
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

    return 0;
}