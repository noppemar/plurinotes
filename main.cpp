#include <QApplication>
#include <QtWidgets>
#include "FenPrincipale.h"
#include "notes.h"
#include "histonotes.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FenetrePrincipale fenetre;

    
    QString filename= QFileDialog::getOpenFileName();   //chercher le fichier xml
    HistoNoteManager &m=HistoNoteManager::getInstance(); //créer une instance de NotesManager
    m.setFilename(filename); //fixer le nom du fichier dans l'instance NotesManager
    m.load();   //charger le fichier
    fenetre.updateNotes();
    fenetre.updateTaches();

    fenetre.show();

    return app.exec();
}
