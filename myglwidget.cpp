#include "myglwidget.h"
#include "losedialog.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTime>
#include <QTimer>
#include<cstdlib>
#include<ctime>

// Declarations des constantes
const unsigned int WIN_WIDTH  = 1200;
const unsigned int WIN_HEIGHT = 900;
const float MAX_DIMENSION     = 40.0f;

// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN_WIDTH, WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    // Creation et demarrage du timer
}

// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    g=new Game();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Activation du zbu ffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    GLfloat Cblanc[]={1.0,1.0,1.0,1.0};
    GLfloat PositionLamp[]={0.0,0.0,5.0,0.1};
    glLightfv(GL_LIGHT0,GL_POSITION,PositionLamp);
    glLightfv(GL_LIGHT0,GL_AMBIENT_AND_DIFFUSE,Cblanc);

    // Activation de la lumiere
    glEnable(GL_LIGHTING);
}

// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);

    // Definition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(width != 0)
        glOrtho(-MAX_DIMENSION, MAX_DIMENSION, -MAX_DIMENSION * height / static_cast<float>(width), MAX_DIMENSION * height / static_cast<float>(width), -MAX_DIMENSION * 2.0f, MAX_DIMENSION * 2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Definition de la matrice de projection

}

// Fonction d'affichage
void MyGLWidget::paintGL()

{
    GLfloat Cblanc[]={1.0,1.0,1.0,1.0};
    GLfloat PositionLamp[]={0.0,0.0,5.0,0.1};
    glLightfv(GL_LIGHT0,GL_POSITION,PositionLamp);
    glLightfv(GL_LIGHT0,GL_AMBIENT_AND_DIFFUSE,Cblanc);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Definition de la position de la camera
    gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);
    g->afficher();
}

// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        // Changement de couleur du fond
        case Qt::Key_B:
        {
        g->getBall_()->setDirection_(0.0);
            break;
        }

        // Changement de couleur de l'objet
        case Qt::Key_C:
        {
        g->getBall_()->setDirection_(1.0/2*M_PI);
            break;
        }

        // Affichage/Masquage de l'objet
        case Qt::Key_H:
        {
            srand((unsigned)time(NULL));
            if(g->getBall_()->getSpeed_()==0.0)
                g->getBall_()->setSpd(0.4+g->getLevel()*(rand()/double(RAND_MAX))*0.6);
            break;
        }

        // Changement de l'objet a afficher
        case Qt::Key_Space:
        {
            g->getBall_()->setPos(0.0,0.0);
            break;
        }
        case Qt::Key_Left:
        {
            if(g->getBall_()->getSpeed_()==0.0)
                g->getBall_()->translation(-3.5);
            g->getPlatform_()->movePlatform(-3.5);
            break;
        }
        case Qt::Key_Right:
        {
            if(g->getBall_()->getSpeed_()==0.0)
                g->getBall_()->translation(3.5);
            g->getPlatform_()->movePlatform(3.5);
            break;
        }
        // Sortie de l'application
        case Qt::Key_Escape:
        {
            break;
        }

        // Cas par defaut
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}

void MyGLWidget::updateGame()
{
    LoseDialog l;

    if(g->isWin())
        g->nextLevel();
    else
        if(g->isLose())
        {
            g->resetGame();
            l.exec();
        }
        else
            g->update();

    updateGL();
}

int MyGLWidget::getNumberOfball()
{
    return g->getNumberOfBall();
}

int MyGLWidget::getLevel()
{
    return g->getLevel();
}

int MyGLWidget::getScore()
{
    return g->getScore();
}

float MyGLWidget::getWidthOfPlatform()
{
    return g->getPlatform_()->getWidth_();
}

void MyGLWidget::setWidth(float width)
{
    g->getPlatform_()->setWidth(width);
}

Game* MyGLWidget::getGame()
{
    return g;
}

MyGLWidget::~MyGLWidget(){
    delete g;
}
