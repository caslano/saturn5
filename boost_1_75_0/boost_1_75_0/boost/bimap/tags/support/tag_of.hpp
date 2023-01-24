// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/tag_of.hpp
/// \brief Safe way to acces the tag of a type

#ifndef BOOST_BIMAP_TAGS_SUPPORT_TAG_OF_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_TAG_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>

/** \struct boost::bimaps::tags::support::tag_of
\brief Metafunction to obtain the tag of a type.

\code
template< class TaggedType >
struct tag_of
{
    typedef {Tag} type;
};
\endcode

If the type is not tagged you will get a compile timer error with the following message:

\verbatim
USING_TAG_OF_WITH_AN_UNTAGGED_TYPE, TaggedType
\endverbatim

See also tagged, value_type_of.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// tag_of metafunction

template< class Type >
struct tag_of
{
    BOOST_BIMAP_STATIC_ERROR( USING_TAG_OF_WITH_AN_UNTAGGED_TYPE, (Type) );
};

template< class Type, class Tag >
struct tag_of< tagged< Type, Tag > >
{
    typedef Tag type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_TAG_OF_HPP


/* tag_of.hpp
UHsUbecgeCDcvqqzapRUykbgEYgEMHgXC7ual/pYd5S+YIUuAbErd7Wt4EJUfdGehz1Z2pKpzioMi5VbTCqtxap8V1imk7xueV1IXuMeIslrUsumJK+yYMkL4235LC8vaF6l9dgOVaW1c0MjlZZnHW3KjS0aqbSuuM6g0sqkAldcjaLXjMdJ9GozlkWvTGVD2blFr718TpgEslAUyUKcdmpDGEc29JSpotdE+vZJUrOi10RlaFmzohcboq4cDM3FUHOcNoebq1asZZroVamMfppkojJV9KrURK8dERrjFCx6rcJva2k1aW2BBVdFr7824tatpOafWadrhjdpmbpJwWkX8BL3XAlyF2K3xkIXcCAXZCPNL1YmPU14UFNj5d9DjEf8OaWtwq/0bIftYayuXLlphpGFePc9YiHKmYW4mAZTLsrsm4RlSpULgso8xWVKucyfH2KZUk3aitioSVt3hxP7l64Tt65+zyBuvfNh01yIZ7hejxWjF7di9GTvoFWnx4phqre6H1G9GEn13kK+xIGdxcpqXzDp9FhvTiamI6sfC1svIsbIho7rpK2sYGkryyBtjbPqpa0sg7SVdX5F1l/9jIqs8C//BxRZS748v6TVfwMqsmyF4NyZ5CtVeRCwR21AMYoomIZ/A/YT6/EDpNTe/yfwjHj5Q1N9ISEtZQcB/KXUpJLeuXjzfpOiyjdKsHxzrwXlG0j3JBl7
*/