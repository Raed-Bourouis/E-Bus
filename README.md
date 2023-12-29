# E-Bus
Dans ce Readme je viens d'expliquer la structure mon projet.

J'ai commencé par créer 3 structures qui vont representer chacune un utilisateur (voy) un bus (bus) et une réservation (res).

En suite, j'ai créer 3 types des listes chainées, chacune aura pour valeur une instance de l'une des structure mentionnée ci-dessus. (boys pour voy, buss pour bus et ress pour res). Puis, j'ai crée 3 variables: accounts instance de voys, fleet instance de buss, orders instance de ress.

Ces listes sont cruciales car il seront l'objet de tout traitement dans n'importe quelle fonction ou procedure.


avant de lister les fonctionnalitées de program, j'expliquera briévement le mode de stockage des données à long terme. j'ai simuler une base des données en employant 3 fichier binaires qui seront rempli par les données de l'une des listes chainées:

  - fleet.bin est le fichier responsable de la listes fleet
  
  - orders.bin est le fichier responsable de la liste orders
  
  - voyageurs.bin est le fichier responsable de la liste accounts

A l'éxecution de program, les procédures read_voys(), read_fleet(), read_orders() lisent les données des fichiers et les ajoutent à leurs listes chainées respectives. Puis à la fermeture, aprés que tous les traitements sont fait, les procédures write_voys(), write_fleet(), write_orders() font l'inverse.


à fin d'assurer la bonne fonctionnement de cette base, je vous prie de mettre tout les fichier de ce repertoire dans un meme directoire sur votre pc lors de l'execution.

Quand à la fonctionnalité de ce program:

  - Creer un nouveau compte

  - Creer une nouvelle reservation

  - Voir la flotte des bus
    
  - Voir tous les reservations, ce qui offre la possibilité de modifier l'une d'eux

  - faire des modification en tant que admin du logiciel. Pour acceder au mode admin il faut saisir l'identifiant d'admin que j'ai initialisé a 123456789 pour raison de simplicité. Les modifications possibles consistent de voir tous les utilisateurs, effacer tous les utilisateur, effacer tous les reservation, ainsi qu'ajouter un bus a la flotte. 

