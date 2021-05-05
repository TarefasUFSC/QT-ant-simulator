#include "simulationenv.h"
#include "ant.h"
#include "colony.h"

#include <QKeyEvent>
#include <iostream>
using namespace std;
SimulationEnv::SimulationEnv(QWidget *parent )
{
    // criar scene
   //if(scene)
   scene = new QGraphicsScene();
   // fixar o tamanho em 800x600, que é infinito por definição
   scene->setSceneRect(0, 0, 1240, 720);
   setScene(scene);
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   // fixar o tamanho
   setFixedSize(1240, 720);


   timer = new QTimer();
   connect(timer, &QTimer::timeout, this, std::bind(&SimulationEnv::step, this));
}
void SimulationEnv::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Enter){
        for(Colony *c : colonyList){
            if(!c->createdAnts){
                for(int i = 0;i<antsNumber;i++){
                    Ant* a = new Ant();
                    scene->addItem(a);
                    antList.push_back(a);
                    a->setPos(c->x()+25,c->y()+25);
                    c->createdAnts = true;
                }
            }
        }
    }
}
void SimulationEnv::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        Colony *c = new Colony(nullptr,event->x(),event->y());
        scene->addItem(c);
        colonyList.push_back(c);
    }
}
void SimulationEnv::step(){
    for(Ant* a : antList){
        a->move();
    }
}
void SimulationEnv::startSimulation(bool showPath,int antNumber){
    showPaths = showPath;
    antsNumber = antNumber;
    timer->start(50);
    show();
}
