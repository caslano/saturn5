/*!
@file
Defines `boost::hana::Hashable`.

@copyright Louis Dionne 2016
@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_HASHABLE_HPP
#define BOOST_HANA_CONCEPT_HASHABLE_HPP

#include <boost/hana/fwd/concept/hashable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/hash.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Hashable
        : hana::integral_constant<bool,
            !is_default<hash_impl<typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_HASHABLE_HPP

/* hashable.hpp
DxIeP9bx+LGan0eGLG2fkKWl43GvJjHMlVitNI93h5XfDgFu3gQvzXTRlRxNkO9e3dpZ6VZ09bddiZ6wloCYloBVSiQgJlYIw/4m3mYV31MGjfN6dI/SrC0b0ccj4RUhBmj0BAiJ5TcZgDqvmDqvjsRqeteYvimZHW6R0Tl6Ikyff/1DK8Qk22MiqX7oEwBWbFAhFoZEAHKAX0sjAB7OH7hCtKvJfs6vVqmcX6NSOb9Opef8RpXC+c3Kz/mDjQg=
*/