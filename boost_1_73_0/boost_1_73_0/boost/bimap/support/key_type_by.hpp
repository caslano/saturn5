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
RdpSlbnjRLXYc0L1ikRSEuHNnpOLAhCZgFOAE4EzgJOd62nONe0bQqPB5ngvC+i9oZcD1wDRCMTfA+Jj570lZUASCfBBx3sA5wf0oeoLgf2o9gNpwfNqIH3/iwN6r0l1QJtZmQWkmUJ8ynHadzGH1AOBU4H0reFjji91/JMINZib1kGOS4tQmpsg3Gzh5glXK9zNwj0h3FPCbRBuo3AfC/e5cN8J96NwR1iG62cZ7jjhjhdupstwc1yG4y7iQLY=
*/