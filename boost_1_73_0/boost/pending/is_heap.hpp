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
09X1DdTmZd8RqedjfBgX+46PoI1suTQ2e2DbsPjwTQuMfxTEb+Lx2X/RJ0yzyfs4ylgFMuo9eX8s8J567ya8B/semuuS8Wq8m51+c66ex5V5vyXi2ik87mcwrgij99DwsHw7z6ucq4vVB+f1805eoyF5vQ3jhbzn92Z0nYG/WGe+xJ5FX3Z8kdsjwWl8JTjfVM/C0y/mTPrFnE3/6yz9bzjpfzMk/W9h+mshXkNAXYmF1pkG
*/