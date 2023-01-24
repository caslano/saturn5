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
vK3CWufNkdYf7pE9SJQ/a5tQQsed4n/+Ic3yX7St527ppuzkYelmZf7Z8snajsfZGMZGC4v9vBrTvYvKM+f1tvkNtklCEbVHzOpLuF2xq70VVNYC6jMkVOZcz4YSvjluifRfm/5KMkexSuf4JpRIqPSxAfI8CJLWPnrTcN2ueIv9WujNnWq+/x38UMJAcW/Nb759r1lR8fEocQuDsqdQ2j6P9YzTE8dzUSwT9qup7gM920PYA4dIMMJ/0a4+VrWobBBJxRM06Nme3Rzb+Eu8+bf3a5B1z0M2uFXG++vJs1WclrhFzXEg4ZY0qiQqjAg6AAZ9CcSG0U1OyEhjSOLC0KCpYEUZ7slKmU50OPoVO7QRvB5EiyKJD5OEEoDZZDSDc56PPZPEA6BfcUNFJy/BzWBfMLkMb7DpczjRFR+UdBIkA2xYXSa5poR6TlLRW8fjDJIK0NX94YrVhsGGCMoLbpRx/kr2NeULAtsQG0YFpZnkm2wF38qcfpX6A5zmigFKB46TQaIG4MLIocSTnbJO4F0wKb03IdXOM0MsQ7StL1JoAegXqL5BTfS0NoJQd0I65j9gya6BBcH1YE96ukly8DWYV5ZKxixIKNjf0XPvlyrmwiepHa5vbYMUOnsDs47529krikYnncspTmBv3pfAsh2uVEtZnnuNxkQC6bwZp685l6H6vrKa8TXksq8kwAr+RpGESxO19d58tMVW
*/