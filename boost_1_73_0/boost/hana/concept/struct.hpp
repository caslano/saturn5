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
Rnjx/+IvD1n/NB527XDDIq370nA8jVMZS0/Tg+TLJouVjZKToQbJuHYXB9nu5OnKtJniNSmfE6Q5KWNSPkxIGnmlSTSUSKhm183wYjmfc1fZqXH90BBFu42G6EAjPaKowus5t9t28/xoz3rCiXRWTJIb3ZHpJ7gRyEADff1y/kqcdkdqD8sKyl5wjMYIY2cu7YmP1ghmyuXVoe92xjjZ2ahAfAyRPJcS+mpCq/VxxKSuMo4A
*/