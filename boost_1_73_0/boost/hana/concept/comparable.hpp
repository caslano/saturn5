/*!
@file
Defines `boost::hana::Comparable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMPARABLE_HPP
#define BOOST_HANA_CONCEPT_COMPARABLE_HPP

#include <boost/hana/fwd/concept/comparable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Comparable
        : hana::integral_constant<bool,
            !is_default<equal_impl<typename tag_of<T>::type,
                                   typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMPARABLE_HPP

/* comparable.hpp
eHO9Vl6wGcapbj5Z05HiqrofSJrR9tZTFhtzFA00ulvBTv9gosQKOMpqeODbxJ1bwmApyMGgkeHVm+A1jGe37qSZqK//lpVY5Gc6P5YmR9nkh6rZ5KEohroNip91Uew6U9/blE204mX3NCBueIc5WH4v4XZwn2/Yk8biLheCrBh7nC12a7k96UJs83HktfF0ytEW6Ta9FNYWtiyQJeQ2a6fzLdc6QPJrbpWz/2TRTi51Md3x
*/