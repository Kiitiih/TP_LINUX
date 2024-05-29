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

2.1. Accès aux registres
On travaille sur des adresses virtuelles, mais le FPGA a des adresses physiques. Si on veut écrire sur une adresse physique sur le FPGA, il faut trouver une adresse virtuelle qui va correspondre à celle la, en gros on créer un pointeur sur l'adresse physique avec la fonction mmmap. Par exemple dans le cours on a : 
p = (uint32_t*)mmap(NULL, 4, PROT_WRITE|PROT_READ, MAP_SHARED,fd, 0xFF203000);      ou NULL correspond à l'adresse ou on voudrait qu'il écrire, nous on lui dit de prendre celle qu'il veut avec le NULL. le 4 est le nombre d'octet car on est sur un système 32 bits. Le prot write/read nous permet d'écrire et de lire sur l'adresse, le map_share permet que la mémoire soit accèssible par autre chose que notre programme, le fd est le fileopen qui pointe vers la mémoire du FPGA (mem) et le FF correspond à l'adresse physique que l'ont veut pointer. 
Cette méthode permet de prototyper rapidement mais présentent deux limites :
C'est pas portable on a spécifié notre adressse en dur
Cette méthode ne permet pas de travailler sur Driver plus compliqué (avec interrupetion) car on travaille actuellement en mode utilisateur hors toutes les interruptions sont fait en mode noyau

2.2. Compilation de module noyau sur la VM
On a chargé et déchargé un module dans le noyau. 
Commande pour insérer le module : insmod
Commande pour décharger le module : rmmod

Avec la commande sudo dmesg on voit : Hello World qui s'affiche car il y a KERN_INFO dans le code de moodle
Et en déchargeant le module "Bye, Bye" s'écrit en rouge car il y a écrit KERN_ALERT dans le code


Il existe un dossier proc (fourre-tout) dans linux, on veut créer un fichier texte (virtuel) dans ce dossier. Pour se faire, on va écrire des fonctions dans notre module. En regardant dans le cours, on trouve les fonctions write, read et supression. On copie ces fonctions dans notre fichier qui contient le module. On créer une structure qui va intégrer ces fonctions struct file_operations proc_fops; et on va les appeler dans la fonction init du noyaux (proc_fops.write = fops_write; proc_fops.read = fops_read;) 

Récupéreation de la configuration actuelle du noyau
On fait des modifs (configuration du noyau) pour pouvoir compiler notre module par la suite
scp copie source vers destination
Le point (.) est un raccourci pour "ce dossier"
Les fichiers qui se terminent par .gz sont des fichiers compressés, on les dézippe avec la commande gnzip
La commande mv pour deplacer et renommer en .config (qui la fait disparaitre car il devient un ficier caché)
Les makefiles qu'on doit faire s'attend à avoir un fichier .config d'où le fait de la renommer

Le makefile fait appel au CROSS_COMPILE -gcc
C'est pour ca qu'on met un tiret à la fin du chemin car c'est le cross .gcc

2.3.3 Hello World
On creer un nouveau fichier Hello2 et on modifie notre makefile en mettant en jour le chemin du noyau

![image](https://github.com/Kiitiih/TP_LINUX/assets/144770585/8c508a15-7136-4680-bc95-59329f370a3b)

La compilation ne marche pas car on peut pas le faire dans un dossier partagé. Pour cela on créé un autre dossier où on copie et le code et le makefile et on compile de nouveau et cette foic ci la compilation marche et le module fonctionne bien avec la commande dmesg.


![image](https://github.com/Kiitiih/TP_LINUX/assets/144770585/b063b229-38dd-4464-9e74-6f2cc2c44629)

TP3 : Device tree 

 ![image](https://github.com/Kiitiih/TP_LINUX/assets/144770585/7e8857c3-55d3-4ba9-ba43-5c7a37d0b927)

On réalise les manip décrit dans le TP pour retrouver accéder à un led en modifiant le fichier dts existant
On copie un fichier dans notre répertoire de travail eton le renomme
On compile le fichier .dts en un fichier .dtb
On accède ensuite à la partition de boot dans le VEEK où on renomme notre fichier .dtb en .old et on copie notre copie notre fichier .dtb dans le PC avant de rebooter la carte
Le nouveau device tree notre montre notre fichier ensea :
