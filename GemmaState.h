#ifndef GEMMASTATE_H
#define GEMMASTATE_H

#include <QStateMachine>
#include <QEvent>
#include <QString>
#include <chrono>
#include "CyclicExecutionState.h"
#include <functional>

class GuiaGEMMA : public QObject
{
    Q_OBJECT
public:
    GuiaGEMMA();
    QStateMachine machine;
    int i =0, n = 0, j = 0;

private:
    
    bool check = false;
    QTimer *timer;
    void transition();

//Funciones de los estados
public slots:
    void func_s1();
    void func_s2();
    void func_s3();
    
//Señales para transiciones entre estados
signals: 
    void goToS2();
    void goToS3();
    void goToS1();
};


#endif // GEMMASTATE_H