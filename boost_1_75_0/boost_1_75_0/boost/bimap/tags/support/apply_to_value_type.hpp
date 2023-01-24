// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/apply_to_value_type.hpp
/// \brief Similar to mpl::apply but for tagged types.

#ifndef BOOST_BIMAP_TAGS_SUPPORT_APPLY_TO_VALUE_TYPE_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_APPLY_TO_VALUE_TYPE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>
#include <boost/mpl/apply.hpp>

/** \struct boost::bimaps::tags::support::apply_to_value_type
\brief Higger order metafunction similar to mpl::apply but for tagged types.

\code
template< class Metafunction, class TaggedType >
struct apply_to_value_type
{
    typedef tagged
    <
        Metafuntion< value_type_of< TaggedType >::type >::type,
        tag_of< TaggedType >::type

    > type;
};
\endcode

This higher order metafunctions is very useful, and it can be used with lambda
expresions.

See also tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {

template < class F, class TaggedType >
struct apply_to_value_type;

template < class F, class ValueType, class Tag >
struct apply_to_value_type<F, tagged<ValueType,Tag> >
{
    typedef BOOST_DEDUCED_TYPENAME mpl::apply< F, ValueType >::type new_value_type;
    typedef tagged< new_value_type, Tag > type;
};

} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_APPLY_TO_VALUE_TYPE_HPP

/* apply_to_value_type.hpp
tD2aulI0S4wqJXETkHpbwUt4vriMLA/22Qru6gYGa0LwvaUbVonO4z8Ax8DF4g2P2PyF+CBH7JF9NoWblCumkxF5Z6jaV2i0xfeTMZdZi+b2G66FZSo4wAI50TnjFPixnxKValv3Cd2NHv5DmKluEB4JLP9cjPGeBoGBe0sWx/lZGFYEvsVcvgp3aDn6w4BP4RlWMdEpZeHY1QwnFQi/wQIUa9QcoFgRyo+PWOEugd/tVPw7wsDAopC844vOpPqcDSn5teGp/uvhQlYiVfCr22LK32UG78xq2q7PyQ18ouIUlYj8YDucTt+eGwm+HyNs6zrn1w3wtLCtuy3Etq6iL7SZrnTGNj1Xa+0FtnPxeCr+GDYXQs1x2l3cXLzy7WdwBRQcIoHb1r4LUWUnp9npGxuHdvXo/eGxLrjt5Tc4MVZD892M39bSatLaej14FhOJE7+tykqel7H5ez/TNSNwdKQsQyYQ/oWoIBS4LCENToGWkb4QYmnLmOlXXw9x3j1dxELUzQSdox9VjlcthNFgfjdc2/sSzBKHT0UmtrC/qkcthEMw76ZK/BftgvwW1yHoYSGrq7/Jw1s9MUrnBVKJidejlMe3oQ6T3FK2DNh/34UDi4H7c1QmQvllvrGMg8tEcJn1VCZC8w9btUs7YwsBMPLmLkYmnCoI22Y4RHxc5GYlqEAQkIN8xA4ZGwgkoKr0NjGhJH9SjOdCeIHD
*/