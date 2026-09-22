#ifndef SERPPIENTE_H
#define SERPPIENTE_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSoundEffect>
#include <QElapsedTimer>
#include <QPushButton>
#include <QResizeEvent>
#include <QVector>

class Serpiente : public QWidget {
    Q_OBJECT
public:
    Serpiente(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void moveSnake();
    void generateFood();
    bool hasCollision(const QPoint &head) const;

private slots:
    void startGame();
    void retryGame();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    static constexpr int bannerHeight = 32;
    static constexpr int playTop = 40;
    QTimer *timer;
    QElapsedTimer gameClock;
    QVector<QPoint> snake;
    QPoint food{-10, -10};
    int direction = 1; // 0: up, 1: right, 2: down, 3: left
    bool gameOver = false;
    int elapsedSeconds = 0;
    int score = 0;
    QMediaPlayer eatSound;
    QMediaPlayer gameOverSound;
    QMediaPlayer songButton;
    QMediaPlaylist ambientPlaylist;
    QMediaPlayer ambientSound;
    QPushButton *playButton;
    QPushButton *retryButton;
};

#endif // SERPPIENTE_H