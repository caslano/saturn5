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
eqi0ywbewcXZYH4ymZ6Hw8n4j3ByugkffcYMOmpGnpJj2madT/TB3OJzEl77ZDA6Oz6qRT+9wOpnpfJjsoq74v/F6tNr9WOSWv2ApcrhFEKq7p2WSU0NC8MWt4h9bk+8oCh4ClHYZSiVdN2Vg7y9cqcVof5L7xb+MPD2JhfzkKYANlavKU2P78W62Nj0QPTOyD82+Eyza9s2d/znfrKo732FCzUD08l5OD6eX02mp+HJ5Xg4H03GbV9/Mr7UDz0FXwc5n/wnwM9axTcA+hgv5yd734T39BKtstLi0Ysc56VOepszkS/E0kKco1BV+c9UNAcrtbpIm8rc2acq/BtQSwMECgAAAAgALWdKUs9BDdbjBgAAFxIAACQACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL3NlbmRyZWN2LmNVVAUAAbZIJGDdV21v27YW/u5fceaLdlar+KW4GO7ipJjhOG3Qzg5ib0W2DAItURZXWdRIyol32/++c0jRlpN2AdZhH+bClUKeNz7nOefQvWd/36cFz+DRT2S/EX7waTUulfyVx+bT0lH0Adw/1LrB52NOerBX+RAF8LjKB+hYlaj2ckLvUfSYoxuKjf7rkeZNRK+4gmqkOZblVolVZqAzDmDw7bf/gyN40X/R
*/