#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QColor>
#include <QVector2D>
#include <GL/glu.h>
#include "game.h"

// Classe dediee a l'affichage d'une scene OpenGL //YANG
class MyGLWidget : public QGLWidget
{
    Q_OBJECT

public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);
    void startGame();



    int getNumberOfball();
    int getLevel();
    int getScore();
    void setWidth(float width);
    void updateGame();
    float getWidthOfPlatform();
    Game* getGame();
    ~MyGLWidget();

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);

private:
    Game* g;
    // Quelques variables a definir
public slots:

};

#endif // MYGLWIDGET_H
