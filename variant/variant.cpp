#include "variant.h"
#include <sstream>
#include <stdexcept>

// Constructor para inicializar un Variant sin valor asociado
Variant::Variant(variant_type tipo) : tipo(tipo), entorno(nullptr), procedimiento(nullptr) {}

// Constructor para inicializar un Variant con un valor asociado
Variant::Variant(variant_type tipo, const std::string& valor) : tipo(tipo), valor(valor), entorno(nullptr), procedimiento(nullptr) {}

// Constructor para inicializar un Variant con un procedimiento
Variant::Variant(proc_type procedimiento) : tipo(Proc), procedimiento(procedimiento), entorno(nullptr) {}

// Convierte el contenido de Variant a una representación en cadena
std::string Variant::to_string() const {
    std::ostringstream flujo;
    switch (tipo) {
        case Symbol:
        case Cadena:
        case Number:
            flujo << valor; // Para valores simples como símbolos, cadenas o números
            break;
        case List:
            flujo << "(";
            for (size_t i = 0; i < lista.size(); ++i) {
                if (i > 0) flujo << " "; // Separar los elementos con un espacio
                flujo << lista[i].to_string();
            }
            flujo << ")";
            break;
        case Proc:
        case Lambda:
            flujo << "<procedimiento>"; // Representación genérica para procedimientos
            break;
    }
    return flujo.str();
}

// Convierte el contenido de Variant a una cadena JSON
std::string Variant::to_json_string() const {
    json11::Json::object objeto;
    objeto["tipo"] = json11::Json(static_cast<int>(tipo)); // Almacenar el tipo como entero

    switch (tipo) {
        case Symbol:
        case Cadena:
        case Number:
            objeto["valor"] = json11::Json(valor); // Almacenar el valor directamente
            break;
        case List: {
            json11::Json::array arreglo;
            for (const auto& elemento : lista) {
                std::string error;
                json11::Json parseado = json11::Json::parse(elemento.to_json_string(), error);
                if (!error.empty()) {
                    throw std::runtime_error("Error al parsear JSON: " + error);
                }
                arreglo.push_back(parseado);
            }
            objeto["valor"] = arreglo; // Almacenar la lista como un arreglo JSON
            break;
        }
        case Proc:
        case Lambda:
            objeto["valor"] = json11::Json("<procedimiento>"); // Representación genérica
            break;
    }

    return json11::Json(objeto).dump();
}

// Convierte una cadena JSON a un objeto Variant
Variant Variant::from_json_string(const std::string& json) {
    std::string error;
    json11::Json parseado = json11::Json::parse(json, error);
    if (!error.empty()) {
        throw std::runtime_error("Error al parsear JSON: " + error);
    }
    return parsear_json(parseado);
}

// Método auxiliar para procesar y convertir un JSON a Variant
Variant Variant::parsear_json(const json11::Json& parseado) {
    if (!parseado.is_object()) {
        throw std::runtime_error("Formato JSON no válido");
    }

    int tipo = parseado["tipo"].int_value(); // Recuperar el tipo desde el JSON
    Variant resultado(static_cast<variant_type>(tipo));

    switch (resultado.tipo) {
        case Symbol:
        case Cadena:
        case Number:
            resultado.valor = parseado["valor"].string_value(); // Recuperar el valor
            break;
        case List:
            for (const auto& elemento : parseado["valor"].array_items()) {
                resultado.lista.push_back(parsear_json(elemento)); // Procesar recursivamente
            }
            break;
        case Proc:
        case Lambda:
            throw std::runtime_error("No se pueden deserializar procedimientos"); // No permitido
    }

    return resultado;
}
