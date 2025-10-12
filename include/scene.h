#ifndef SCENE_H
#define SCENE_H

class Scene {
private:
    int time;  // timestamp da cena

public:
    // Construtor padrão
    Scene();

    // Construtor parametrizado
    Scene(int time);

    // Getter
    int getTime() const;

    // Setter
    void setTime(int newTime);
};

#endif // SCENE_H
