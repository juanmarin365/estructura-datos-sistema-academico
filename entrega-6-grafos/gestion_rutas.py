from collections import deque


class Grafo:
    def __init__(self):
        # Diccionario que almacena las ciudades y sus rutas.
        self.ciudades = {}
        self.adyacencia = {}

    def agregar_ciudad(self, codigo, nombre):
        if codigo in self.ciudades:
            print("La ciudad ya existe.")
            return

        self.ciudades[codigo] = nombre
        self.adyacencia[codigo] = {}
        print("Ciudad agregada correctamente.")

    def eliminar_ciudad(self, codigo):
        if codigo not in self.ciudades:
            print("La ciudad no existe.")
            return

        # Eliminar las rutas que llegan a esta ciudad.
        for origen in self.adyacencia:
            self.adyacencia[origen].pop(codigo, None)

        # Eliminar la ciudad y sus rutas salientes.
        del self.adyacencia[codigo]
        del self.ciudades[codigo]

        print("Ciudad eliminada correctamente.")

    def agregar_arco(self, origen, destino, peso):
        if origen not in self.ciudades or destino not in self.ciudades:
            print("Una de las ciudades no existe.")
            return

        if peso <= 0:
            print("El peso debe ser mayor que cero.")
            return

        if destino in self.adyacencia[origen]:
            print("La ruta ya existe.")
            return

        self.adyacencia[origen][destino] = peso
        print("Ruta agregada correctamente.")

    def eliminar_arco(self, origen, destino):
        if origen in self.adyacencia:
            if destino in self.adyacencia[origen]:
                del self.adyacencia[origen][destino]
                print("Ruta eliminada correctamente.")
                return

        print("La ruta no existe.")

    def mostrar_destinos(self, origen):
        if origen not in self.ciudades:
            print("La ciudad no existe.")
            return

        print(f"\nDestinos directos desde {self.ciudades[origen]}:")

        destinos = self.adyacencia[origen]

        if not destinos:
            print("No tiene rutas de salida.")
            return

        for destino, peso in destinos.items():
            print(f"- {self.ciudades[destino]} | Peso: {peso}")

    def verificar_conexion(self, origen, destino):
        if origen not in self.ciudades or destino not in self.ciudades:
            print("Una de las ciudades no existe.")
            return

        if destino in self.adyacencia[origen]:
            peso = self.adyacencia[origen][destino]
            print(f"Sí existe conexión directa. Peso: {peso}")
        else:
            print("No existe conexión directa.")

    def bfs(self, inicio):
        if inicio not in self.ciudades:
            print("La ciudad no existe.")
            return

        visitados = {inicio}
        cola = deque([inicio])
        recorrido = []

        while cola:
            actual = cola.popleft()
            recorrido.append(self.ciudades[actual])

            for vecino in self.adyacencia[actual]:
                if vecino not in visitados:
                    visitados.add(vecino)
                    cola.append(vecino)

        print("\nRecorrido BFS:")
        print(" -> ".join(recorrido))

    def mostrar_lista_adyacencia(self):
        print("\nLISTA DE ADYACENCIA")

        for origen in sorted(self.ciudades):
            rutas = []

            for destino, peso in self.adyacencia[origen].items():
                rutas.append(
                    f"{self.ciudades[destino]} ({peso})"
                )

            resultado = ", ".join(rutas) if rutas else "Sin rutas"
            print(f"{self.ciudades[origen]} -> {resultado}")

    def mostrar_matriz_adyacencia(self):
        print("\nMATRIZ DE ADYACENCIA")

        codigos = sorted(self.ciudades)

        print(f"{'':>8}", end="")
        for codigo in codigos:
            print(f"{codigo:>8}", end="")
        print()

        for origen in codigos:
            print(f"{origen:>8}", end="")

            for destino in codigos:
                peso = self.adyacencia[origen].get(destino, 0)
                print(f"{peso:>8}", end="")

            print()

        print("\n0 significa que no existe una ruta directa.")

    def mostrar_arcos(self):
        print("\nLISTA DE ARCOS")

        contador = 0

        for origen, destinos in self.adyacencia.items():
            for destino, peso in destinos.items():
                print(
                    f"{self.ciudades[origen]} -> "
                    f"{self.ciudades[destino]} | Peso: {peso}"
                )
                contador += 1

        if contador == 0:
            print("No hay rutas registradas.")

    def mostrar_ciudades(self):
        print("\nCIUDADES REGISTRADAS")

        for codigo in sorted(self.ciudades):
            print(f"{codigo}: {self.ciudades[codigo]}")


