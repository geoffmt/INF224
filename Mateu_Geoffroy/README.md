#Rendu TP INF224

##Etape 1

/

## Etape 2

/

## Etape 3

/

## Etape 4

> Comme pour la fonction d'affichage, la fonction pour jouer l'objet ne modifie pas l'objet et elle doit être déclarée dans les classes **Photo** et **Video** et dans la **classe de base** afin de permettre un appel polymorphique sur la hiérarchie de classes. Cependant, contrairement à la fonction d'affichage, elle ne peut pas avoir d'implementation au niveau de la classe de base (car a priori chaque type d'objet nécessite un utilitaire différent pour être joué). Comment appelle-t'on ce type de méthode et comment faut-il les déclarer ?

Cette méthode est une méthode abstraite qu'il faut déclarer avec ```virtual``` et valant 0. 
```virtual void playMedia() const = 0;```



> Modifier le *Makefile* si nécessaire (on rappelle qu'il ne faut pas mettre les .h dans *SOURCES*). Compiler, corriger les éventuelles erreurs et tester le programme. Si vous avez fait correctement ce qui précède, il ne sera plus possible d'instancer des objets de la classe de base. Pourquoi ?

On ne peut alors plus instancier d'objets de classe ```Multimedia``` de base car la classe est abstraite.
Sa méthode ```playMedia()``` n'est pas définie.



## Etape 5

> Quelle est la propriété caractéristique de l'**orienté objet** qui permet de faire cela ? Qu'est-il spécifiquement **nécessaire de faire dans le cas du C++** ? Quel est le type des éléments du tableau : est-ce que ce tableau contient les objets ou des **pointeurs** vers ces objets ? Pourquoi ? Comparer à Java.

La propriété caractéristique est le polymorphisme. Les objets ```Video```et ```Picture```dérivent de la classe de  base. 

C'est un tableau de pointeurs vers des ```Multimedia```. Il contient donc des pointeurs. Cela est utile car tous les objets n'ont pas la même taille, il est donc nécessaire de stocker des pointeurs. Ce procédé est identique en Java. 



## Etape 6

> Que faut-il faire pour que l'objet Film ait **plein contrôle sur ses données** et que son tableau de durées des chapitres ne puisse pas être modifié (ou pire, détruit) à son insu ? (c'est l'objet qui doit pouvoir modifier ce qui lui appartient, pas les autres !)
>
> **Attention**, le même problème se pose si un accesseur **retourne directement ce tableau sans prendre les précautions nécessaires** : la encore le contenu du tableau n'est pas récopié et l'appelant peut le modifier à sa guise. Quelle est la solution très simple que propose C/C++ pour éviter ce problème ?

En recopiant le tableau à l'instanciation de l'objet, on s'assure que seul cet objet y a accès. On peut procéder de la même manière pour les accesseurs. 

On peut par exemple aussi renvoyer un pointeur qui pointe vers le tableau. 



## Etape 7

> Contrairement à Java ou C#, C/C++ ne gère pas la *mémoire dynamique* automatiquement : comme il n'y a pas de ramasse miettes, tout ce qui a été créé avec *new* doit être détruit avec *delete* sinon on aura des fuites mémoires. Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait **pas de fuite mémoire** quand on détruit leurs instances ?
>
> De même, la **copie d'objets** peut poser problème dans certains cas. Pourquoi et que faudrait-il faire ?

La classe ```Film``` crée un tableau dynamiquement dans son constructeur. Elle doit
donc le delete dans son destructeur.
Si un objet à des pointeurs vers d'autres objets et que l'on copie ce pointeur alors il se peut qu'on ait des problèmes de mémoire. 



## Etape 8

> Le groupe ne doit pas détruire les objets quand il est détruit car un objet peut appartenir à plusieurs groupes (on verra ce point à la question suivante). On rappelle aussi que la liste d'objets doit en fait être une liste de **pointeurs** d'objets. Pourquoi ? Comparer à Java.

On utilise des pointeurs d'objets car les pointeurs font tous la même taille et peuvent pointer vers des objets de tailles différentes (cf. Etape 5). Identique en Java.



## Etape 9

/

## Etape 10

/

## Etape 11

> Votre méthode *processRequest()* devra pouvoir accéder aux données de la classe créée à la question précédente. Sachant que cette méthode peut appartenir à n'importe quelle classe, quelle est la solution la plus simple ?

En déclarant la méthode ```processRequest()``` comme méthode de la classe précédente, elle a
accès à tous ses attributs.



Méthodes implémentées :
```search ([media_name])``` : Affiche les attributs d'un ```Multimedia```.
```search ([group_name)]``` : Affiche les attributs d'un ```Group```.
```play ([media_name])```: Joue un ```Multimedia ```avec l'outil adapté. 

