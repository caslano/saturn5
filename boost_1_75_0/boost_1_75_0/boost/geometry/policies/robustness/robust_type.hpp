// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014 Bruno Lalande, Paris, France.
// Copyright (c) 2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_TYPE_HPP


#include <boost/config.hpp>
#include <boost/type_traits/is_floating_point.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL

namespace detail_dispatch
{

template <typename CoordinateType, typename IsFloatingPoint>
struct robust_type
{
};

template <typename CoordinateType>
struct robust_type<CoordinateType, boost::false_type>
{
    typedef CoordinateType type;
};

template <typename CoordinateType>
struct robust_type<CoordinateType, boost::true_type>
{
    typedef boost::long_long_type type;
};

} // namespace detail_dispatch

namespace detail
{

template <typename CoordinateType>
struct robust_type
{
    typedef typename detail_dispatch::robust_type
        <
            CoordinateType,
            typename boost::is_floating_point<CoordinateType>::type
        >::type type;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_TYPE_HPP

/* robust_type.hpp
Tuf0r5FK5Wd34T4PCZnm1j11rAAS6lEf6G5XaLfiNmnMYE6iqkqvFaP29qUGuMuRJrMVl7y3q3bHp4cSTSI70lMQ1x3VJOQTvFaLM9Ne0vdrUTPEx03CFYnykDtaHHmJOGaYg3/NtgmzxsB/V5Ow+7XKgmkyKFQR6QVXWZhJOlIONLDX6xnMjkolVpV4EmgwkWLaCnXqzuzU6qnWEmH80tS6NH9mtapx/Liq92htcLmEEu+gIxsyv1xbNbWlsl9Se1bZ7FB9xExANzzwjk5WcjT1beTWV8XC9ZSIQWrExj+0TUv2HivLaxXk7mFlBHPx9tOVbgLY7u5X25rrWuMHbnL6pWvLa+Rld/oB8RT8fhdamsP2BjrhNf2Ucc/8lr2KKzY8mi8MQOk6gqLNiarMVvVlKd9Jml3u5LDlL14syRX5S7WO9YJ+u9yfdx+998xrNN+u4QHyDWuK2HOmL0yW6huW043ethckDuTxabRrO9amVzGbV0BPHieQPyJa7qSijPYIWd09cs3y0K0dJXgO0zBKRo0p92cqe7vWmk/cgbj3pdiiQ1o/J7ofmaeWTk/mLnFmxXROEaO/r9fBEfDZvNRiWLMNK/VaubR9Z9oEc9SKz/S1cbnblPG9THKIgtBNEftGsN1WN817S3O1vgQGKOlxfqET0x6fnOP78pQ4Xyb6cP4JwyW/a0F33bjXlmmsWnFWpwzShB+3rrKw
*/