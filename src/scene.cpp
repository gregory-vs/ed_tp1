#include "scene.h"

// Construtor padrão (inicializa com zero)
Scene::Scene() {
    time = 0;
}

// Construtor parametrizado
Scene::Scene(int time) {
    this->time = time;
}

// Getter
int Scene::getTime() const {
    return time;
}

// Setter
void Scene::setTime(int newTime) {
    this->time = newTime;
}
