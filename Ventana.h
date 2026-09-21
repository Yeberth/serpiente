#ifndef VENTANA_H
#define VENTANA_H

#include <QApplication>
#include <QWidget>
#include "Serpiente.h"

class Ventana : public Serpiente {
    Q_OBJECT
    int x, y;

public:
    Ventana(QWidget *parent = nullptr);
    void setPos(int x, int y) {
        this->x = x;
        this->y = y;
        move(x, y);
    }
};

#endif // VENTANA_H