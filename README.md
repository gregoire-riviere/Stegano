# Stegano
Cet outil permet de cacher un message dans une image.

### Utilisation
Pour l'utiliser, compiler le tout avec la commande `make`.
Arguments:
* **le type d'action** : f pour *find* (retrouver un message dans une image) ou h pour *hide* (pour cacher un message)
* **l'image source** : l'image dans laquelle chercher le message ou dans laquelle cacher le message (selon l'action choisie)
* **message** : message à cacher (uniquement pour action h)
* **l'image de destination** : image de sortie (uniquement pour action h)

### Exemple
Exemple d'appel :
```
./stegano h ex/lenna.bmp "Cet outil permet de stocker un message dans une image. Pratique!" ex/lenna2.bmp
```

Dans le dossier ex se trouve l'image de d'entrée et de sortie de cette commande.
