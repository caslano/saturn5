// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/overwrite_tagged.hpp
/// \brief Hard tagging

#ifndef BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::overwrite_tagged
\brief Hard tagging metafunction

\code
template< class Type, class Tag >
struct overwrite_tagged
{
    typedef {TaggedType} type;
};
\endcode

If the type is not tagged, this metafunction returns a tagged type with the
passed tag. If it is tagged it returns a new tagged type with the tag replaced
by the one passed as a parameter.

See also tagged, default_tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// Change the tag

template< class Type, class NewTag >
struct overwrite_tagged
{
    typedef tagged<Type,NewTag> type;
};

template< class Type, class OldTag, class NewTag >
struct overwrite_tagged< tagged< Type, OldTag >, NewTag >
{
    typedef tagged<Type,NewTag> type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP



/* overwrite_tagged.hpp
UUp/wiLiumam3aeQwaQhazvEHKDyf77vMRiHA0JWzhB9bC2gtUuTc/fKcyeqmO7BF04IcB6OsBoMlwZCOhGqGVnBsx/3mO8xqhlF667i/Yuo1a1uHmQUo337vszXg2NbuQo0so5fza+3q8C4RgZ78Uehz4MxCbuY+ZZYVkaMYqF4jKWFG/LHMippknRzXM7QYDS1Xt3ZcFuQ8yxd8AsUYWq0Ovl9FsBYs3sStkJDEa9Dt0zjCgpuuVT1zvH+Io3G5u5or0jY/D9a4XXF9nhPx5m7d2qDRIoInsl5NfgXeJLblUjprMqZqvsZO4Cw/drvW1Ry7LtXHWaDvYFw4+dpcoOsmrZUKm59Y0uWdjKwRnFZ6+hsTP/34PAx24urOOFqluIwyXJygrPMrkbB2BDBlOM+mAKjpao4gK1G0GiPRP3d2MMHl+lE8GK4WIqj2wvyqaHqviL/ksbWykJuzjztz/b7En0zBcM4lMzqNctTl5OK0T0HeqsQ/duonNyea7Gdn7KZkRk35+YY+VH1Eo8Z3bA+J/RY77u+hjVdpHJwXPTof5jbHKzzjfZj4A==
*/