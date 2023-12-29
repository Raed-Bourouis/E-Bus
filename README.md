# E-Bus
Dans ce Readme je viens d'expliquer la structure mon projet.
J'ai commencé par créer 3 structures qui vont representer chacune un utilisateur (voy) un bus (bus) et une réservation (res).
En suite, j'ai créer 3 types des listes chainées, chacune aura pour valeur une instance de l'une des structure mentionnée ci-dessus. (boys pour voy, buss pour bus et ress pour res). Puis, j'ai crée 3 variables: accounts instance de voys, fleet instance de buss, #orders instance de ress.
Ces listes sont cruciales car il seront l'objet de tout traitement dans n'importe quelle fonction ou procedure.

avant de lister les fonctionnalitées de program, j'expliquera briévement le mode de stockage des données à long terme. j'ai simuler une base des données en employant 3 fichier binaires qui seront rempli par les données de l'une des listes chainées:
  -fleet.bin est le fichier responsable de la listes des bus
