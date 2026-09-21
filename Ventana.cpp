#include "Ventana.h"

Ventana::Ventana(QWidget *parent) : Serpiente(parent) {
    setWindowTitle("Serpiente");
    resize(400, 300); // Set the size of the window
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}