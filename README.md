# create_raster
rendu de modele numerique de terrain

1-Necessaire pour lancer le code :

- Avoir proj aller sinon telecharger sur https://proj.org/ (minimun proj 7.2.1)
- Avoir cmake (version miimun 2.6

2- comment executer :

- construire un dossier build dans le repertoire create_raster 
- lancer le cmake etant dans le dossier build
- Puis make : l'executable s'appelle create_raster et se trouve dans le dosiier build
- Lancer l'executable passant en paramettre le chemin du fichier de donne et la largeur de l'image

3- Resumer des ligne de commandes a taper dans le terminal une fois dans le dossier create_raster

mkdir build
cd build
cmake ..
make
./create_raster ../doc/datalonglat.txt 800  


Ici le nom du fichier de donnee est datalonglat.txt et il se trouve dans dans le dossier ../create_raster/doc/

4- Les resultats :

quatre images sont generees dans le dossier ../create_raster/doc/
- MNT_ASCII.PGM : c'est le fichier PGN (noir sur blanc) ecrit en ASCII du rendu
- MNT_ASCII.PPM : c'est le fichier PPN (couleur) ecrit en ASCII du rendu
- MNT_BINAIRE.PGM : c'est le fichier PGN (noir sur blanc) ecrit en BINAIRE du rendu
- MNT_BINAIRE.PPM : c'est le fichier PPN (couleur) ecrit en BINAIRE du rendu

5- La documentations :
Pour plus d'information sur le code ouvrir le fichier HTML ../create_raster/doc/html/annotated.html
