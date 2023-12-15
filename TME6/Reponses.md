# Question 4

D'après https://man.cx/nanosleep, la fonction nanosleep retourne si le processus s'est bien endormi le temps passé en argument. Si elle renvoie autre chose, c'est que le processus a été interrompu par un signal. Ainsi, on réalise une boucle afin de continuer à s'endormir le temps restant après l'interruption du signal.

# Question 5 

Afin d'être sûre que les deux combats utilisent une graine aléatoire, les processus père et fils lancent tous les deux leurs combats. Ainsi, chaque processus fait un appel defense() qui fait un appel à randsleep() (et donc la graine r est différente).