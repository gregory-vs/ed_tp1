#include <iostream>
#include "objeto.h"
using namespace std;


int main() {
    const int MAX = 100;
    Objeto objetos[MAX];
    int qtd = 0;

    inserirObjeto(objetos, qtd, MAX, 1, 4.0, 2.5, 3.0);
    inserirObjeto(objetos, qtd, MAX, 2, 2.5, 5.0, 3.0);
    inserirObjeto(objetos, qtd, MAX, 3, 6.0, 1.0, 2.0);

    cout << "Objetos iniciais:" << endl;
    imprimirObjetos(objetos, qtd);

    atualizarPosicao(objetos, qtd, 2, 3.5, 6.0);

    cout << "\nDepois de atualizar o objeto 2:" << endl;
    imprimirObjetos(objetos, qtd);

    return 0;
}
