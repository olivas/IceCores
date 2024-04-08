# IceCores
A proof-of-concept project based loosely on IceCube's single-threaded framework IceTray.

## Concurrent Data Structures
IceCube uses a single data structure, called a Frame, modelled on a map<string, base_ptr> 
that's used to share data between modules.  Modules retrieve data from the Frame necessary
to perform their function and put data in the Frame that downstream modules will use.

In order to support concurrent module execution the Frame will need to be made thread-safe.

