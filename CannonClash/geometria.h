#include "Strutture.h"
#include "Entity.h"

void costruisci_piano(Entity* fig);
void costruisci_cuore(float cx, float cy, float raggiox, float raggioy, Entity* fig);
void costruisci_farfalla(float cx, float cy, float raggiox, float raggioy, Entity* fig);
void costruisci_proiettile(float cx, float cy, float raggiox, float raggioy, Forma* fig);
void crea_punti_forma_da_file(const char* nomeFile, const char* modalita, Forma* Curva);
