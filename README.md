<snippet>
  <content><![CDATA[
# ${1:CastleGenerator}

##Pistes de développement
- Commencer par créer des murailles à angle droit 
ie. On crée un bloc (mur, porte, tour, etc...) puis pour créer le suivant 
on choisira si on le place à droite, en ligne ou à gauche dur mur précedemment créé
- La map sur laquelle on crée le mur sera donc une matrice dans un premier temps
- on peu ainsi calculer les coordonnées du bloc à placer en fonction des indices sur 
la matrice
- Cas particuliers à traiter :
	- Si on crée une tour il ne faut pas en recréer une directement après
	- Si on crée une porte il faudrait que le bloc précedent et suivant soit des tours
	- Gérer la longueur du mur : Si l'utilisateur rentre une certaine longueur pour le mur
	il ne faut pas créer un mur en ligne droite et se retrouver à court de blocs et donc
	penser à retourner au point de départ avant qu'il ne soit trop tard
  - S'assurer que la longueur du mur entrée est au moins égale à la somme des tours et 
  des portes
   
TODO: Write a project description
 
## Installation
 
TODO: Describe the installation process
 
## Usage
 
TODO: Write usage instructions
 
## Contributing
 
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D
 
## History
 
TODO: Write history
 
## Credits
 
TODO: Write credits
 
## License
 
TODO: Write license
]]></content>
  <tabTrigger>readme</tabTrigger>
</snippet>