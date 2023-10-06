/****************************************************************************
* File name: MyState.cpp
* Author: Alejandro Torrejon Harto
* Date: 05/10/2023
* Description: QState wrapper to execute functions in a cyclic way while the state is active.
****************************************************************************/

#include "CyclicExecutionState.h"

/**
 * @brief Builds MyState object
 *
 * This function takes the name of the state, execution period, function to execute, to build the object.
 *
 * @param name Name of the state.
 * @param period_ms Period of cyclic execution.
 * @param function Function to execute.
 */
CyclicExecutionState::CyclicExecutionState(QString name, int period_ms,  const std::function<void()>& function){
    #if DEBUG
        std::cout << "Construyendo MyState "<< name.toStdString() <<std::endl<<std::flush;
    #endif
    this->setObjectName(name);                  // Set object name

    this->function = function;                  // Set function to execute
    this->timer_state = new QTimer(this);       //Create cyclic timer
    this->timer_state->setInterval(period_ms);  //Set time to cyclic timer

    //Connecting the cyclic timer to the function 
    connect(this->timer_state, &QTimer::timeout, this, [this](){this->function();});
    #if DEBUG
        std::cout << "Construido MyState"<< this->objectName().toStdString() <<std::endl<<std::flush;
    #endif
}

/**
 * @brief Destroy MyState object
 *
 * This function destroys and frees the object's memory
 */
CyclicExecutionState::~CyclicExecutionState() {
    this->timer_state->stop();  //Stop cyclic timer
    delete this->timer_state;   //Delete cyclic timer
    #if DEBUG
        std::cout << "Dell MyState"<< this->objectName().toStdString()<<std::endl<<std::flush;
    #endif
}

/**
 * @brief Changes the period of the cyclic execution
 *
 * This function modifies the execution period and restarts with the new time in case it is active.
 *
 * @param period_ms Period of cyclic execution.
 */
void CyclicExecutionState::changePeriod(int period_ms)
{
    //Set new time to cyclic timer
    this->timer_state->setInterval(period_ms);
    //Restart cyclic timer
    if (this->active()){
        timer_state->stop();
        timer_state->start();
    }
}

/**
 * @brief When the status is activated this function is executed. 
 *
 * This function launches the cyclic timer that executes the configured function, event is not used.
 */
void CyclicExecutionState::onEntry(QEvent *event)
{
    Q_UNUSED(event)
    this->timer_state->start();     //Launches the cyclic timer
    #if DEBUG
        std::cout << "Entrando en MyState "<< this->objectName().toStdString() <<std::endl<<std::flush;
    #endif
}

/**
 * @brief When the status is deactivated this function is executed. 
 *
 * This function stops the cyclic timer that executes the configured function, event is not used.
 */
void CyclicExecutionState::onExit(QEvent *event)
{
    Q_UNUSED(event)
    this->timer_state->stop();      //Stops the cyclic timer
    #if DEBUG
        std::cout<< "Saliendo de MyState "<< this->objectName().toStdString() <<std::endl<<std::flush;
    #endif
}