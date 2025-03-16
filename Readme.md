# TP1 — Détection et correction d’erreurs

## Partie 1 – Simulation d’un canal binaire symétrique sans mémoire (CBSSM)

#### Q1.2:

Après avoir exécuter la commande:

```bash
echo "Bonjour tout le monde" | ./cbssm 0
```
Ce qui veux dire que la probabilité d'erreur pour chaque bit vaut **0**.

Alors que après avoir modifier cette valeur de probabilité, j'ai eu comme résultat:

- Pour `p=0.001`:(On constate aucun changement la probabilité est encore petite)
```
Bonjour tout le monde
```

- Pour `p=0.005`:(On constate un changement d'un seul caractère)
```
Bonjour tout!le monde
```

- Pour `p=0.05`:(On constate un grand changement de notre chaine de caractère)
```
Cojbour`UoUt me`m+.d$
```

#### Q1.3:

Après avoir passer le fichier `data/poeme.txt` dans le **CBSSM** avec la commande suivante:(Avec p est la valeur de la probabilité)

```bash
cat data/poeme.txt | ./cbssm p
```

Après avoir modifier cette valeur de probabilité, j'ai eu comme résultat:

- Pour `p=0`:(On constate aucun changement la probabilité d'erreur est null)
```
Souvent le coeur qu’on croyait mort
Cécile Sauvage

Souvent le coeur qu’on croyait mort
N’est qu’un animal endormi ;
Un air qui souffle un peu plus fort
Va le réveiller à demi ;
Un rameau tombant de sa branche
Le fait bondir sur ses jarrets
Et, brillante, il voit sur les prés
Lui sourire la lune blanche.
```

- Pour `p=0.001`:(On constate aucun changement la probabilité est encore petite)
```
Souvent le coeqr qu’On croyait mort
Cécile Sauvage

Souvent`le coeur qu’on croyait mort
N’est qu’un animal endormi ;
Un air qui souffle Un peu plus fort
Va le réveiller à demi ;
Un rameau tombant de sa branche
Le fait bondir sur ses jarrets
Et, brillante, il voit sur les prés
Lui sourire la lune blanche.
```

- Pour `p=0.005`:(On commence à constater quelques changement mais la sortie est encore lisible)
```
Souvent le coeur qu’on croyait`mort
Céci|e Sauvage

Souvent le coeur qu∙on croyait mort
N’e�t qu’un animal endormi ;
Un air qui souffle un peu plus fort
Va le réveiller à demi ;
Un rameau tombant de sa brancHe
Le fait bondar sur ses jarrets
Et, brkllante, il voit sur les prés
Luisourire la lune b�anche.
```

- Pour `p=0.05`:(On constate un grand changement de notre sortie )
```
Souve~p"le cneur qu〙on$�roqaMt`moSv
CécIh�`Sa�~aoe�U*uveot le co�ur qu搑on croyait(m�rt
�E���t 1<∘un a>ioal(eNgOr�h ;
�l amr 1WM0{oufflu qn(`e�$pl=q fo2uVa <d 2ëv!i,�er � t�li ;*Un!sameau tombmn� da sa brsnc�e
Ne fait `ofd�r sur(sesj!rrevs
Mt
   brIlmq/te,`il t-yd sur`les ps˩sH5i �mebm2e lc lune b|a.che>
```
Donc à partir de `p=0.05`, la sortie commence à être difficilement déchiffrable.

#### Q1.4:

Après avoir passer l’archive du TP  dans le **CBSSM** avec la commande suivante:(en variant **XX** avec plusieurs valeur de probabilité d'erreur)

```
cat TP-Erreurs.zip | ./cbssm XX > TP-Erreurs-XX.zip
```

Et après avoir décompresser cette archive `TP-Erreurs-XX.zip`, avec la commande suivante:

```
unzip -d repertoire1 TP-Erreurs-XX.zip
```

On peut constater avec des petites valeurs de probabilités d'erreur `(inférieur à 0.0005)`, l'archive se décompresse avec succès avec quelques petites erreur.

Alors que à partir de `0.0005`, l'archive se décompresse avec succès mais avec beaucoup d'erreurs.

Après plusieurs essaie, je m'arrete à `0.05`, où l'archive ne se décompresse plus meme après plusieurs essaie avec la meme la valeur de probabilité d'erreurs.

#### Q1.5:

Après avoir passer l'image fournie `lille.gif`  dans le **CBSSM** avec la commande suivante:(en variant **XX** avec plusieurs valeur de probabilité d'erreur)

```
cat lille.gif | ./cbssm XX > lille-XX.gif
```

On peut constater que l'image est très sensible  aux erreurs parce que l'image est devenu inreconnaissable à partir de la valeur de probabilité `XX = 0.00005`.

#### Q1.6:

Après avoir experimenter les trois differents types de fichier `text.txt`,`archive.zip`,`image.gif` sur le **cbssm** et avec differents valeur de probabilité d'erreurs, on constate que parmi ces fichiers les  **images** sont les moins tolérants aux erreurs par rapport aux fichiers **archive** et aux fichiers **text**.

## Partie 2 – codage par répétition 3 fois

#### Q2.1:

Pour déterminer le bit majoritaire à partir de 3 bits, on va utiliser le tableau de verité et le tableau de karnaugh.

On va nommé chacun de ces bits par une lettre `A , B , C`.

**Tableau de vérité:**

En se basant sur cette image de modélisation du bit majoritaire:

![Codage par répétition](./data/codeRep.svg)


| **A** | **B** | **C** | **M(A, B, C)** |
|:-----:|:-----:|:-----:|----------------|
| 0     | 0     | 0     | 0              |
| 0     | 0     | 1     | 0              |
| 0     | 1     | 0     | 0              |
| 0     | 1     | 1     | 1              |
| 1     | 0     | 0     | 0              |
| 1     | 0     | 1     | 1              |
| 1     | 1     | 0     | 1              |
| 1     | 1     | 1     | 1              |

**Tableau de Karnaugh**

| **A/BC** | 00 | 01 | 11 | 10 |
|----------|----|----|----|----|
| 0        | 0  | 0  | 1  | 0  |
| 1        | 0  | 1  | 1  | 1  |

Après avoir établie de tableau de Karnaugh, la relation simplifié est comme suit:

**Relation mathématique**

```math
M(A,B,C)=(A∧B)∨(A∧C)∨(B∧C)
```

**Relation avec des opérateurs logiques `(ET (&), OU (|), XOR (^))`**

```
M(A,B,C)=(A&B)∣(A&C)∣(B&C)
```

#### Q2.3:
Après avoir compiler le test `test_repeat` avec la commande suivante `make test_repeat` et executer avec la commande `./test_repeat`.

Le test est passé avec succès:

```bash
ALL TESTS PASSED
Tests run: 1 (including 9 assertions)
```

#### Q2.4:
Après avoir compiler le programme avec la commande `make`.

Et en lançant la commande suivante:

```bash
echo "Bonjour tout le monde" | ./encode repeat3
```

J'ai eu comme résultat:

```bash
BBBooonnnjjjooouuurrr   tttooouuuttt   llleee   mmmooonnndddeee
```
Donc on voit bien sur la sortie que chaque octet est bien triplé.

#### Q2.5:

Après avoir tester le décodage avec la commande suivante:

```bash
echo "Bonjour tout le monde" | ./encode repeat3 | ./decode repeat3
```

J'ai eu comme résultat:

```bash
Bonjour tout le monde
```
Donc on voit bien sur la sortie que le décodage a bien fonctionné.

#### Q2.6:
Après avoir creer encoder et décoder le fichier `TP-Erreurs.zip` dans le fichier `archive.zip`, en éxecuter la commande suivante:

```bash
cat TP-Erreurs.zip | ./encode repeat3 | ./decode repeat3 > archive.zip
```
Et en comparant le premier fichier `TP-Erreurs.zip` avec le deuxième fichier `archive.zip`, avec la commande suivante: 

```bash
cmp -l TP-Erreurs.zip archive.zip 
```
On peut constater que y a aucune difference entre les deux fichiers ce qui prouve l'efficacité de la fonction `encode` et `decode`.

#### Q2.7:

La commande **cbssm** est ajoutée après l'encodage et avant le décodage comme ceci:
```bash
cat TP-Erreurs.zip | ./encode repeat3 | ./cbssm p | ./decode repeat3 > archive.zip #Avec p: la probabilité d'erreurs à faire varier entre 0 et 1.
```

#### Q2.8:

**Archive:**

Après avoir éxecuter la commande suivante en variant de manière décroissante à partir de **1** `p` la probabilité d'erreur:

```bash
cat TP-Erreurs.zip | ./encode repeat3 | ./cbssm p | ./decode repeat3 > archive.zip
```

Et en décompressant à chaque valeur de probabilité l'archive créer, avec la commande suivante:

```bash
unzip -d repertoire1 archive.zip  
```

Je n'ai réussi de décompresser cette archive que à partir de la valeur de probabilité `p = 0.04`.

**Image:**

Après avoir éxecuter la commande suivante en variant de manière décroissante à partir de **1** `p` la probabilité d'erreur:

```bash
cat data/lille.gif | ./encode repeat3 | ./cbssm p | ./decode repeat3 > data/decode.gif 
```

Je n'ai réussi de lire cette image que à partir de la valeur de probabilité `p = 0.05`.

Ce qui donner le rendu suivant:

![image](./data/decode.gif)

Mais à la probabilité d'erreurs `p = 0.001`, l'image devient complétement lisible.

![image_lisible](./data/decode_lisible.gif)

## Partie 3 – codages linéaires systématiques

#### Q3.2:
Après avoir coder la fonction `code_word`et compiler le fichier `lib/linear_coding.c`, avec la commande `make`.

Et en compilant les tests et executant le fichier de test avec la commande `./test_linear_coding `.

On perçoit l'éxecution du test avec succès:

```bash
ALL TESTS PASSED
Tests run: 1 (including 12 assertions)
```

#### Q3.3:

Après avoir lancer le programme `view_linear_coding`, le résultat du codage du mot 0110 avec le codage par parité est `0 1 1 0 0 `.

```bash
Generator matrix for parity coding [5, 4, 2]
1 0 0 0 1 
0 1 0 0 1 
0 0 1 0 1 
0 0 0 1 1 
Word
0 1 1 0 
Result of the coding
0 1 1 0 0 
```

#### Q3.5:

Après avoir compiler `make` et lancer le programme `view_linear_coding`, le résultat du codage du mot 0110 avec le codage par parité est `0 1 1 0 0 `.

```bash
--------------------------------------------------
1 0 0 0 1 0 0 0 1 0 0 0 
0 1 0 0 0 1 0 0 0 1 0 0 
0 0 1 0 0 0 1 0 0 0 1 0 
0 0 0 1 0 0 0 1 0 0 0 1 
Generator matrix for repeat coding [12, 4, 3]
1 0 0 0 1 0 0 0 1 0 0 0 
0 1 0 0 0 1 0 0 0 1 0 0 
0 0 1 0 0 0 1 0 0 0 1 0 
0 0 0 1 0 0 0 1 0 0 0 1 
Word
0 1 1 0 
Result of the coding
0 1 1 0 0 1 1 0 0 1 1 0 
```

#### Q3.7:

Après avoir réaliser le code de la fonction `transposed_control_matrix`, et lancer les tests correspondants dans `test_linear_coding`, on perçoit l'éxecution du test avec succès:

```bash
ALL TESTS PASSED
Tests run: 2 (including 42 assertions)
```
#### Q3.8:

Après avoir lancer le programme `./view_linear_coding`, on constate que les transposées des matrices de contrôle sont bien correctes.

```bash
Transposed control matrix
1 0 0 0 1 0 0 0 
0 1 0 0 0 1 0 0 
0 0 1 0 0 0 1 0 
0 0 0 1 0 0 0 1 
1 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 
0 0 0 1 0 0 0 0 
0 0 0 0 1 0 0 0 
0 0 0 0 0 1 0 0 
0 0 0 0 0 0 1 0 
0 0 0 0 0 0 0 1 
```

#### Q3.9:

Après avoir coder la fonction `syndrome` qui permet de calculer le **syndrome** d’un mot reçu, on peut constater que la fonction permet bien de calculer le **syndrome** avec succès.

```bash
Syndrome for 0 1 1 0 0 1 1 0 0 1 1 0 
0 0 0 0 0 0 0 0 
Syndrome for 1 1 1 0 0 1 1 0 0 1 1 0 
1 0 0 0 1 0 0 0 
```
#### Q3.10:

Après avoir réaliser la fonction `correct_result` qui corrige le mot fourni en paramètre, et e, compilant et lançant les tests:

```bash
1 0 1 0 1 0 
0 1 0 1 0 1 
ALL TESTS PASSED
Tests run: 3 (including 54 assertions)
```

Et après avoir lancer `./view_linear_coding`, on voir que le mot initiale a bien été corriger.

```bash
Syndrome for 0 1 1 0 0 1 1 0 0 1 1 0 
0 0 0 0 0 0 0 0 
Syndrome for 1 1 1 0 0 1 1 0 0 1 1 0 
1 0 0 0 1 0 0 0 
Corrected word: 0 1 1 0 0 1 1 0 0 1 1 0 
```
 
#### 3.11:

Après avoir réaliser la fonction `decode_word` qui décode un mot reçu et renvoie le mot en l’ayant corrigé, et en lançant les tests `./test_linear_coding`, on constate l'execution de tou les tests avec succès.
```bash
1 0 1 0 1 0 
0 1 0 1 0 1 
1 0 1 0 1 0 
0 1 0 1 0 1 
ALL TESTS PASSED
Tests run: 5 (including 83 assertions)
```

