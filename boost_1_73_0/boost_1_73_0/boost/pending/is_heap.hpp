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
t1Pf81JCowEF0TTXUMlPPoNEdd+yEg/lPyLJ3JME01MH61MVkawXtFOC2bylCPNU7k65UOmMJGMknZWfyPf5JQg0tqWGzrxXn+admeTtk1nNinuhI/rAYNj2Acm+8S4Bqz8biFDYRvWIZ4XD6oQEuE091YdB8EcuJMD0i0/r2JvVJ25oMwNruW1m4+qMrjqtV3IrEH6yLkah1NFj30tUlBsliMbssANATSvR91ihINDCikHSNFwVYW9jSqvqWvP7vzB/bRCztfnYPFmWd0xaJWpacxYzaoib48vcEiv+k1e6dS0SBcRB2Sfb6z/Rj03KrmYOsgapPA0fqLu61h98lQr+IKkAM/38p8WCr8acmcLHn87ycs9yw7KVQ/XSzpqMN06gR5lz7aIRpihn4NvPIWV8tZN8tZP8H7aT4MXdHb4AVfyftpmwqeSTLSVflInEXE+N2TEwX02KsTvTlM6L6sRVMch+iMTwXN3sie5hlSxe57XkjlP635TznensDXxxlZfKNCYotWRygTQzokoik1j+RyQV6bO+dfbAgv2jwAWcGWfw7fbaX3jdb81apWqROrzflEXmyufsIB4jmYRZjWWSak3Ui1WToxtQFk2G/LVak0ILX5TN2XVlSnZVD89mZfPblCZkofXRbr+y
*/