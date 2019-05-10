# My Pencil Universe

 You are now in charge of creating a system that would efficiently produce and sell pencils, with the ultimate goal of making sure everyone on the planet (or the galaxy) has enough pencils forever.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.
### Prerequisites

What things you need to install the software and how to install them:

- GNU C++: https://gcc.gnu.org/install/
- Qt: https://www.qt.io/download
- NetBeans: https://netbeans.org/downloads/8.2/ (be sure to use version 8.x as version 9 and upwards no longer support C++)
- CMake: https://cmake.org/install
- Doxygen: https://sourceforge.net/projects/doxygen/
- CURL (for Ubunut/Debian): https://askubuntu.com/questions/78183/installing-curl-h-library
- JSON (for Ubuntu/Debian): ``` sudo apt install libjson-c-dev libjsoncpp-dev ```

### Installing

A step by step series of examples that tell you how to get a development env running

Place the follwoing step into terminal to build the project.

```
mkdir build && cd build && cmake ..
```

You can now make the project

```
make
./src/PencilProducer
```

You can also run the unit tests:

```
make 
./test/runTests
```

to make docs run:

```
make doc
google-chrome-stable doc/html/index.html
```

To check the test coverage run the following lines after you have ran the tests at least once:

```
cd test/CMakeFiles/runTests.dir
lcov -c -d . -o coverage.info
genhtml coverage.info
google-chrome-stable index.html
```

## Built With

* [QT5](qt.io) - The GUI framework used
* [Cmake](https://cmake.org) - Dependency Management
* [Doxygen](http://www.doxygen.nl) - Used to generate docs
* [Google tests](https://github.com/google/googletest) - Used to generate unit tests


## Contributors

* **Gandbold Adilbishf** - *Sprint 1* - [Github](https://github.com/GanboldAdilbish)

* **D.Huynh** - *Sprint 1* - [Github](https://github.com/dung-huynh )

* **Brian Sherif** - *Sprint 2* - [Github](https://github.com/BrianSherif)

* **Ezana Geressu** - *Sprint 2* - [Github](https://github.com/ezanageressu)

* **Sanan bin Tahir** - *Sprint 3* - 

* **Rohit Paudel** - *Sprint 3* - 

* **Dushan Terzikj** - *Sprint 4* - [Github](https://github.com/terz99)

* **Mukhammad Shokarimov** - *Sprint 4* [Github](https://github.com/mshokarimo)

* **Dragi Kamov** - *Sprint 5* [Github](https://github.com/dragikamov)

* **Amine Ighiri** - *Sprint 5* [Github](https://github.com/toysoldieram)

## Acknowledgments

* Software engineering Teaching Assistants
* Inspiration for Cmake of sprint 1 from Secure and Dependable Systems 
* QdarkStyleSheet - [Github](https://github.com/ColinDuquesnoy/QDarkStyleSheet)

## Improvements in Sprint 1

Unknown

## Improvements in Sprint 2

Unknown

## Improvements in Sprint 3

* Some printing bugs fixed, there were labels overlapping
* Wallet and Inventory classes added
* Random number generation of prices of graphite and wood were not working as expected, replaced with new function which works as intended
* Full functioning API, documented and tested.
* Loading of the APM machine amount has been fixed.
* Improved the marketing and upgradeAPM buttons.

## Improvements in Sprint 4

Unknown

## Improvements in Sprint 5

* Code split into new directories
* New .gitignore
* Fixed getting of environmental variables
* Fixing commenting (there were almost no comments)
* Minor changes to the UI
* Fixed the project file
* Asking for a save file name
* Game Over screen
* Fixing indentation
* More changes to the UI
* Removed welcome class and interface and remade it
* Fixed save button
* Fixed load button
* Added error messages
* Uploading score fixed
* Wrote the report
* Testing