def leer_entero(mensaje):
    # Validar que el usuario ingrese un número entero.
    while True:
        try:
            return int(input(mensaje))
        except ValueError:
            print("Ingrese un número entero válido.")


def cargar_datos_iniciales(grafo):
    # Ciudades del ejercicio.
    grafo.agregar_ciudad(0, "Bogotá")
    grafo.agregar_ciudad(1, "Medellín")
    grafo.agregar_ciudad(2, "Cali")
    grafo.agregar_ciudad(3, "Bucaramanga")

    # Rutas dirigidas con sus respectivos pesos.
    grafo.agregar_arco(0, 1, 12)
    grafo.agregar_arco(0, 2, 25)
    grafo.agregar_arco(1, 3, 18)
    grafo.agregar_arco(2, 1, 8)
    grafo.agregar_arco(2, 3, 14)
    grafo.agregar_arco(3, 0, 30)


def menu():
    grafo = Grafo()
    cargar_datos_iniciales(grafo)

    while True:
        print("\n" + "=" * 45)
        print(" SISTEMA DE GESTIÓN DE RUTAS")
        print("=" * 45)
        print("1. Agregar ciudad")
        print("2. Eliminar ciudad")
        print("3. Agregar arco (ruta)")
        print("4. Eliminar arco (ruta)")
        print("5. Mostrar destinos desde una ciudad")
        print("6. Verificar conexión directa")
        print("7. Recorrer grafo con BFS")
        print("8. Mostrar lista de adyacencia")
        print("9. Mostrar matriz de adyacencia")
        print("10. Mostrar lista de arcos")
        print("11. Mostrar ciudades")
        print("0. Salir")
        print("=" * 45)

        opcion = leer_entero("Seleccione una opción: ")

        if opcion == 1:
            codigo = leer_entero("Código de la ciudad: ")
            nombre = input("Nombre de la ciudad: ").strip()

            if nombre:
                grafo.agregar_ciudad(codigo, nombre)
            else:
                print("El nombre no puede estar vacío.")

        elif opcion == 2:
            grafo.mostrar_ciudades()
            codigo = leer_entero("Código a eliminar: ")
            grafo.eliminar_ciudad(codigo)

        elif opcion == 3:
            grafo.mostrar_ciudades()
            origen = leer_entero("Ciudad de origen: ")
            destino = leer_entero("Ciudad de destino: ")
            peso = leer_entero("Peso de la ruta: ")
            grafo.agregar_arco(origen, destino, peso)

        elif opcion == 4:
            grafo.mostrar_ciudades()
            origen = leer_entero("Ciudad de origen: ")
            destino = leer_entero("Ciudad de destino: ")
            grafo.eliminar_arco(origen, destino)

        elif opcion == 5:
            grafo.mostrar_ciudades()
            origen = leer_entero("Código de origen: ")
            grafo.mostrar_destinos(origen)

        elif opcion == 6:
            grafo.mostrar_ciudades()
            origen = leer_entero("Ciudad de origen: ")
            destino = leer_entero("Ciudad de destino: ")
            grafo.verificar_conexion(origen, destino)

        elif opcion == 7:
            grafo.mostrar_ciudades()
            inicio = leer_entero("Ciudad inicial: ")
            grafo.bfs(inicio)

        elif opcion == 8:
            grafo.mostrar_lista_adyacencia()

        elif opcion == 9:
            grafo.mostrar_matriz_adyacencia()

        elif opcion == 10:
            grafo.mostrar_arcos()

        elif opcion == 11:
            grafo.mostrar_ciudades()

        elif opcion == 0:
            print("Gracias por utilizar el sistema.")
            break

        else:
            print("Opción no válida.")


if __name__ == "__main__":
    menu()
