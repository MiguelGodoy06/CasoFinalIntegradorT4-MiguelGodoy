#include "variant/variant.h"
#include <iostream>

int main() {
    // Creamos objetos Variant para diferentes tipos de datos
    Variant miSimbolo(Symbol, "x");
    Variant miNumero(Number, "3.14");
    Variant miLista(List);

    // Agregamos elementos a la lista
    miLista.lista.push_back(miSimbolo);  // Cambié 'list' a 'lista'
    miLista.lista.push_back(miNumero);   // Cambié 'list' a 'lista'

    // Mostramos los elementos creados en la consola
    std::cout << "Simbolo: " << miSimbolo.to_string() << std::endl;
    std::cout << "Numero: " << miNumero.to_string() << std::endl;
    std::cout << "Lista: " << miLista.to_string() << std::endl;

    // Convertimos la lista a formato JSON y la imprimimos
    std::string cadenaJSON = miLista.to_json_string();
    std::cout << "JSON: " << cadenaJSON << std::endl;

    // Intentamos leer la lista desde un JSON
    try {
        Variant listaDesdeJSON = Variant::from_json_string(cadenaJSON);
        std::cout << "Desde JSON: " << listaDesdeJSON.to_string() << std::endl;
    } catch (const std::exception& error) {
        // Si ocurre un error al parsear el JSON, lo mostramos
        std::cerr << "Hubo un error: " << error.what() << std::endl;
    }

    return 0;
}
