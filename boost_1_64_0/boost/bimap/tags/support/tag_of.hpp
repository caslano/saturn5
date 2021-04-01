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
HO32sTTFMSk80KWPW5tTDCHAB0WaSdUVXn7lxcWI7sx0dmQV/X+xs5SH9/dsU/NR+oXaGeDUnMhiJAi4rjApuczbAtJiPPUPHWAxYm8ayQP5khEBrsytPkgpdiT9X76xX9K1lW/CZ1v4LcYJRibN2hvm0nY1IXOimgtPX3vWkDQexn3ksMNYzNtT5BjDRfi71e6JWCioP9LLWbIVw5Sv4u9D38Gja7HpJ1w0SlYyKWbh2VDE7pv098bjuVqtst0SAXA8jFBlUfb94QDZz3G2FrNggWUmx4DIsy84V1/zwnSfT2+ME1LoW9a0FIHfLwSR7cY+iJWmI0y8AnvruvvQI8H4qPImEeM0rgRNfB+e8Mi5nWzRak5MY7XogBCRd4szTP8PtS8aczY/pi3pLIfjVGIu072PKk+2P+HpmWwglrRwe0H5egBcDcNWdUwWby48fO5wa8UVjiKfrd0l4LQ9eCsoFKwsvfNXwqIi+Li05nNH2UMeZMH7W8rlH/GwTWfoSFLZe5z1UXOOfHx4qxfw5+QE5c9eYOy11IGPUGFQ6f+PeM7yi13O/NFBrw==
*/