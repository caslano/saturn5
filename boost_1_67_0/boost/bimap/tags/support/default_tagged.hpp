// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/default_tagged.hpp
/// \brief Weak tagging

#ifndef BOOST_BIMAP_TAGS_SUPPORT_DEFAULT_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_DEFAULT_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::default_tagged
\brief Weak tagging metafunction

\code
template< class Type, class Tag >
struct default_tagged
{
    typedef {TaggedType} type;
};
\endcode

If the type is not tagged, this metafunction returns a tagged type with the
default tag. If it is tagged, the returns the type unchanged.

See also tagged, overwrite_tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// Default Tagging
// A metafunction that create a tagged type with a default tag value.

template< class Type, class DefaultTag >
struct default_tagged
{
    typedef tagged<Type,DefaultTag> type;
};

template< class Type, class OldTag, class NewTag >
struct default_tagged< tagged< Type, OldTag >, NewTag >
{
    typedef tagged<Type,OldTag> type;
};

} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_DEFAULT_TAGGED_HPP




/* default_tagged.hpp
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
*/