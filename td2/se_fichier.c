#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "se_fichier.h"

SE_FICHIER	SE_ouverture(const char *chemin, int acces)
{
	SE_FICHIER f;
	
	f.descripteur = (acces & O_CREAT) ? open(chemin, acces, 0644) : open(chemin, acces);
	f.chemin = (char*)chemin;
	f.acces = acces;
	return f;
}

int	SE_fermeture(SE_FICHIER fichier)
{
	return close(fichier.descripteur);
}

int	SE_suppression(const char *chemin)
{
	return unlink(chemin);
}

int	SE_lectureCaractere(SE_FICHIER fichier, char *caractere)
{
	return read(fichier.descripteur, caractere, sizeof(char));
}

int	SE_ecritureCaractere(SE_FICHIER fichier, const char caractere)
{
	return write(fichier.descripteur, &caractere, sizeof(char));
}
/*
int	SE_lectureChaine(SE_FICHIER fichier, char *chaine, int tailleMax)
{
	
}

int	SE_ecritureChaine(SE_FICHIER fichier, const char *chaine, int taille)
{
	
}

int	SE_lectureEntier(SE_FICHIER fichier, int *entier)
{
	
}

int	SE_ecritureEntier(SE_FICHIER fichier, const int entier)
{
	
}*/
