/****************************************************************************
* File name: MyState.h
* Author: Alejandro Torrejon Harto
* Date: 05/10/2023
* Description: QState wrapper to execute functions in a cyclic way while the state is active.
****************************************************************************/

#ifndef CYCLICEXECUTIONSTATE_H
#define CYCLICEXECUTIONSTATE_H
#define DEBUG 0

#include <QState>
#include <QTimer>
#include <iostream>


/**
 * @class CyclicExecutionState
 * @brief Class representing a state.
 *
 * QState wrapper to execute functions cyclically while the state is active.
 */
class CyclicExecutionState : public QState
{
    Q_OBJECT

public:
    explicit CyclicExecutionState(QString name, int period_ms, const std::function<void()>& function);
    ~CyclicExecutionState();
    void changePeriod(int period_ms);

protected:
    void onEntry(QEvent *event) ;
    void onExit(QEvent *event) ;

private:
    QTimer *timer_state;            //Cyclic timer of execution of the function
    std::function<void()> function; //Function to be executed
};
#endif // CYCLICEXECUTIONSTATE_H