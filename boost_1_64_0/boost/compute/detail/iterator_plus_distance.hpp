//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_PLUS_DISTANCE_HPP
#define BOOST_COMPUTE_DETAIL_ITERATOR_PLUS_DISTANCE_HPP

#include <iterator>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class Distance, class Tag>
inline Iterator iterator_plus_distance(Iterator i, Distance n, Tag)
{
    while(n--){ i++; }

    return i;
}

template<class Iterator, class Distance>
inline Iterator iterator_plus_distance(Iterator i,
                                       Distance n,
                                       std::random_access_iterator_tag)
{
    typedef typename
        std::iterator_traits<Iterator>::difference_type difference_type;

    return i + static_cast<difference_type>(n);
}

// similar to std::advance() except returns the advanced iterator and
// also works with iterators that don't define difference_type
template<class Iterator, class Distance>
inline Iterator iterator_plus_distance(Iterator i, Distance n)
{
    typedef typename std::iterator_traits<Iterator>::iterator_category tag;

    return iterator_plus_distance(i, n, tag());
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_ITERATOR_PLUS_DISTANCE_HPP

/* iterator_plus_distance.hpp
MzCssABHPxb9Llja+q3GoWmv+0dl4Zg7f13eq9p1foDIr2QMSpDTQJ9gz4TigcmyyCJbLpLp8IwTub1MT2vBYogJ6xGR39AQDHCRQfysV7/VfnOxmi0Oqkt3mG+LZ77rRxxTepgLIkzqrtJTo9lbbKLX/Eu6uDXLvk4pfRqj/mT5IGuqol/ibtNeZy/mOwSHMOqiFf8b+HDfyMvQBIMl9Glj2Hgy1TjUgCYd9/B+qekC6kJ4mDA9Zh1K4yA8EnF+COoX6cWaxU2m/exUf0p5NxRd2CeJjW8gzbjKZtsHhUZJtpxMoNd+kngbgmNIzf0tIM2AMyRTTTaKlYJIg3YoyEiIH3CWYXkzgEkV8sl6usoLRE9xeUwSV9BFQ86KCbbZj8sarta3+UtI5ZOe3GmVQQGppx2e+ICjF9eLJRo10CJp8kG56RQaj06OFFu2AlMXA22GoM1XRRgCik/o5/WiyCkg4n5BUIrg5i1jLLbLlHt9mjJ6gHE4Gt64rhcwKMnnSKaPbzVpy+D5w9hmNAKfYo6YH185BydjIuts4tBfE2WynI7ng6It3hQL1Q==
*/