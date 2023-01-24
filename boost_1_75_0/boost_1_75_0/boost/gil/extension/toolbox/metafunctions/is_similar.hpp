//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP

#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_similar metafunctions
/// \brief Determines if two pixel types are similar.

template<typename A, typename B>
struct is_similar : std::false_type {};

template<typename A>
struct is_similar<A, A> : std::true_type {};

template<typename B,int I, int S, bool M, int I2>
struct is_similar
    <
        packed_channel_reference<B,  I, S, M>,
        packed_channel_reference<B, I2, S, M>
    > : std::true_type {};

}} // namespace boost::gil

#endif

/* is_similar.hpp
4B37uYYvLdi6iY0Ew9+WPcegz8bz5RoJRK1+W72ny0qNTbb0pbcw+BD6Puryzz2gJGs77R2334yZbxb6mCWSYpS+STSSqJNogZ7gLekGdVWMc3WpWEons49VSARncYsV3v9j/OMjY99Ps3sDH4c/2qWzaunnDgRtmJUcYZRao35mg3vz1Zk4ge7eM+u11HW/xGWTpYwQQMfb9qKuc15MgG+Oj/VStaIRHZeoBgBUam12IjbqRO4pZM7blsndXHWyno/2hwJqsCelqUq+Z0JHTY3YdQFCsBowf0BqzvXvuuIEZ5cUcNvwNlyw+pfwUfRQQDGTjxOmtqw2LWApT1mgdB2ArNGIbGe0V+IDj4tg5ilvc/ZsESpPcxddRA+zlUfI5EIvbxQsIbGYnesdYmmn5an7LJqOn0azPsGnHsBKT/3En5ROA/ZdxCtQGtL4MfUaSCFDpFEFirfCO+1DtWd93223ie5eANz9ef9eZ+eP6elZ49FrnmXhq2XprryYh5qGyCXsXZVc187XsJ7WOqGMxgaD4f5x3r7sJh2/fSsWjQvVSCpyNDqKWZTrlhfxQJhMssmXlkuoiXZf+teB6q2f7p+wc0hb8/Ezu0ee25daoYppApfCrjMlBM7hrTph0brdrS0tFbd1jT0zBOWfhAlnp1LaDtxN/duGHvxw/Pn+z9CJz/cSzct4AzWllhijP6Wm09HM4LP3CzlOMx99
*/