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
jWxjQesZ5JRNmo1mtBtWWoz51vm9s7NAqfkemg23tAB989sMt7TodtQp24fGPUKNbFIMuRxma8oh+KQc3u/XlkPQNL8cZmvKIb7jWg57feeM369z0P5q4ocVZLd4gb6htkP136K0l7yPFhbnTk2Yy9ni3KD+ji36NhQJ7EyDiVlowzVpwE2oaxkMNpwO8G9+Gzo+q/E21MrXck2cPjH6BSVOUn2bXHd5bIyFMed35kHOnep3UG3NNKvO0rTNJ1BvqyVN1Pi/pZHrM8S/XpFLqizJNtmvaV9t9fWgS79RfwL1Fd901NeDzn5D0nv9D854/QPx8gxW44XRi2ucQCtldKJz7AL/5o9dJjvGLrBLvVPzqO5HZ1wWGO2+Gheucq7lB/QN1jn4N7/OVUdQ56y+InjcGZ88Yy1C4mOskxrn17CGja0aaEWBXgOzTd2vyacCW7wOOPMJ/u7xLrf5y1pzE9rU/Zp8PCD5KG2q6xjuiCYt5hv9iktanMj8w0r/tT85v3mp0Y67fjM0B1mka8sHN79dWiTlRk2XJT9r5mTGuoibjKFBhWs5Aa+0Uaenatso0DS/jdqvaaPwHUcbZeXDlF+ccexsrJe4xJFruFs+gK+RtZMTqN+LIqjf1r3IYxyvU6y77jB9EK96jhfuDM8oKZV7wzZ5cUUDyPvTTN/FOpcU6X3u4SmOekfhKvoVDyBk499FLOM0mPxcxPo0kXFmedlMaFSpWVBTVDZzpqnKFG8MQ1fxbMgifcIiTn+LtwvbkTtkb+k4iz1eaHPlbMdTEe6B89lg7isWkX2Mi+7lNV6v437qKUYdkjjy6Xm6rl8Z4PPBPE8v4XhY9HE2vxlWPODXtLun5vy8hOx+sc9Q1t5WRDnl3o0/O13kLho+edSwSSPGFI04u7Bo9Dm2OyElRUr94HiE/GeI/3jxT6P90LVIu0GQYwed3fJgPzTK3xRdU+a9DXyf3fzihm+G6YcojDbjm80BZcE8Ctp6R3zRp3Ccrfb4YTOeAWUsxvEM+c8Q//HkH9nbMVZcHjbjEpC4iBuFq5S5mBgzLos5/6oMY/w4XeJiu7cBqFukvbeRSfQXcZws/kw5O/JMumkOpMA04V07XT3ZxjL3gknmdzTeMfY4w2XGq3vlhsSc9o/Q2pDh6BG5HySebJbbCiPVdk8k8vNbCB+yUvjK2NYfb8o7FJAGPAV4rbEmIvJSx8HrIVba0ts9cmfQM8Sgbe39Db1zdgnLa4WRF+JDH1ldyWVH/NvKWY6fyN7eeyP+JqLO6M5nZAHvou+V44ycX3vG807DH3LgDQH7eQ054/cU+Xels5fbkV8HYvFqCZ2nrnScp7ZoPHFe86yBr7vzfWim6WXRxAe3+mJ9vqh4j4PWCm81aLOMb7YPfmrRZMMedk6GZJ4EzxdI5vaOczBWWj9D/tnKN7bFeflcQ3CP23nRPk08L2qWeeQ/u4X6C8pbZUyyj8tWLkwS1+HzUbYCQ0NlqxoVoaoUT6HPKcPQvA7vs3tsukYX0CU0jiPzpdnfMZQ8DZJfYqN3c7k+8HlWDh933K4eynfc/GobFEzg+sH1eSC3QeskDjRSpHdWinC1blZZjbYNepToT+K4WPytzT6b747PieA8pqbtkbbf38KUtTszdIPZgPQ+HJJ1tugSry2asRjtv8v9Lubp3mi7rrkzKuPumJamPB9y3r9pvfF5hl0e0TOHMRGKQGnZIpe3NpkvU965HE32v3kG4e/FMItg0HaE2g0es7bjduFXRP8A7BgFwlwMswjGyoPMJuqKXqbRtb0u0YzzIu57K2EGoAIUnukWZ/5taOvU5wXz9qVz8d3Jz87C7anQ9RJdB0vIPt6TSzc=
*/