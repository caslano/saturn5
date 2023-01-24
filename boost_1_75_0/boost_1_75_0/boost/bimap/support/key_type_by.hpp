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
8HBOwKhi4qsWqm2dl1Z9tsgpco8u2J0dXmquvf4CE53IpHrvjZ3oSFxVJOrAL33El5Rts6BOM5xcjUZObZ6qpF2AKVrcp24if2rivbGTsjtDm6Mpn7bgoRdAj1bGpjeqB1JYXfVrd8qEXnMFBk1HLs7+wFvh2v6fsQ5l2lbgWp/ykWx7I3rAYFfytLeH/2nF6iAJhNx53cH5wjE8lYSsyYS7PO3A9LzXn7w6tVncC1XGKqCffvv6t9WLSN1xZlmL1kvLjsjFDk5PasxEOHPkR98O6ES77rS/uXFgHeWAYdtKQEUF+OFu6OUpYbd2dlpjSMpM9SmCrKbCl8+7UbfBT5saNjAe94yYqRBCIfAesN94FKGmgCYYzruWMNTF8ZRchL5LF9C75hz70W66bBT/0BlC8Q+hZoOj7ILvxYsQSbNb4l1KUbLuqnMMXNc6WIGulG0Qryt7Pq/eSuEL4vS1aFndg1ZVI5MXEUHHz+nwHRQmaf5FeK9GdNVpNvFFqEsFTQF16GXh2tzxAXKoNnzAx7qJfryryVQbEnLOZcQrYQtiE3na4YPSd9XpgG4oW49YxUqehnKkPdc2JDppWSC+f4hOWh6APHu13biXdmPXN427cS93JU6XHVy2RGOARnj3bowl0w36PuNUCHlvOYXeW0JTfPthh77UxYT+DLoI5AlmpnBrTjf82V1YZlsam9lUv/f/YTV9pPW7Wut3
*/