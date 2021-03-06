# M2Mod tool #
* M2Mod tool prives way to operate with Blizzard World fo Warcraft model files (\*.M2 and \*.skin). It reinterprets them in \*.m2i files, that can be imported into [Blender](https://www.blender.org/) with [scripts](https://bitbucket.org/suncurio/blender-m2i-scripts/).
If you wish, you can produce \*.M2 from your edited \*.m2i

### Installation. ###
* Compile yourself or download latest [Release](https://bitbucket.org/suncurio/m2mod/downloads/)

### How to use. ###
* Install [Blender](https://www.blender.org/)
* Download latest [Blender m2i Scripts](https://bitbucket.org/suncurio/blender-m2i-scripts/downloads/) (click download repository) and install them into blender
* Use M2Mod to produce m2i file and import it into Blender
* Edit your model
* ....
* Export your model to m2i file
* Use M2Mod to create new m2 file based on exported m2i and base m2.
* Profit!

To use this model in game, Arctium Launcher is needed

### Misc
* Keep listfile.csv up to date: donwload Community csv from https://wow.tools/files and place into M2Mod/mappings directory
* If you you custom textures, they must be added to <your filename>.csv into 'mappings' directory. Format is same as in listfile.csv. Id should be completely random and must not overlap with blizz files

### Example configuration
![img](https://i.imgur.com/2Rm73uI.png)

### Credits ###
* Based on Fr33m4n work, which is base on Redaxle work