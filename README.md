# IceCores
A proof-of-concept project based loosely on IceCube's single-threaded framework IceTray.  
The execution model forms a DAG, where a single DAG represents an HPC job or task. 

![alt text](https://github.com/olivas/IceCores/blob/main/resources/images/fear_the_turtle.png?raw=true)

This framework supports any DAG topology.  The image above is for illustration purposes, and
intended to represent a turtle to pay tribute to the University of Maryland at College Park 
where this project was initially developed.

## Getting Started
### Dependencies
The only dependencies are modern C++, cmake, and boost.  Prefer a modern standard like 17 or 20.  
Modern development will assume C++20. 

```shell
cd IceCores
mkdir build
cd build
cmake ..
make
make test
```

## Concurrent Data Structures
IceCube uses a single data structure, called a Frame, modelled on a map<string, base_ptr> 
that's used to share data between modules.  Modules retrieve data from the Frame necessary
to perform their function and put data in the Frame that downstream modules will use.

In order to support concurrent module execution the Frame will need to be made thread-safe.

