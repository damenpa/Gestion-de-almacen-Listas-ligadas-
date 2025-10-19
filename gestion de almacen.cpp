#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef struct Nodo
{
    int id;
    int reorden;
    float precio;
    string nombreProducto;
    int existencia;
    int maximo;
    int ganancia;
    struct Nodo* siguiente;
} Nodo;

Nodo* inicio = NULL;
float capitalInicial = 8000000.00;

void altas(int id_a, float precio_a, string nombreProducto_a, int existencia_a) {
    Nodo* nuevoNodo = new Nodo();
   
    if (nuevoNodo == NULL) {
        cout << "no se puede crear nodo";
        return;
    }
    
    float costoTotal = existencia_a * precio_a;
    if (costoTotal > capitalInicial) {
        cout << "Error: Capital insuficiente para realizar esta compra" << endl;
        cout << "Costo: " << costoTotal << ", Capital disponible: " << capitalInicial << endl;
        delete nuevoNodo;
        return;
    }
    
    capitalInicial = capitalInicial - costoTotal; 
        
    nuevoNodo->id = id_a;
    nuevoNodo->precio = precio_a;
    nuevoNodo->nombreProducto = nombreProducto_a;
    nuevoNodo->existencia = existencia_a;
    nuevoNodo->siguiente = NULL;
    
    if (inicio == NULL) {
        inicio = nuevoNodo;
    } else {
        Nodo* actual = inicio;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    
    cout << "Articulo agregado exitosamente!" << endl;
    cout << "Capital restante: " << capitalInicial << endl;
}

void buscar() {
    int buscar;
    cout << "\nIngresa el id del articulo por buscar: ";
    cin >> buscar;
    
    Nodo* actual = inicio;
    while (actual != NULL && actual->id != buscar) {
        actual = actual->siguiente;
    }
    
    if (actual == NULL) {
        cout << "Articulo no encontrado!" << endl;
        return;
    }
    
    cout << "id: " << actual->id << endl;
    cout << "Nombre del producto: " << actual->nombreProducto << endl;
    cout << "Precio del producto: " << actual->precio << endl;
    cout << "Existencia: " << actual->existencia << endl;
}

void listar() {
    if (inicio == NULL) {
        cout << "No hay articulos en el inventario" << endl;
        return;
    }
    
    Nodo* actual = inicio;
    while (actual != NULL) {
        cout << "id: " << actual->id << endl;
        cout << "Nombre del producto: " << actual->nombreProducto << endl;
        cout << "Precio del producto: " << actual->precio << endl;
        cout << "Existencia: " << actual->existencia << endl;
        cout << "------------------------" << endl;
        actual = actual->siguiente;
    }
}

void compras() {
    int idCompras, piezas;
    cout << "---COMPRAR---" << endl;
    
    if (inicio == NULL) {
        cout << "No hay articulos en el inventario" << endl;
        return;
    }
    
    Nodo* actual = inicio;
    while (actual != NULL) {
        cout << "id: " << actual->id << endl;
        cout << "Nombre del producto: " << actual->nombreProducto << endl;
        cout << "Precio del producto: " << actual->precio << endl;
        cout << "Existencia: " << actual->existencia << endl;
        cout << "------------------------" << endl;
        actual = actual->siguiente;
    }
    
    cout << "Ingresa el id del producto que deseas comprar: ";
    cin >> idCompras;
    cout << "Ingresa la cantidad de piezas que deseas comprar: ";
    cin >> piezas;
    
    if (piezas <= 0) {
        cout << "Error: Cantidad invalida" << endl;
        return;
    }
    
    actual = inicio;
    while (actual != NULL && actual->id != idCompras) {
        actual = actual->siguiente;
    }
    
    if (actual == NULL) {
        cout << "ERROR: ID INEXISTENTE" << endl;
        return;
    }
    
    float costoTotal = piezas * actual->precio;
    if (costoTotal > capitalInicial) {
        cout << "Error: Capital insuficiente para realizar esta compra" << endl;
        cout << "Costo: " << costoTotal << ", Capital disponible: " << capitalInicial << endl;
        return;
    }
    
    actual->existencia = actual->existencia + piezas;
    capitalInicial = capitalInicial - costoTotal;
    
    cout << "Compra realizada exitosamente!" << endl;
    cout << "Nueva existencia: " << actual->existencia << endl;
    cout << "Capital restante: " << capitalInicial << endl;
}

void venta() {
    int idVentas, piezas, salir;
    cout << "---VENTAS---" << endl;
    
    if (inicio == NULL) {
        cout << "No hay articulos en el inventario" << endl;
        return;
    }
    
    Nodo* actual = inicio;
    while (actual != NULL) {
        cout << "id: " << actual->id << endl;
        cout << "Nombre del producto: " << actual->nombreProducto << endl;
        cout << "Precio del producto: " << actual->precio << endl;
        cout << "Existencia: " << actual->existencia << endl;
        cout << "------------------------" << endl;
        actual = actual->siguiente;
    }
    
    cout << "Ingresa el id del producto que deseas vender: ";
    cin >> idVentas;
    cout << "Ingresa la cantidad de piezas que deseas vender: ";
    cin >> piezas;
    
    if (piezas <= 0) {
        cout << "Error: Cantidad invalida" << endl;
        return;
    }
    
    actual = inicio;
    while (actual != NULL && actual->id != idVentas) {
        actual = actual->siguiente;
    }
    
    if (actual == NULL) {
        cout << "ERROR: ID INEXISTENTE" << endl;
        return;
    }
    
    if (actual->existencia >= piezas) {
        actual->existencia = actual->existencia - piezas;
        capitalInicial = capitalInicial + (piezas * actual->precio);
        cout << "Venta completada exitosamente!" << endl;
        cout << "Nueva existencia: " << actual->existencia << endl;
        cout << "Capital actual: " << capitalInicial << endl;
    } else {
        cout << "Lo sentimos, por el momento solo tenemos " << actual->existencia 
             << " piezas disponibles para poder vender" << endl 
             << "Presiona 1 si deseas vender las disponibles o 2 si deseas salir al menu: ";
        cin >> salir;
        if (salir == 1) {
            int disponibles = actual->existencia;
            actual->existencia = 0;
            capitalInicial = capitalInicial + (disponibles * actual->precio);
            cout << "Venta completada con " << disponibles << " piezas" << endl;
            cout << "Capital actual: " << capitalInicial << endl;
        } else {
            return;
        }
    }
}

int main() {
    int menu, id_a, existencia_a;
    float precio_a;
    string nombreProducto_a;
    
    cout << "Bienvenido a nuestro sistema" << endl;
    
    do {      
        cout << "\nPor favor ingresa una opcion" << endl;
        cout << "1. Dar de alta un articulo" << endl;
        cout << "2. Lista de articulos" << endl;
        cout << "3. Buscar un articulo" << endl;
        cout << "4. Vender un articulo" << endl;
        cout << "5. Comprar articulos (reabastecer)" << endl;
        cout << "6. Salir" << endl;
        cout << "Opcion: ";
        cin >> menu;
        
        switch (menu) {
        case 1:
            cout << "\nIngresa el id: ";
            cin >> id_a;
            cout << "Ingresa el precio: ";
            cin >> precio_a;
            cin.ignore();
            cout << "Ingresa el nombre del producto: ";
            getline(cin, nombreProducto_a);
            cout << "Ingresa la existencia del producto: ";
            cin >> existencia_a;  
            altas(id_a, precio_a, nombreProducto_a, existencia_a);
            break;
        case 2:
            listar();
            break;
        case 3:
            buscar();
            break;
        case 4:
            venta();
            break;
        case 5:
            compras();
            break;
        case 6:
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            cout << "Opcion invalida!" << endl;
            break;
        }
    } while (menu != 6);
    
    Nodo* actual = inicio;
    while (actual != NULL) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    
    return 0;
}