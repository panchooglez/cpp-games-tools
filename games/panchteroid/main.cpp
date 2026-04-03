#include "raylib.h"
#include "vec2.hpp"
#include "physics.hpp"
#include "graphics.hpp"
#include <numbers>
#include <cstdlib>
#include <iostream>

void draw_nave(Nave& nave, bool acelerando) {
    float head_x = nave.head.x;
    float head_y = nave.head.y;
    float altura_nave = 150.0f;
    float angle_back = std::fmod((nave.angle + std::numbers::pi), (2.0f * std::numbers::pi));

    // Vectores de la estructura de la nave
    vec2 back {altura_nave * std::cos(angle_back), -altura_nave * std::sin(angle_back)};
    vec2 back_side {(altura_nave/5) * std::sin(angle_back), (altura_nave/5) * std::cos(angle_back)};
    
    vec2 pos_left = nave.head + back + back_side;
    vec2 pos_right = nave.head + back - back_side;

    // Dibujar la nave
    DrawTriangle(
        {head_x, head_y}, 
        {pos_left.x, pos_left.y}, 
        {pos_right.x, pos_right.y}, 
        BLUE
    );

    // Solo dibujamos el fuego si estamos apretando la tecla
    if (acelerando) {
        int frameActual = static_cast<int>(GetTime() * 20.0) % 16;
        auto frameFuego = ArteMatematico::FUEGO_NAVE[frameActual]; 

        float ang = nave.angle;
        float s = -std::sin(ang  - std::numbers::pi / 2);
        float c = std::cos(-ang + std::numbers::pi / 2);

        // Usar el vector 'back' para anclar el fuego exactamente atrás
        vec2 centro_trasero = nave.head + back;

        // Transformamos los 3 vértices del triángulo (rotación + traslación al centro trasero)
        vec2 v1 = {
            centro_trasero.x + (frameFuego[0].x * c - frameFuego[0].y * s),
            centro_trasero.y + (frameFuego[0].x * s + frameFuego[0].y * c)
        };
        vec2 v2 = {
            centro_trasero.x + (frameFuego[1].x * c - frameFuego[1].y * s),
            centro_trasero.y + (frameFuego[1].x * s + frameFuego[1].y * c)
        };
        vec2 v3 = {
            centro_trasero.x + (frameFuego[2].x * c - frameFuego[2].y * s),
            centro_trasero.y + (frameFuego[2].x * s + frameFuego[2].y * c)
        };

        // Dibujamos el fuego en ese frame
        DrawTriangle({v1.x, v1.y}, {v3.x, v3.y}, {v2.x, v2.y}, RED);
    }
}

int main() {
    // Inicialización
    const int screenWidth = 2400;
    const int screenHeight = 1400;
    Nave nave { vec2{500.0f, 500.0f}, vec2{0.0f, 0.0f}, 3 * std::numbers::pi / 4};
    bool acc = false;
    bool left = false;
    bool right = false;
    InitWindow(screenWidth, screenHeight, "Clon de Asteroids - Motor Propio");
    SetTargetFPS(60); // Clavamos el juego a 60 FPS

    // Game Loop
    while (!WindowShouldClose()) { // Detecta si pulsas la X de la ventana o ESC
        
        // --- INPUTS ---
        acc = IsKeyDown(265);
        if(acc) std::cout << "Acc";
        left = IsKeyDown(263);
        if(left) std::cout << "Left";
        right = IsKeyDown(262);
        if(right) std::cout << "Right";
        float dt = GetFrameTime();

        nave.update(acc, right, left, dt);
        

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            
            draw_nave(nave, acc);

        EndDrawing();
    }

    // Liberar Recursos
    CloseWindow();
    return 0;
}