// Boost.Geometry Index
//
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_NTH_ELEMENT_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_NTH_ELEMENT_HPP

#include <algorithm>

namespace boost { namespace geometry { namespace index { namespace detail {

// See https://svn.boost.org/trac/boost/ticket/12861
//     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=58800
//     https://gcc.gnu.org/develop.html#timeline
// 20120920 4.7.2 - no bug
// 20130322 4.8.0 - no bug
// 20130411 4.7.3 - no bug
// 20130531 4.8.1 - no bug
// 20131016 4.8.2 - bug
// 20140422 4.9.0 - fixed
// 20140522 4.8.3 - fixed
// 20140612 4.7.4 - fixed
// 20140716 4.9.1 - fixed
#if defined(__GLIBCXX__) && (__GLIBCXX__ == 20131016)

#warning "std::nth_element replaced with std::sort, libstdc++ bug workaround.";

template <typename RandomIt>
void nth_element(RandomIt first, RandomIt , RandomIt last)
{
    std::sort(first, last);
}

template <typename RandomIt, typename Compare>
void nth_element(RandomIt first, RandomIt , RandomIt last, Compare comp)
{
    std::sort(first, last, comp);
}

#else

template <typename RandomIt>
void nth_element(RandomIt first, RandomIt nth, RandomIt last)
{
    std::nth_element(first, nth, last);
}

template <typename RandomIt, typename Compare>
void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp)
{
    std::nth_element(first, nth, last, comp);
}

#endif

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_NTH_ELEMENT_HPP

/* nth_element.hpp
pPfDkHLIg6C2u4e/9ADn/5bo0w/H+6dDeexrcCPECEYPoNSdE4HPu6ODA8O8By3Rd8S1ftbSYFxen5Ue4sVeSaqMs+wcaYYLFWDYRQd+gV+Ps/GcscClKmuQ8XM0oGAfe7iY0Iz+avCwAF1GUxZsXMu+KVMvbX6z+7B/uLO0m2Cjl/RDBtgN/1buq90pGIJW42U/GwOJ4OYE0ZbMDbD3f9VzRuD6KwPXX79XwXhxTfsMjzwUyLCVN2sI1P7614+hATA4eG6qC/nrR2t2DI869ibsdH/x/w0sGaYGTapZV25ccjcpknVOOUjxTlIsi4MY48ligAbaLQMatykP+DCsGH4O656GxjfL078/HR29Gb0dvj1SP+MverB2Vx7B7TXb+UChoB8c/IksFtAxha8JJuRcq55USydBGTsq4+T6fxRAs18PLQ/NEOkkm1ebmzsrv8ZiuvHn5LsffX6ngb/9dvmXSwbVTw3cUDYAv9fBjqZ0h2Az5xFcbL7Ehytn8jdbg5kiwPBjvF2PFY6tDHbpPEb5JjwIjvyBF5Ghm94jGcd5iQ6AglCEfv8RE+CnT7jTq6zhc2B/MCS5PO81+ay+WCz6d7gO9I+hERjMGG7In8J9S54nz4CwyRC9cN+TPwXHQ209ERF0kX0Glhtt
*/