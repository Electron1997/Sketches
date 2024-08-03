\mainpage Volume Sketching Library Documentation

# What this library provides

This header-only template library provides C++ implementations of the following volume sketching techniques:

* Count Sketch (C_sketch)
* Count-Min Sketch (CM_sketch)
* Count-Bayesian Sketch (CB_sketch)
* Cardinality-Count-Average Sketch (CCA_sketch)
* Cardinality-Count-Bayesian Sketch (CCB_sketch)


# How to use this library

To use this library it is sufficient to include the library folder, or even just the desired files, in the project. Alternatively, it is possible to place the library folder anywhere (e.g. in /usr/local/include/ on a Linux system) and compile with e.g. -I /usr/local/include/ TODO: make this more general.

# Note on parallelism

This library does not provide any thread safety. By design, this library expects exactly one thread operating on each sketch. One approach to leverage multiple threads anyway is to employ one separate sketch per thread. To obtain a total volume estimete it is then sufficient to aggregate the query results computed by each thread.