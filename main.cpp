#include <QCoreApplication>
#include <QStateMachine>
#include "GemmaState.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    GuiaGEMMA gemma;
    return app.exec();
};
