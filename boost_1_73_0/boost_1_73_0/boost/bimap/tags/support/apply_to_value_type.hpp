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
xCNbSSujCIh4IKFEE80BVCpB44V95CuIhlNP8L+mpvU3Aa3IGdgYzGA024BIWGkDuBrNf59czuFqMJ0OxvNrmJzAYHzNxk5H4yNKvSQwA3hfGrQEbkAWZS4xaTC/3+h3+ltwcHQ8Gx6uY6F/AZYRkVwQfqayWUh1CzTRYWn0rRGFjw6UVtuD2XA0gjIXLtWmYEsLX2ZS3ekPCLHI80jEH2zDsHQU1EJR/qh0qc5jre4oT5ITJZV1KIi5lM1UllGZ+qiSudumApcsTUlTsWsU6DJEvvJY46C/ioZj63TolnIBj96fb7/e+fkXOH4/PBoN19AUbMXXiPyua38VMeXP47IgG6kDipCZocI3XkP7PLUMNFZtr8E12Ab/yGUulNig4AqJMNeLt51VRymWIccXpkYXobCxlKHTIUZxIuPgean6kMW8vC//5yUrl+615tbcbKwSF97f3294hy01By4+VG6d1m1bYixTGT/KFxhNXUKhj5gY7/wkVZxXCcKBdYnUvezw0RYnqe4RtN2xTjgyNrycnjFvXwy9G2dE+VZUpSmagHLwF4YOclS3LtvsfKRIagGHRVnS7VPBek0O7tN5oxItHXWMd40qH0gK0cS8WivTeatMDzUsi5iYHtd0iV3svnoE+cpbp7nVXm1u
*/