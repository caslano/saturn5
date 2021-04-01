//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#if __KCC
namespace std
{

template < class RandomAccessIterator, class Distance >
bool __is_heap(RandomAccessIterator first, RandomAccessIterator last, Distance*)
{
    const Distance n = last - first;

    Distance parent = 0;
    for (Distance child = 1; child < n; ++child)
    {
        if (first[parent] < first[child])
            return false;
        if ((child & 1) == 0)
            ++parent;
    }
    return true;
}

template < class RandomAccessIterator >
inline bool is_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    return __is_heap(first, last, distance_type(first));
}

template < class RandomAccessIterator, class Distance,
    class StrictWeakOrdering >
bool __is_heap(RandomAccessIterator first, RandomAccessIterator last,
    StrictWeakOrdering comp, Distance*)
{
    const Distance n = last - first;

    Distance parent = 0;
    for (Distance child = 1; child < n; ++child)
    {
        if (comp(first[parent], first[child]))
            return false;
        if ((child & 1) == 0)
            ++parent;
    }
    return true;
}

template < class RandomAccessIterator, class StrictWeakOrdering >
inline bool is_heap(RandomAccessIterator first, RandomAccessIterator last,
    StrictWeakOrdering comp)
{
    return __is_heap(first, last, comp, distance_type(first));
}

}
#endif

/* is_heap.hpp
qc7z53go/4FOpzTHSnuIqKh26uK0QtkZvGnkKrPVd3oXBtEUokVQ1URFndZc6f/ApORsMZoGBPCK9ydZ1/H1dqkUA7gPaXvkVWnkXLlOhWNL5kFTTlcqgALPOYIdGPmxpkSsS/fai6QXdCg6QqBkyqasQ5+93kVzzSnkdp6kwc7L/3k6KBqnGCoZF58RwncOhBGmMbXkrcp6UfzVmd4AFCfRUNKDflk6CODMWtgyx2d/TrV5tTBJIDaHyCD2vZvR9iwwaxk8q9NQ1tCXlLW3TwFUZddfOzSWWoCw0GsuqpcFBN0zu3UqVG7jBDKVH9BP4r9HDa/7JLuWX9tqbGQstfIivfnF9I9ekUJLUvhSrAFbPZZeREbjgMyYB2F6Cj9jp8vxwucH9XKyHkMd20KZvZWsUD648JuvncXBxA7R65MVHcps20uwZlsTYc0RDNAAj7f8mUsGm3dKZZvazXnbzABMaZtESVj9UzQg8hhDi1/kW0Ylfb6xCtLJxAlDBjyLSGLmu3lx0pGy3Bcie8WFwQuqflmcvmqBwQqaoY2DUQmYpydps7XqEGlDHQ==
*/