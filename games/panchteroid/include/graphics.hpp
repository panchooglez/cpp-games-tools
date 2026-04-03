#pragma once
#include <array>
#include "vec2.hpp"

namespace ArteMatematico {

// Generador Aleatorio de Cómputo (LCG - Linear Congruential Generator)
// Fórmula matemática muy antigua y rápida que simula caos.
class GeneradorCaos {
    unsigned int estado;
public:
    constexpr GeneradorCaos(unsigned int semilla) : estado(semilla) {}
    
    constexpr unsigned int siguiente() {
        estado = (estado * 1664525) + 1013904223;
        return estado;
    }

    constexpr float float_aleatorio() {
        return static_cast<float>(siguiente() % 10000) / 10000.0f;
    }
};

constexpr std::size_t FRAMES_FUEGO = 16;
using TrianguloFuego = std::array<vec2, 3>;
using AnimacionFuego = std::array<TrianguloFuego, FRAMES_FUEGO>;

constexpr AnimacionFuego generar_propulsor() {
    AnimacionFuego anim{};
    GeneradorCaos caos(98765);

    for (std::size_t i = 0; i < FRAMES_FUEGO; ++i) {
        float ancho = 20.0f + (caos.float_aleatorio() * 15.0f);
        float largo = 35.0f + (caos.float_aleatorio() * 50.0f);
        float desvio_x = (caos.float_aleatorio() * 8.0f) - 4.0f;

        anim[i][0] = vec2{ -ancho / 2.0f, 0.0f };
        anim[i][1] = vec2{ ancho / 2.0f, 0.0f };
        anim[i][2] = vec2{ desvio_x, largo };
    }

    return anim;
}

constexpr auto FUEGO_NAVE = generar_propulsor();

}