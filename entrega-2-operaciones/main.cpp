#include <iostream>
#include <string>

using namespace std;

const int PAISES = 4;
const int MESES = 3;

int main() {

    string paises[PAISES];
    float temperaturas[PAISES][MESES];
    float promedios[PAISES] = {0};

    int indiceMayor = 0;

    // 1. Ingresar los paises y las temperaturas
    cout << "=== REGISTRO DE TEMPERATURAS ===" << endl;

    for (int i = 0; i < PAISES; i++) {

        cout << "\nIngrese el nombre del pais " << i + 1 << ": ";
        cin >> paises[i];

        for (int j = 0; j < MESES; j++) {

            cout << "Ingrese la temperatura del mes "
                 << j + 1
                 << " para "
                 << paises[i]
                 << ": ";

            cin >> temperaturas[i][j];
        }
    }

    // 2. Mostrar los paises y las temperaturas ingresadas
    cout << "\n=== TEMPERATURAS REGISTRADAS ===" << endl;

    for (int i = 0; i < PAISES; i++) {

        cout << "\nPais: " << paises[i] << endl;

        for (int j = 0; j < MESES; j++) {

            cout << "Mes "
                 << j + 1
                 << ": "
                 << temperaturas[i][j]
                 << " grados"
                 << endl;
        }
    }

    // 3. Calcular el promedio trimestral de cada pais
    for (int i = 0; i < PAISES; i++) {

        float suma = 0;

        for (int j = 0; j < MESES; j++) {

            suma = suma + temperaturas[i][j];
        }

        promedios[i] = suma / MESES;
    }

    // 4. Mostrar los promedios trimestrales
    cout << "\n=== PROMEDIOS TRIMESTRALES ===" << endl;

    for (int i = 0; i < PAISES; i++) {

        cout << paises[i]
             << ": "
             << promedios[i]
             << " grados"
             << endl;
    }

    // 5. Buscar el pais con mayor temperatura promedio
    for (int i = 1; i < PAISES; i++) {

        if (promedios[i] > promedios[indiceMayor]) {

            indiceMayor = i;
        }
    }

    cout << "\nEl pais con la mayor temperatura promedio es: "
         << paises[indiceMayor]
         << " con "
         << promedios[indiceMayor]
         << " grados."
         << endl;

    return 0;
}
