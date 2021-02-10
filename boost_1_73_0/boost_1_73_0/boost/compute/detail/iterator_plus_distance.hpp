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
gAxVOFfizKU/xhoHMqAncFq6jr4YZa7VNgoqP3g5KonzdYGQZL7eWi1CTxkfEhNXNI5GeNBGBnTZtn17awDSHYw0RHDDI7DU/1GVH3HRexqwjKEdoMvU0j4RQZ6HWkvwnTVzTOtMydmsLR/PLX7iKGqJigoWm0ofLTZH/AnEZtleS5+f9c/D2eVnWRWJa3XLk7Q7GEmeWzurprvsMK6Ld9MJssC62V9VzciS6KWq08ovfE0X0+k46tEIZpemyWdbp+9m/SjydiHxAc7ZHDDQzSJnRikfdre9HT/KE1MFIKWKu0DnBoUPxu64lxLNKvHwHr2QxyUhKZyIt/S5M6xglgj4FpRgquP7tl4cJWg/qDtp8GhEEGrpbHA67dL5FAQ1uArx//KM/49H42dctNHVdOxiLMq9IQ0SmfxQ30x994ZPFCAOE99aiXePTvNsmZoYuWk6RdDGfB8NXG4+6s7jCmHk/o/zGsb+WP+/ZAxH83A2vRhNBtPrNhlcJCCjGoEuTQVGXGkY5mYNnkU9mewcDp1v8s4j53cgbK6E1J31Mp5luXFLXDNcAOI4YOZN9TVs2ahE51kgxx4LgR+BbjMgAo1Y2oW0f55z5K0L8xWf8GJMMpgCvD09igpMOstNQyJMs4HbYUmvCzi3ddNq
*/