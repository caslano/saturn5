/*!
@file
Defines `boost::hana::Struct`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_STRUCT_HPP
#define BOOST_HANA_CONCEPT_STRUCT_HPP

#include <boost/hana/fwd/concept/struct.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Struct
        : hana::integral_constant<bool,
            !is_default<accessors_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_STRUCT_HPP

/* struct.hpp
a/i7N68Lrp09YpReqf10wEkgXLEAjecn8/vtJhfbdVJDQdnio4wE5WW6xGM0dcbynrZBXULWWYsXmiKxXnszty3euXOnGGOMkaSM8ZWxXLQot2jz0J7J0rd353AfS7TjDPw4fvyLNNRUctnaU1akeSi3+ryfQUMOZ3pqWncl/t84DEGeGGrLhKj3NlG7BFsPkNwgPk07lEvw4OLK9k2R2KwXY5M3tTJLb4+0W2zNWnzZC5HQTt/iOykhf9Hwo3I=
*/