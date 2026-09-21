#include "Serpiente.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>
#include <QCoreApplication>
#include <QDir>
#include <QUrl>

Serpiente::Serpiente(QWidget *parent) : QWidget(parent) {
    resize(400, 300);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Serpiente::moveSnake);
    timer->start(100); // Move every 100 ms
    snake.append(QPoint(50, playTop + 10)); // Initial position
    gameClock.start();

    const QString audioPath = QCoreApplication::applicationDirPath() + "/audio/";
    ambientSound.setMedia(QUrl::fromLocalFile(audioPath + "ambient.wav"));
    ambientSound.setVolume(20);
    eatSound.setMedia(QUrl::fromLocalFile(audioPath + "eat.mp3"));
    eatSound.setVolume(80);
    gameOverSound.setMedia(QUrl::fromLocalFile(audioPath + "Gunshot1.wav"));
    gameOverSound.setVolume(50);
    songButton.setMedia(QUrl::fromLocalFile(audioPath + "buttom.mp3"));
    songButton.setVolume(80);

    ambientSound.play();
    generateFood();
}

void Serpiente::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        if (direction != 2) { // Prevent reversing
            songButton.stop();
            songButton.setPosition(0);
            songButton.play();
            direction = 0;
        }
        break;
    case Qt::Key_Right:
        if (direction != 3) {
            songButton.stop();
            songButton.setPosition(0);
            songButton.play();
            direction = 1;
        }
        break;
    case Qt::Key_Down:
        if (direction != 0) {
            songButton.stop();
            songButton.setPosition(0);
            songButton.play();
            direction = 2;
        }
        break;
    case Qt::Key_Left:
        if (direction != 1) {
            songButton.stop();
            songButton.setPosition(0);
            songButton.play();
            direction = 3;
        }
        break;
    }
}

void Serpiente::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    painter.fillRect(0, 0, width(), bannerHeight, QColor(35, 35, 35));
    painter.setPen(QColor(90, 90, 90));
    painter.drawRect(0, playTop, width() - 1, height() - playTop - 1);
    painter.setPen(Qt::white);
    painter.drawText(
        QRect(12, 0, width() - 24, bannerHeight),
        Qt::AlignVCenter | Qt::AlignLeft,
        QString("Tiempo: %1 s").arg(elapsedSeconds));
    painter.drawText(
        QRect(12, 0, width() - 24, bannerHeight),
        Qt::AlignVCenter | Qt::AlignRight,
        QString("Puntos: %1").arg(score));

    painter.setBrush(Qt::green);
    for (const auto &point : snake) {
        painter.drawRect(point.x(), point.y(), 10, 10);
    }
    painter.setBrush(Qt::red);
    painter.drawRect(food.x(), food.y(), 10, 10);

    if (gameOver) {
        painter.setPen(Qt::white);
        painter.drawText(
            rect().adjusted(0, bannerHeight, 0, 0),
            Qt::AlignCenter,
            "Game Over");
    }
}

void Serpiente::moveSnake() {
    if (gameOver) {
        return;
    }

    elapsedSeconds = static_cast<int>(gameClock.elapsed() / 1000);
    QPoint head = snake.first();
    switch (direction) {
    case 0: // up
        head.setY(head.y() - 10);
        break;
    case 1: // right
        head.setX(head.x() + 10);
        break;
    case 2: // down
        head.setY(head.y() + 10);
        break;
    case 3: // left
        head.setX(head.x() - 10);
        break;
    }

    if (hasCollision(head)) {
        gameOver = true;
        elapsedSeconds = static_cast<int>(gameClock.elapsed() / 1000);
        timer->stop();
        gameOverSound.stop();
        gameOverSound.setPosition(0);
        gameOverSound.play();
        ambientSound.stop();
        update();
        return;
    }

    snake.prepend(head);

    if (head == food) {
        ++score;
        elapsedSeconds = static_cast<int>(gameClock.elapsed() / 1000);
        eatSound.stop();
        eatSound.setPosition(0);
        eatSound.play();
        generateFood();
    } else {
        snake.removeLast();
    }

    update();
}

bool Serpiente::hasCollision(const QPoint &head) const {
    if (head.x() < 0 || head.y() < playTop ||
        head.x() + 10 > width() || head.y() + 10 > height()) {
        return true;
    }

    for (int i = 1; i < snake.size(); ++i) {
        if (snake.at(i) == head) {
            return true;
        }
    }

    return false;
}

void Serpiente::generateFood() {
    const int columns = qMax(1, width() / 10);
    const int rows = qMax(1, (height() - playTop) / 10);
    const int cellCount = columns * rows;
    QRandomGenerator *generator = QRandomGenerator::global();

    for (int attempt = 0; attempt < cellCount; ++attempt) {
        const QPoint candidate(
            generator->bounded(columns) * 10,
            playTop + generator->bounded(rows) * 10);

        bool occupied = false;
        for (const QPoint &segment : snake) {
            if (segment == candidate) {
                occupied = true;
                break;
            }
        }

        if (!occupied && candidate != food) {
            food = candidate;
            return;
        }
    }

    gameOver = true;
    timer->stop();
}