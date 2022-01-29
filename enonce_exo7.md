## résolution equation de la chaleure (diffusion de la chaleur , equation de Laplace) par la méthode des différences finies 
une surface MxN sur laquelle on applique des températures de départ (stables) uniquement sur les bords (haut, bas, gauche droite) et 
grace à l'équation de diffusion de la chaleur on essaie de deviner la température qu'il fera à tous les points de la surface de la 
plaque. Pour cela il suffit de résoudre l'équation de Laplace. Cet algorithme permet de trouver les solutions à cette équatin 
en discrétisant l'espace un maillage est réalisé (découpage de la surface globale en plusieurs petits morceaux et on essaie de trouver 
la température aux points d'intersection en utilisant la méthode des différences finies).
il s'aggit ici de paralléliser cet algorithme avec MPI en considérant les cas suivants:
    1-Le nombre de lignes de la matrice est égal au nombre de processus (petite taille)
    2-Le nombre de processus <<< taille de la matrice et dans ce cas chaque processus sera en charge de calculer 
plusieurs lignes de la matrice. 
NB. il y a 3 boucles (boucle while des itérations, deux boucles for pur le parcours de la matrice), ici il n'est possible 
de paralléliser que les deux boucles for (ou une seule d'elles) la boucle externe contient des dépendances de données il faut 
terminer avec l'itération i avant de passer à l'itération i+1 donc pas possible de la paralléliser. 

Autre remarque, pour calculer une ligne i, le processus a besoin de la ligne en question à l'itération précédante, et des deux lignes 
adjacentes i+1 et i-1. Donc en cas de découpage en lignes il faut lui envoyer sa ligne et deux autres ligens adjacentes. 
On peut découper aussi par colonne ou alors par petites matrices, mais le découpage par ligne c'est le plus simple et
 celui qui limite aussi les dépendances. 

3-réaliser une comparaison entre la version séquentielle et la version parallèle avec MPI et calculer le speed up et efficacité. 