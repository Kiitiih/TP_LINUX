# TP_LINUX

Nous avons commencer par flasher la carte SD puis nous l'avons sur la carte
En parallèle noous avons télécharger le fichier de TP sur moodle et le logiciel VirtualBox qu'on utilisera plus tard

1.3 Connexion au système
A l'aide du logiciel TerraTerm nous configurons la liaison série entre notre PC et la SoC
Après nous être connecté au SoC sur la liaison série, nous avons réaliser la configuration réseau

1.4 Découverte de la cible
On lance la machine virtel VM Virtual Box et commencons à explorer les dossiers

Quelques commandes :
Pwd donne le chemin ou on se situe 
Cd .. ramène au dossier racine juste au dessus de celui dans lequel on se trouve 
Cd ~ ramène sur le home 
Cd. on n'a l'impression qu'il ne fait rien mais il te remet dans le dossier actuel
ioports vide sur la SoC parce qu'on est sur une architecture ARM, par contre on a des choses sur celui de VM car on a une architecture de PC.

Après avoir créer l'executable on veut le mettre sur la carte, on utilise la ligne suivante : scp chemin_sur_VM root@IP_DE_LA_CARTE_SOC:chemin_sur_SOC
Chemin sur VM est l'endroit ou on est, chemin sur soc on peut écrire juste les : après l'adresse et ca mettera l'executable dans le home
Ensuite dans Tera term on fait ./ le nom du fichier (./ = éxecuter)

C'est pas portable on a spécifié notre adressse en dur
Cette méthode ne permet pas de travailler sur Driver plus compliqué (avec interrupetion) car on travaille actuellement en mode utilisateur hors toutes les interruptions sont fait en mode noyau
