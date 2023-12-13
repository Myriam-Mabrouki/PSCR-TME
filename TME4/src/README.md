

# Question 2

Oui. Si jamais plusieurs threads sont en concurrence et qu'une commutation arrive entre deux transferts, i vers j et k vers l, plusieurs cas sont possibles.
- j = l : Dans ce cas là, lorsqu'on crédite j, on a un mutex qui nous permet d'assurer la synchronisation entre les transferts de i et de k.
- i = k : idem pour débiter
- i != k et/ou j != l : Aucun problème ne se pose pour débiter ou créditer la même personne avec un crédit ou un débit qui pourrait être perdu.

# Question 4

On vérouille le débité et le crédité avant d'effectuer les opérations. 
On effectue les opérations.
On dévérouille le débité et le crédité.

# Question 5

La fonction transfert ayant déjà vérouillé les mutex, les autres fonctions (débiter et créditer) se bloquent. En effet, bien que ce soit le même mutex, il ne peut être pris qu'une fois. Le problème est alors corrigé grâce au recursive_mutex.

# Question 6

Le problème est le suivant : 
- dans un premier thread nous avons un débiteur d et un créditeur c
- dans un second thread nous avons notre débiteur qui est c et notre créditeur qui est d
Un interblocage peut se produire si nous avons le scénario suivant:
1) Dans le premier thread : Dans la fonction transfert nous faisons debiteur.lock() sur d 
2) Dans le second thread : Dans la fonction transfert nous faisons debiteur.lock() sur c 
Nous sommes ensuite bloquer avec crediteur.lock() dans les deux threads.
Pour régler ce problème nous devons toujours lock d avant c dans les deux threads. L'ordre de vérouillage (entre débiteur et créditeur) dans transfert dépend donc du numéro des comptes des débiteur et créditeur.


# Question 7

Un thread comptable qui tourne en concurrence avec les threads de transfert ne sera pas satisfait avec les synchronisations actuelles. En effet, lorsqu'on parcourt les comptes dans Banque il se peut qu'il y ait des transferts dans les comptes déjà parcourus. Le résultat sera alors incorrect.