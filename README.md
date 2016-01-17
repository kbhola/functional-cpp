# functional-cpp

This is a library of templated classes, structs, and functions.

These are toy features I've created to replicate functional-programming concepts in C++ (e.g., map, reduce, filter).  The majority of templated functions work on std::vector, instead of arbitrary containers, because std::vector is almost always the correct container choice (because of constant access time and data locality).  While extending the templates to work on arbitrary containers would not be difficult, I believe it represents over-abstraction and is unnecessary.

