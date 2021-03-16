// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP
#define BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class U>
using convert_integer =
    std::conditional_t<std::is_integral<std::decay_t<T>>::value, U, T>;

}
} // namespace histogram
} // namespace boost

#endif

/* convert_integer.hpp
dykvvuBsD0r//xeYdS86rzc6F/gOmPRLRXyLrZ8LUf/nC980Zf9mVU2eZf7KCv2j9bUOuK0C20PHleD7VJLvCHDHJfjOWyvH5wZu2NryfNdK8nmBC0vwtUvydQF3twTf05J8LwC3UYLvY0m+Q8AdleDr8bIcXx/gBr5cnm+qJN8PgPNL8C2Q5MsAd6cE31OSfGuAWyfBt0eSby9wRyT4vpPkO3edS3GvK893xTo5vunAeSX4WiT50sB1SfA9Jsk=
*/