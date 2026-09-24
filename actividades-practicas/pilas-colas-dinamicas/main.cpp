#include <iostream>
#include <limits>

using namespace std;

class PilaFloat {
private:
    struct Nodo {
        float valor;
        Nodo* siguiente;

        Nodo(float valor, Nodo* siguiente) {
            this->valor = valor;
            this->siguiente = siguiente;
        }
    };

    Nodo* cima;

public:
    PilaFloat() {
        cima = nullptr;
    }

    ~PilaFloat() {
        float valor;
        while (pop(valor)) {
            // pop elimina cada nodo.
        }
    }

    void push(float valor) {
        cima = new Nodo(valor, cima);
    }

    bool pop(float& valor) {
        if (cima == nullptr) {
            return false;
        }

        Nodo* nodoEliminar = cima;
        valor = cima->valor;
        cima = cima->siguiente;

        delete nodoEliminar;
        return true;
    }

    bool top(float& valor) const {
        if (cima == nullptr) {
            return false;
        }

        valor = cima->valor;
        return true;
    }

    bool estaVacia() const {
        return cima == nullptr;
    }

    void mostrar() const {
        if (estaVacia()) {
            cout << "\nLa pila esta vacia.\n";
            return;
        }

        cout << "\nPila (desde la cima):\n";
        Nodo* actual = cima;

        while (actual != nullptr) {
            cout << actual->valor << '\n';
            actual = actual->siguiente;
        }
    }
};


class ColaFloat {
private:
    struct Nodo {
        float valor;
        Nodo* siguiente;

        Nodo(float valor) {
            this->valor = valor;
            siguiente = nullptr;
        }
    };

    Nodo* primero;
    Nodo* ultimo;

public:
    ColaFloat() {
        primero = nullptr;
        ultimo = nullptr;
    }

    ~ColaFloat() {
        float valor;
        while (desencolar(valor)) {
            // desencolar elimina cada nodo.
        }
    }

    void encolar(float valor) {
        Nodo* nuevo = new Nodo(valor);

        if (ultimo == nullptr) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
    }

    bool desencolar(float& valor) {
        if (primero == nullptr) {
            return false;
        }

        Nodo* nodoEliminar = primero;
        valor = primero->valor;
        primero = primero->siguiente;

        if (primero == nullptr) {
            ultimo = nullptr;
        }

        delete nodoEliminar;
        return true;
    }

    bool frente(float& valor) const {
        if (primero == nullptr) {
            return false;
        }

        valor = primero->valor;
        return true;
    }

    bool estaVacia() const {
        return primero == nullptr;
    }

    void mostrar() const {
        if (estaVacia()) {
            cout << "\nLa cola esta vacia.\n";
            return;
        }

        cout << "\nCola (desde el frente):\n";
        Nodo* actual = primero;

        while (actual != nullptr) {
            cout << actual->valor << '\n';
            actual = actual->siguiente;
        }
    }
};


int leerOpcion() {
    int opcion;

    while (!(cin >> opcion)) {
        cout << "Entrada no valida. Ingresa un numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return opcion;
}


float leerFloat() {
    float valor;

    while (!(cin >> valor)) {
        cout << "Entrada no valida. Ingresa un numero decimal: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}


void menuPila(PilaFloat& pila) {
    int opcion;
    float valor;

    do {
        cout << "\n===== MENU DE PILA =====\n";
        cout << "1. Push (agregar valor)\n";
        cout << "2. Pop (retirar valor)\n";
        cout << "3. Top (consultar la cima)\n";
        cout << "4. Mostrar pila\n";
        cout << "5. Volver al menu principal\n";
        cout << "Selecciona una opcion: ";

        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                cout << "Ingresa el valor float: ";
                valor = leerFloat();
                pila.push(valor);
                cout << "Valor agregado a la pila.\n";
                break;

            case 2:
                if (pila.pop(valor)) {
                    cout << "Valor retirado: " << valor << '\n';
                } else {
                    cout << "No se puede retirar: la pila esta vacia.\n";
                }
                break;

            case 3:
                if (pila.top(valor)) {
                    cout << "Valor en la cima: " << valor << '\n';
                } else {
                    cout << "La pila esta vacia.\n";
                }
                break;

            case 4:
                pila.mostrar();
                break;

            case 5:
                cout << "Volviendo al menu principal.\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
}


void menuCola(ColaFloat& cola) {
    int opcion;
    float valor;

    do {
        cout << "\n===== MENU DE COLA =====\n";
        cout << "1. Encolar (agregar valor)\n";
        cout << "2. Desencolar (retirar valor del frente)\n";
        cout << "3. Consultar el frente\n";
        cout << "4. Mostrar cola\n";
        cout << "5. Volver al menu principal\n";
        cout << "Selecciona una opcion: ";

        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                cout << "Ingresa el valor float: ";
                valor = leerFloat();
                cola.encolar(valor);
                cout << "Valor agregado a la cola.\n";
                break;

            case 2:
                if (cola.desencolar(valor)) {
                    cout << "Valor retirado del frente: " << valor << '\n';
                } else {
                    cout << "No se puede desencolar: la cola esta vacia.\n";
                }
                break;

            case 3:
                if (cola.frente(valor)) {
                    cout << "Valor al frente de la cola: " << valor << '\n';
                } else {
                    cout << "La cola esta vacia.\n";
                }
                break;

            case 4:
                cola.mostrar();
                break;

            case 5:
                cout << "Volviendo al menu principal.\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);
}


int main() {
    PilaFloat pila;
    ColaFloat cola;
    int opcion;

    do {
        cout << "\n===== PILAS Y COLAS DE TIPO FLOAT =====\n";
        cout << "1. Probar pila\n";
        cout << "2. Probar cola\n";
        cout << "3. Salir\n";
        cout << "Selecciona una opcion: ";

        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                menuPila(pila);
                break;

            case 2:
                menuCola(cola);
                break;

            case 3:
                cout << "Programa finalizado.\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 3);

    return 0;
}