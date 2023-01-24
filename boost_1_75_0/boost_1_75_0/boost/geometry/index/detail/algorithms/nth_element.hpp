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
PANV10RqHG4nz6K4T/vsSoK8NYuruVQ311/zJcFgudZ+SJaWE+arDV4tudVqAwPlHND86ONPLy2Xcyonrac64v3vMcrztYK1sh6xHtUH33Stf1XElTuYjIapNXL/7GUqbkyuV67y5L0xdUGsc6V1Vk+NyBavex4pvkRh4jIOm2OcgvRItwPwGfmmezeJbqqiXlc7ueL99pxtm4WuaidCZJ3mFzoicAD7+CkfbZXWrg8vqp3e2D1Z5bElV3KYIJ95G/rzhtNLiYtub5P646e/7DSiqO894JWUfZOutSL2tZ9r7kc4/sb3qYZjWa+QUSeM3pqyryfQ22Io9t6gy5ogXZabHtdaTxLdUC010H/l89VXjtYYv7zNZIwozrP+C82T9G6sMn6jWVhp3NP5Q0jnqBFvunXdH9P229zr0Al9cN/2caBk/nOfpyZTM5E6g/vcg6A7St0YuUBodh6wvM80JunlNm2eUqRXubEgHg+yz3mamc3Kq4rnEVWGJC9HjaFx3xvcaKG0hOXR+/kYDrXKI2nTSl9bqq6FkXdwSkLr9xi3HGjd+LiXC/j1t2Te4Mr3dRwmxwPzbEt2n/RPj9dpLamwJ9m1ypFK5f7BeOtnpfBhyl16usWezQaKH4fdjm3flQKZqqjPPitRt4Z8V/z86L+mXWVAjqlnw0t7VUX+RNPf6PKRFUYLWSEX5mqhlcC4NZOaCCp7+IoHzsAg
*/