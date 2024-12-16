#ifndef VARIANT_H
#define VARIANT_H

#include <vector>
#include <string>
#include <map>
#include <json11.hpp> // Biblioteca para manejar JSON

// Enumeración para los diferentes tipos de Variant
enum variant_type { Symbol, Number, List, Proc, Lambda, Cadena };

// Declaración adelantada de la estructura Entorno
struct Entorno;

// Clase que representa un tipo de dato genérico
class Variant {
public:
    // Tipos de datos y alias utilizados dentro de la clase
    typedef Variant(*proc_type)(const std::vector<Variant>&); // Puntero a una función que procesa Variants
    typedef std::vector<Variant>::const_iterator iter;       // Iterador constante para listas de Variants
    typedef std::map<std::string, Variant> map;              // Mapa para asociar claves con Variants

    // Atributos principales de la clase
    variant_type tipo;               // Tipo del Variant (Symbol, Number, etc.)
    std::string valor;               // Valor asociado (si aplica)
    std::vector<Variant> lista;      // Lista de Variants para representar estructuras anidadas
    proc_type procedimiento;         // Procedimiento asociado (si es de tipo Proc)
    Entorno* entorno;                // Apunta a un entorno (contexto de ejecución)

    // Constructores de la clase
    Variant(variant_type tipo = Symbol);                   // Constructor por defecto o con tipo
    Variant(variant_type tipo, const std::string& valor);  // Constructor con tipo y valor
    Variant(proc_type procedimiento);                     // Constructor para procedimientos

    // Métodos para manejo de datos
    std::string to_string() const;                          // Convierte el Variant a cadena legible
    std::string to_json_string() const;                     // Convierte el Variant a formato JSON
    static Variant from_json_string(const std::string& json); // Crea un Variant a partir de una cadena JSON
    static Variant parsear_json(const json11::Json& parseado); // Método auxiliar para procesar JSON
};

#endif // VARIANT_H
