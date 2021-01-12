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
/auzF8LLqP2bEP7Yr++8M+ld+7W5Hy+4ecXVjkzB33Gm/OIVDj27+5gz35y+Xs/nZz96xMGK8gnlDzvxpVv3brz6y4cbB87b+vYheJHLsynhu299z33eE99d033nFit1nP4avFh3FOWvvPC4+Du3Opd3m4dv+JaeHQZuOuEXfvP9M2sss1Hbs85D9z/HQ/6Thqep/RN7PPngj18c8/mSI9Zb7ZojF4LthrMI7w0k1nxj6PMt
*/