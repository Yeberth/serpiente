

/*
    Author: Yeberth Martinez
    Creditos: @zapsap0853 musica
    descripcion: Juego de la serpiente en C++ usando Qt
*/


#include "Ventana.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Ventana ventana;
    ventana.show();
    return app.exec();
}