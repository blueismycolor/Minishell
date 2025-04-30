# 🐚 MiniShell — Un interpréteur de commandes Unix simplifié

Ce projet consiste à créer un interpréteur de commande basique, **similaire à Bash**.  
Le but est de **comprendre le fonctionnement interne d’un shell Unix**, notamment :
- L’analyse de commande
- La gestion des processus
- Les redirections
- Les signaux
- Les variables d'environnement

---

## 🎯 Objectifs principaux

✅ Afficher un **prompt** et lire les commandes de l’utilisateur  
✅ Gérer **l’historique des commandes**  
✅ Analyser et exécuter des **commandes simples et composées** (avec `|`)  
✅ Gérer les **variables d’environnement** et l’expansion de `$`, y compris `$?`  
✅ Implémenter les **redirections** : `<`, `>`, `>>`, `<<`  
✅ Gérer les **signaux** : `Ctrl-C`, `Ctrl-D`, `Ctrl-\`  
✅ Implémenter les **builtins** suivants :
- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

---

## 🔧 Exemples d'utilisation

### 1️⃣ Commande simple
```bash
$ ls -l
```
➡️ Le shell exécute la commande `ls` avec l’option `-l`.

---

### 2️⃣ Pipes
```bash
$ cat file.txt | grep "hello" | wc -l
```
➡️ Les commandes sont chaînées :
- `cat file.txt` → lit le fichier
- `grep "hello"` → filtre les lignes contenant "hello"
- `wc -l` → compte les lignes

---

### 3️⃣ Redirections
```bash
$ echo "bonjour" > salut.txt      # Écrit "bonjour" dans le fichier (écrase)
$ cat < salut.txt                 # Lit depuis le fichier
$ echo "ligne" >> log.txt         # Ajoute "ligne" à la fin du fichier
```

---

### 4️⃣ Here-Doc (`<<`)
```bash
$ cat << FIN
Bonjour
Au revoir
FIN
```
➡️ Transmet le bloc multi-lignes à `cat` jusqu’au mot-clé `FIN`

---

### 5️⃣ Expansion des variables
```bash
$ echo $HOME       # Affiche le chemin vers le répertoire personnel
$ echo $?          # Affiche le code de retour de la dernière commande
```

---

### 6️⃣ ' et "
```bash
$ echo "Salut $USER"   # Affiche le contenu de la variable $USER
$ echo '$USER'         # Affiche littéralement $USER
```

---

### 7️⃣ Builtins
```bash
$ cd /tmp
$ pwd
/tmp
$ export VAR=42
$ echo $VAR
42
$ unset VAR
$ env
```

---

## 📦 Compilation

Utiliser un Makefile pour compiler :
```bash
make
```

---

## 📚 Ressources utiles

- `man bash`, `readline`, `fork`, `execve`, `dup2`, `pipe`, `waitpid`
- [Learn Git Branching (visualiser Git en ligne)](https://learngitbranching.js.org/)
- [Correction PDF](https://github.com/rizky/42-corrections/blob/master/minishell.pdf)

---

## 🚀 Auteurs
[aeudes](https://profile.intra.42.fr/users/aeudes), [egatien](https://profile.intra.42.fr/users/egatien), [mgodefro](https://profile.intra.42.fr/users/mgodefro) & [tlair](https://profile.intra.42.fr/users/tlair)

Réalisé dans le cadre du projet Minishell de 42, destiné à l’apprentissage du fonctionnement d’un shell Unix minimal.
