# create_raster
rendu de modele numerique de terrain

1-Necessaire pour lancer le code :

	- Avoir proj, aller sinon telecharger sur https://proj.org/ (minimun proj 7.2.1)
	- Avoir cmake (version miimun 2.6)

2- comment exécuter :

	- construire un dossier build dans le répertoire create_raster 
	- lancer le cmake étant dans le dossier build
	- Puis make : l'exécutable s'appelle create_raster et se trouve dans le dosiier build
	- Lancer l'exécutable passant en paramettre le chemin du fichier de données et la largeur de l'image
		NB: pour ne pas avoir des problèmes suite au chemin du fichier, il est conseillé de deposer votre fichier de données dans l'un des dossiers du répertoire create_raster. Moi je choisis généralement de le deposer dans le dosier ../create_raster/doc/

3- Résumer des lignes de commandes à taper dans le terminal une fois dans le dossier create_raster (on suppose que votre fichier de donées s'appelle datalonglat.txt et qu'il est dans le dosier ../create_raster/doc et que vous voulez une largeur de 800)

	mkdir build
	cd build
	cmake ..
	make
	./create_raster ../doc/datalonglat.txt 800


	!!!!Attention!!!! Ici le nom du fichier de données est datalonglat.txt et il se trouve dans dans le dossier ../create_raster/doc/

4- Les resultats :

	quatre images sont générées dans le dossier ../create_raster/doc/
		- MNT_ASCII.PGM : c'est le fichier PGN (noir sur blanc) ecrit en ASCII du rendu
		- MNT_ASCII.PPM : c'est le fichier PPN (couleur) ecrit en ASCII du rendu
		- MNT_BINAIRE.PGM : c'est le fichier PGN (noir sur blanc) ecrit en BINAIRE du rendu
		- MNT_BINAIRE.PPM : c'est le fichier PPN (couleur) ecrit en BINAIRE du rendu

5- La documentation :
	Pour plus d'information sur le code exécuter le fichier ../create_raster/doc/Doxyfile
	Pour celà dans un terminal ouvert dans la racine de ../create_raster/doc/ taper 
		doxygen Doxyfile
	un dossier html est créé. entrer dans ce dossier et double cliquer sur le fichier ../create_raster/doc/annoteted.html 
	une page web s'ouvre avec l'ensemble des commentaires du programme.
