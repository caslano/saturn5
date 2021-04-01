// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/key_type_by.hpp
/// \brief Metafunction to access the set types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_KEY_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_KEY_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::key_type_by

\brief Metafunction to obtain the key type of one of the sides in a bimap

The tag parameter can be either a user defined tag or \c member_at::{side}.
The returned type is one of the {SetType}_of definition classes.

\code

template< class Tag, class Bimap >
struct key_type_by
{
    typedef typename Bimap::{side}_key_type type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/


namespace boost {
namespace bimaps {
namespace support {

// Implementation of key type type of metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    key_type_by,
    left_key_type,
    right_key_type
)


} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_SUPPORT_KEY_TYPE_BY_HPP


/* key_type_by.hpp
CPB46Org0yyC1hmTT+zBWw/Z75GGqoKsr9RVFF+JNEYbVY/5+YKem/ryr4v+UAUqGgT311AEu7VVQqhR1L9zCVleiBFcpE237c+cxaySv5AfQd3hvP67c45Ond81nGC5vmsQHwc//9qTGfqni8EvreltlVGd6QR6+ETgbVpNkGe5CoUcO5cIABSGXtV/qXM0wrnIYvjtAVQIiobjPCrnHpubxYVg4PUrUjH4EbyQt8dQzuOrHiEq5VHK41v0hX2pOAOAsuaK0o+B8C83pt2qWgMerz1jQkwKLA5PU/Haw2LHw6Pgg6UXC5/a0HC8o45c2DRMfRZeu+SdBVtsD3fWJ/yoiTRIk0K39oY3b//rqecFvMZme0rSfqs+UGeaUZQzHD0VoJtpSHrpRFTbxtMrLXc4wMfX61hbLGiBBZbwSET4T+jg0YnYN1vRmQBJjtbD1RnxOz4sYUfg8C0NE6f6cygXyG4u9s4HpT1K0PgBeq5MtKOOpB9CUjDHzmzMTYmRzk+3NSb5VN8hmq1+BEA+jO43bcqsa2n2vrHn9KLiw3fuimjOPE6rGTR3iQ==
*/