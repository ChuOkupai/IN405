#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "se_fichier.h"

// Affichage du contenu d'un fichier
// \param	chemin	Nom/chemin du fichier à afficher
// \return			-1 si échec à l'ouverture, 0 sinon
int	affichage(const char *chemin)
{
	SE_FICHIER	f;
	char		c;
	
	f = SE_ouverture(chemin, O_RDONLY);
	if (f.descripteur == -1)
		return -1;
	while (SE_lectureCaractere(f, &c) > 0)
		putchar(c);
	if (SE_fermeture(f))
		return -1;
	return 0;
}

// Copie de fichier
// \param	chemin1	Nom/chemin du fichier source
// \param	chemin2	Nom/chemin du fichier destination
// \return			-1 si échec à l'ouverture, 0 sinon
int	copie(const char *chemin1, const char *chemin2)
{
	SE_FICHIER	f1, f2;
	char		c;
	
	f1 = SE_ouverture(chemin1, O_RDONLY);
	if (f1.descripteur == -1)
		return -1;
	f2 = SE_ouverture(chemin2, O_CREAT | O_WRONLY);
	if (f2.descripteur == -1)
	{
		SE_fermeture(f1);
		return -1;
	}
	while (SE_lectureCaractere(f1, &c) > 0)
	{
		if (SE_ecritureCaractere(f2, c) == -1)
		{
			SE_fermeture(f1);
			SE_fermeture(f2);
			return -1;
		}
	}
	SE_fermeture(f1);
	SE_fermeture(f2);
	return 0;
}

// Déplacement de fichier
// \param	chemin1	Nom/chemin du fichier source
// \param	chemin2	Nom/chemin du fichier destination
// \return			-1 si échec à l'ouverture, 0 sinon
int	deplacement(const char *chemin1, const char *chemin2)
{
	if (copie(chemin1, chemin2) == -1 || SE_suppression(chemin1) == -1)
		return -1;
	return 0;
}

// Comparaison entre deux fichiers
// \param	chemin1	Nom/chemin du premier fichier
// \param	chemin2	Nom/chemin du second fichier
// \return			-1 si échec à l'ouverture, 1 si fichiers identiques, 0 sinon
int	sontIdentiques(const char *chemin1, const char *chemin2)
{
	SE_FICHIER	f1, f2;
	int			r1, r2;
	char		c1, c2;
	
	f1 = SE_ouverture(chemin1, O_RDONLY);
	if (f1.descripteur == -1)
		return -1;
	f2 = SE_ouverture(chemin2, O_RDONLY);
	if (f2.descripteur == -1)
	{
		SE_fermeture(f1);
		return -1;
	}
	while (1)
	{
		c1 = 0;
		c2 = 0;
		r1 = SE_lectureCaractere(f1, &c1);
		r2 = SE_lectureCaractere(f2, &c2);
		if (c1 != c2)
		{
			SE_fermeture(f1);
			SE_fermeture(f2);
			return 0;
		}
		else if (! (r1 || r2))
			break;

	}
	if (SE_fermeture(f1))
	{
		SE_fermeture(f2);
		return -1;
	}
	if (SE_fermeture(f2))
		return -1;
	return 1;
}

void	verifAffichage()
{
	int nstdout = creat("test2.txt", 0644);
	int tmp, tmp2;

	system("echo 'This file\nis\n\nGREAT!\n' > test1.txt");
	tmp = dup(fileno(stdout));
	// Vider(entre autre) le buffer de stdout
	fflush(NULL);
	dup2(nstdout, fileno(stdout));
	affichage("test1.txt");
	// Vider(entre autre) le buffer de stdout
	fflush(NULL);
	dup2(tmp, fileno(stdout));
	close(nstdout);
	close(tmp);
	if (! system("diff test1.txt test2.txt > diff.log"))
		printf("'affichage()' test has succeeded.\n");
	else
		printf("'affichage()' test has failed.\n");
	system("rm -f diff.log test1.txt test2.txt");
}

void	verifCopie()
{
	system("echo 'This file\nis\n\nGREAT!\n' > test1.txt");
	copie("test1.txt", "test2.txt");
	if(! system("diff test1.txt test2.txt > diff.log") )
		printf("'copie()' test has succeeded.\n");
	else
		printf("'copie()' test has failed.\n");
	system("rm -f diff.log test1.txt test2.txt");
}

void	verifDeplacement()
{
	system("echo 'This file\nis\n\nGREAT!\n' > test1.txt");
	system("cat test1.txt >test2.txt");
	deplacement("test2.txt", "test3.txt");
	if(! system("test -e test2.txt") )
		printf("'deplacement() test has failed.\n");
	else if (! system("diff test1.txt test3.txt > diff.log") )
		printf("'deplacement()' test has succeeded.\n");
	else
		printf("'deplacement()' test has failed.\n");
	system("rm -f diff.log test1.txt test3.txt");
}

void verifSontIdentiques()
{
	system("echo 'This file\nis\n\nGREAT!\n' > test1.txt");
	system("echo 'This file\nis\n\nGREAT!\n' > test2.txt");
	system("echo 'This file\nis\n\nGREAT!\n\n' > test3.txt");
	system("echo 'This fil\nis\n\nGREAT!\n' > test4.txt");
	system("echo 'This file\nis\nGREAT!\n' > test5.txt");
	if (! sontIdentiques("test1.txt", "test2.txt"))
		printf("'sontIdentiques()' test#1 has failed.\n");
	else if (sontIdentiques("test1.txt", "test3.txt"))
		printf("'sontIdentiques()' test#2 has failed.\n");
	else if (sontIdentiques("test2.txt", "test4.txt"))
		printf("'sontIdentiques()' test#3 has failed.\n");
	else if (sontIdentiques("test3.txt", "test5.txt"))
		printf("'sontIdentiques()' test#4 has failed.\n");
	else
		printf("'sontIdentiques()' test has succeeded.\n");
	system("rm -f test1.txt test2.txt test3.txt test4.txt test5.txt");
}

int	main()
{
	verifAffichage();
	verifCopie();
	verifDeplacement();
	verifSontIdentiques();
	return 0;
}
