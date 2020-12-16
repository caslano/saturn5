// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/member_at.hpp
/// \brief Defines the tags for the member_at::side idiom

#ifndef BOOST_BIMAP_RELATION_MEMBER_AT_HPP
#define BOOST_BIMAP_RELATION_MEMBER_AT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace relation {

/// \brief member_at::side idiom to access relation values and types using metaprogramming. 
/**

This tags are used to specify which member you want to acces when using a metafunction over
a symmetrical type. The idea is to be able to write code like:

\code
result_of::get<member_at::left,relation>::type data = get<member_at::left>(rel);
\endcode

The relation class supports this idiom even when the elements are tagged. This is useful
because a user can decide to start tagging in any moment of the development.

See also member_with_tag, is_tag_of_member_at_left, is_tag_of_member_at_right, get
value_type_of, pair_by, pair_type_by.

\ingroup relation_group
                                                                                        **/
namespace member_at {

    /// \brief Member at left tag
    /**
    See also member_at, rigth.
                                            **/

    struct left  {};

    /// \brief Member at right tag
    /**
    See also member_at, left.
                                            **/

    struct right {};

    /// \brief Member info tag
    /**
    See also member_at, left, right.
                                            **/

    struct info  {};

}

} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_MEMBER_AT_HPP

/* member_at.hpp
8bNW7FNIfZyauc6TYvaI7ynkoqXrGXKXi9mffD6nNd/pHax8LcsLxqEFXCXxXcNZPonmHo0lvQmMXzRRMy8Pe3APK6y+dlip4u9ZQmpkyuNS8Xcz3/iN1J0XVmPnNteqKyZeGXC3xH+a73U3SeUwen3v6cfQ9143Gv+Wvmq01/e+oji8/7ykOLz/PK84vP9cWhzef55cHN5/HlMcfkbZ8OLwM8oKisP72X8aFd7PfmdUeD/7Nc/MpOOlUeH97Gc9M5OOxzwzk457PTOTjjtH/WvnlvEbM30HqvmGKP3xjVH645sj9MftM8mOVQbJv7vv/bb0vTMmZzxzb7eKIfG3rXyh06gWjx+5723e/9pm1cPuqKmuJ+spDabrWpa2sL/2qUtgDpwAO8DJMBfOgp3gMtgZroBd4KWwK1yta2Jugt3hnbom5nu6JuZdXRNzSNfEHIb50PWva4IZcBTMgwPgFFgAd8PT4V44GH4Eh8AKH+UKK+GZcBEshDXwLFgPh8GVcDhcBUfAK+FIeC08G26A58D7YRF8EMq5F7AYvgrz4R/hWHgK+VkCR8Bxx9mH3x3rw8eu2BW7Ylfs+j+5Tk7/f2D/EzX//2WWJ7N/ksoaf8e/7hY+DWfyzbj9bKv/z729EYCoYwDqZ4AZA/iL6O93o4wBqPsRop+APv4cv/4e1SN9vEhls0fp388xYYyPImd7mHzvFki483SOP+hnn1kDsFns1ztib+7breHcvzkju524v9IN9vMPSniT3T5OJ2stgN5H9w9s13yrTdSxDfTBvuvZEt7FbprG5zPxt8l9iDjZ4wZ2eDv0bLxuLaQ/KWaFIeflLTB7ClpL+CvcVvRMo40xTBc3jU2ftLHov+9MMvK96SmL2QH8THKe4Y7WOII5zzxJ3KxzPVmMNTMWl3tnhWeJ/WURxxMqsOfS++ygB95cxhPmqvnLYl4cstZhl5iN1PGIgNlDYvYivnPEbYWOPQTLNcsfppppmrjXWOchxpKwk7QSTlh60+Qe2HlhSb7nNByrsNYX/F3KLN3IsGwhYd6hequuWf159S/pbi7uN0kZEOeG8T3WPr6RZVliybLcGKE/ujlCf3RLlH7ntij9zu3h/U6pr7USrtZ9zAoh9RezMnGT8x/YN215qYTzWN7ti2un/Lz+rDteuTQpccCR+6Zbgs+qvlfrIcmkFLlUvsgg2F7ljOTAG2AH+E3YCT4JO8PXYRf4KewKP4fdYFM9cy8V9oJjdN/EZJgH58K+sB72g5fD0+A3YQH8kfY1n4ZDjrOPdzjWx4tdsSt2xa7YFbti1//5ddL6/2XlJ6T//7csx5z7M1r7/wn+9YHwLf9csP8MtRGm/89t+4UOAkQfA1B/Q8wYQKXon482BqDuR4l+Ivplov+h6l2nmXxHtzvSGICGwdp2MwbAxK/j9f+/Jfa3aP8/6L5e+//oR8oacNt/vmP1z5eI+6fEfxHuZ4q+jenjnSb+b7DXCug93JAzETRsPse9sYSnxd1iXfvNfKvof+rudVKsvn9oeJw3EHFsogTz68XdPWZs4lLRT3FbO0PN2ERBg/D2RhmbKIIvibs5ZmyiQvQ/c58nv4LhFTYIb1+EsYlJUcYmrhV/t7s9jzA28Ttx08Ss/d8s+mluPmbfZJZe1/prXekWcVyiXPzsiDguUemi0zIOjks4Oi4RrX+fpmV/lfi73/0B5U+eSZ/2NY1f2By91tebxL7UfcxJ1jpsxV37829of77qKP35OVZ/fkuE/vy2CP357RH689pH1/48z4+a7fTM8tWM+mfM+gXN9kbo8++L0Oef9F/Q5z9H+vzPTJt0yZqB62Z99P2Hqp1xyV8dvc8vz4C+S0M=
*/