# Pencil Revolution

## To run it:

``` 
mkdir build
cd build
cmake ..
make
./pencils
```

## To test:

```
./test/test-pencils
```

## To generate documentation:

```
make doc
cd ../doc/html
google-chrome-stable index.html
```

## Implemented changes:
- fixed the selling function (it wasn't selling until it had a certain number of pencils in inventory)
- fixed documentation generation
- fixed README
- fixed testing
- refactoring: split out internal models, add rendering functions to sync the UIs
- implementation: add load/save functionality, add entry to the references.txt
- implementation: add second currency
- implementation: add upgrading the APM
- implementation: add marketing tool
- implementation: add debugging tool
- implementation: add testing for the changes in save/load, apm

## Contributors:
* **Dragi Kamov** - *Sprint 3* - [Github](https://github.com/dragikamov)
* **Yiping Deng** - *Sprint 3* - [Github](https://github.com/DengYiping)
