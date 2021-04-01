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
v7cUCk6y8/5JeaO6wqWljCkyuSY5xuB5iKX8URZRkW00TGkGRBnK2igvHdNZZ5bgd+Rqpx8PrMBUL+t9s3vlZL+rsLCPn6SN6+Gy1gIt3WGqZuitbtOZWiiqZujek/HuyD743DuIRnQBKh9Z+NltghHUoa2MnhX+wuKtXuhqUiecmMAEu5mJgD8+rDkaJuOVeeNoBhsPXAw8iLtpRw9i/IwTsApqoACyrA3CLaFF9hAD8oAYQencHjhJpO08cm/nZ16vd8L4WexRX6qCc8tIA5EDzUm+NPC3PuVRV6W/t4KlW0HT37QYQF0KjwjfN3NH0Bh9PP4XabcJRckJjOEi5cfsZkNdbhNpbFIn15RyY6f34Yr66KToSy18BFaIyb0FRRMhXAyBVrvkTq/qjE4fc0Qz+AZUlnQuTbhjosJIayZiUPQZGgzlxpnJ9z38sas49MBEW5e+cF+QnpZX/Eu/5VOP8/OlNKXbhDF5oo329zqGJXo/MdOypUPL6FL3TIHzz261bbXevH/gVxYbHxra88Z9wH1KswbEpV2VP/J61Kui+I4Uciz2pKu/IQ==
*/