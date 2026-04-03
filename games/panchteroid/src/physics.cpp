#include "vec2.hpp"
#include "physics.hpp"
#include <numbers>
#include <cstdlib>


void Nave::update(bool acc, bool right, bool left, float dt){
    if(right) angle = std::fmod((angle - (dt *5)) , (2.0f * std::numbers::pi_v<float>));
    if(left) angle = std::fmod((angle + (dt *5)) , (2.0f * std::numbers::pi_v<float>));

    // tenemos un vector en el plano complejo
    // modulo acc y argumento angle
    // en coordenadas cartesianas eso es:
    // (acc * cos(angle) , - acc * sen(angle))
    vec2 acc_vec { (acc*dt) * std::cos(angle), -(acc*dt) * std::sin(angle)};

    vel += acc_vec;
    head += vel * 200 * dt;
}