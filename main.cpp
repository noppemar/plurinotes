#include <QApplication>
#include <QtWidgets>
#include "FenPrincipale.h"
#include "notes.h"
#include "histonotes.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FenetrePrincipale fenetre;

    HistoNoteManager  &instance=HistoNoteManager::getInstance();

    fenetre.show();

    return app.exec();
}
