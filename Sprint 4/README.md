# se-04-team-19

This is the project of Pencil Producer for se-04-team-19. The source files are in the src folder. The program has been developed using only Qt-Creator. It can be compiled using Qt Creator or cmake and make.

## How to compile:
1. Using Qt Creator: Import the project into Qt Creator with the .pro file in src folder, and then you can build from Qt Creator.
2. Using cmake and make in Linux environment:

```
mkdir build
cd build
cmake ..
make
```

## Running:

```
./src/PencilProducer
```

## Testing(in order to be able to test `googletest` is needed):

```
./test/test
```

## Documentation:

```
make doc
google-chrome-stable html/index.html
```

## Implemented changes:
- Changed the README.md
- Fixed documentation
- Split the code into separate directories
- Made extra CMakeLists.txt that were necessary
- Made the comments more precise
- Added getters and setters
- Added a save file and load file dialog for deciding on the file name
- Added Welcome Screen with 'Start', 'Load' & 'HighScore Borad' buttons.
- Implemented Start button in a way that it leads one to the Gamepay screen.
- Implemented Load button in a way that it loads a sav. file.
- Added 'Exit' button (on the Gameplay Screen) that gets one back to the Welcome Screen.
- Editted the .gitignore file
- HTTP POST
- HTTP GET
- Fixed the wood and graphite randomizer and seller
- Added comments

## Contributors:
* **Dragi Kamov** - *Sprint 4* - [Github](https://github.com/dragikamov)
* **Ani Ambroladze** - *Sprint 4* - [Github](https://github.com/AniAmbroladze)
