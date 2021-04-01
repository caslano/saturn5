// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ITERATOR_TRAITS_DWA200347_HPP
# define ITERATOR_TRAITS_DWA200347_HPP

# include <boost/detail/workaround.hpp>

#include <iterator>

namespace boost {
namespace iterators {

// Macro for supporting old compilers, no longer needed but kept
// for backwards compatibility (it was documented).
#define BOOST_ITERATOR_CATEGORY iterator_category


template <class Iterator>
struct iterator_value
{
    typedef typename std::iterator_traits<Iterator>::value_type type;
};

template <class Iterator>
struct iterator_reference
{
    typedef typename std::iterator_traits<Iterator>::reference type;
};


template <class Iterator>
struct iterator_pointer
{
    typedef typename std::iterator_traits<Iterator>::pointer type;
};

template <class Iterator>
struct iterator_difference
{
    typedef typename std::iterator_traits<Iterator>::difference_type type;
};

template <class Iterator>
struct iterator_category
{
    typedef typename std::iterator_traits<Iterator>::iterator_category type;
};

} // namespace iterators

using iterators::iterator_value;
using iterators::iterator_reference;
using iterators::iterator_pointer;
using iterators::iterator_difference;
using iterators::iterator_category;

} // namespace boost

#endif // ITERATOR_TRAITS_DWA200347_HPP

/* iterator_traits.hpp
LrqirW9BvKp4GsQDk7t1EGOYbsq0aiDYxt8b7dQdoe8fTio6BLeSy01QJ5XwfyupSFKb+D0mt+TU5KdV9SlCcYZrUHMzh+XaP1n4YdURNPRGrkNjjvhp7pmmDXe5qqkrBzXPvhx1utbLWZcIKC0DD/azz2ZPoSLwJPJ2WHnu0F4BR6kW6yIy0r/FeA2ZOs0y6OLwDsWcy4a1kqBrypQM1jDtcOEmNaYIxIsYe/Q6nL4yJt5BxechlB7ciC/psz7ILabe//IwYD+4YuLb5G2bxZcN+WilDe2ifqkwKvx0tj9e61YXymyrUsUmu5/yYEklVDRrE6iowuJvTceblrq2QsQLPnvYHFqxq/i1VBCR6KsyAWZ//0FIAkBm4XAcIinZKY1mlQgArn31pqYOvDmOPEdYMy3DAxpoAN3nAl0UhS6zInHDQTKczmU4z1QICsslSZw+HBdCC96XWezeM65zrHW2at0beteYXJyU43KCQ7VKhhhjWHyUGwS9EOEgoDsSU/oar+QmUKx+YM1TJ+oQPjEVcxejWBuSsyVgNMDv9CpVzRjxE38SloGiwQ==
*/