## se-01-team-12
# Pencils

Welcome to the Pencil Producer! You are now in charge of creating a system that
would efficiently produce and sell pencils, with the ultimate goal of making sure
everyone on the planet (or the galaxy) has enough pencils forever.

## The following packages are required

```
• GNU C++: https://gcc.gnu.org/install/
• Qt: https://www.qt.io/download
• NetBeans: https://netbeans.org/downloads/8.2/ (be sure to use version 8.x as
version 9 and upwards no longer support C++)
• CMake: https://cmake.org/install
• Doxygen: https://sourceforge.net/projects/doxygen/
```

## Guidelines to install

```
git clone https://github.com/matiusulung/se-01-team-12.git
cd se-01-team-12
mkdir build
cd build
cmake ..
make
./Pencils
```

If there is an error that some of the libraries weren't found then just do: 
```
export CMAKE_PREFIX_PATH={YOUR_QT_INSTALLATION_FOLDER}
```
where instead of `{YOUR_QT_INSTALLATION_FOLDER}` you would need to put the 
installation folder of your Qt libraries, for me that is: 
```
~/Qt/5.13.0/gcc_64/lib/cmake
```
And then we can continue with:
```
cmake ..
make
./Pencils
```

## Documentation

Assuming that you compiled the program already, in order to 
make the documentation you would have to be in the created directory 
`build` and you would type in your terminal:
```
make doc
```
then a folder called `doc` will appear and to see the documentation 
you would have to open `doc/html/index.html` in your browser.

## Made by:
Sprint 1 - [**Dragi Kamov**](https://github.com/dragikamov) and [**Ananta Raj Bhattarai**](https://github.com/anantarb)

