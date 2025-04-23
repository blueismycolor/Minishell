Ce projet consiste à créer un interpréteur de commande basique, similaire à Bash.
Le but est de comprendre le fonctionnement interne d'un shell Unix, notamment l'analyse de commande,
la gestion des processus, des redirections et des signaux.

OBJECTIFS PRINCIPAUX :

Afficher un prompt et lire les commandes de l'utilisateur.

--> Gérer l'historique des commandes.

--> Analyser et exécuter des commandes simples et composées (avec pipes).

--> Gérer les variables d'environnement et l'expansion de $, y compris $?.

--> Implémenter les redirections : <, >, >>, <<.

--> Gérer les signaux : Ctrl-C, Ctrl-D, Ctrl-\ comme dans Bash.

--> Implémenter les commandes internes suivantes :
    echo, cd, pwd, export, unset, env, exit.

EXEMPLES : 
1) Commande simple :
$ ls -l --------> Le shell exécute la commande ls avec l’option -l.
/-------------------------------------------------------------------------------/

3) Pipes :
$ cat file.txt | grep "hello" | wc -l ------> ici les commandes sont chaînées.
  - cat file.txt -> lit le fichier
  - grep "hello" -> filtre les lignes contenant "hello"
  - wc -l -> compte les lignes.
chaque commande est un maillon de la chaîne, séparé par |

/-----------------------------------------------------------------------------/

3) Redirections :
$ echo "bonjour" > salut.txt ------> Crée (ou écrase) un fichier salut.txt avec le contenu "bonjour".
$ cat < salut.txt ----------------->  Redirige l’entrée standard depuis un fichier.
$ echo "ligne" >> log.txt ---------> Ajoute "ligne" à la fin du fichier log.txt.

/-----------------------------------------------------------------------------/

5) Here-doc (<<)
$ cat << FIN
Bonjour
Au revoir
FIN
-------> prend tout ce qui est écrit jusqu'à FIN et le passe en entrée à cat.

/-----------------------------------------------------------------------------/

7) Expansion des variables
$ echo $HOME -------------> affiche le chemin du répertoire personnel.
$ echo $?-----------------> affiche le code de sortie de la dernière commande exécutée.

/------------------------------------------------------------------------------/

9) Citations et métacaractères
$ echo "Salut $USER" ------> Expande $USER dans la chaîne.
$ echo '$USER' ------------> Affiche littéralement $USER (pas d’expansion à cause des simples quotes).

/------------------------------------------------------------------------------/

7) Commandes internes (builtins)
$ cd /tmp
$ pwd
/tmp
$ export VAR=42
$ echo $VAR
42
$ unset VAR
$ env

/--------------------------------------------------------------------------------/
