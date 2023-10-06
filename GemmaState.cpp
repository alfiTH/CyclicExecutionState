#include "GemmaState.h"

GuiaGEMMA::GuiaGEMMA()
{
    //Crear los estados
    CyclicExecutionState *s1 = new CyclicExecutionState("s1", 500, std::bind(&GuiaGEMMA::func_s1, this));
    CyclicExecutionState *s2 = new CyclicExecutionState("s2", 500, std::bind(&GuiaGEMMA::func_s2, this));
    CyclicExecutionState *s3 = new CyclicExecutionState("s3", 500, std::bind(&GuiaGEMMA::func_s3, this));

    //enlaza las transiciones
    s1->addTransition(this, SIGNAL(goToS2()), s2);
    s2->addTransition(this, SIGNAL(goToS3()), s3);
    s2->addTransition(this, SIGNAL(goToS1()), s1);
    s3->addTransition(this, SIGNAL(goToS1()), s1);

    // Configuración de la Máquina de Estado
    machine.addState(s1);
    machine.addState(s2);
    machine.addState(s3);

    machine.setChildMode(QState::ExclusiveStates);  // Maquina en serie sin estados paralelos
    machine.setInitialState(s1);                    // Estado inicial

    //Arranca la maquina
    machine.start();
    auto error = machine.errorString();
    if (error.length() > 0){
        qWarning() << error;
        throw error;
    }


    //Comprobador de cual estado esta activo(solo visual, no es necesario)
    timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &GuiaGEMMA::transition);
    timer->start(1000);
}   

//Función de visualización de estados activos
void GuiaGEMMA::transition(){
    QSet<QAbstractState*> activeStates = machine.configuration();
    for(QAbstractState* state : activeStates) 
        qDebug() << "Estado activo:" << state->objectName();
}


/////////////////////Funciones de ejecución de estados////////////////////
///////////////////////////Como sui fueran computes///////////////////////
void GuiaGEMMA::func_s1() {
    
    qInfo()<<"s1"<<i;
    i++;

    if (i>5){
        i = 0;
        emit goToS2();
    }    
}
void GuiaGEMMA::func_s2() {
    if (check)
    {
        qInfo()<<"s2"<<n;
        n--;
    }
    else{
        qInfo()<<"s2"<<n;
        n++;
    }
    
    if (n>5){
        n = 0;
        check=true;
        emit goToS3();
    }
    if (n<-5){
        n = 0;
        emit goToS1();
    }
}
void GuiaGEMMA::func_s3() {
    qInfo()<<"s3"<<j;
    j++;

    if (j>10){
        j = 0;
        emit goToS1();
    }
}
