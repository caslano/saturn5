// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/value_type_of.hpp
/// \brief value_type_of<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_VALUE_TYPE_OF_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_VALUE_TYPE_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::relation::support::value_type_of

\brief Metafunction to obtain the value type of one of the sides.

\code

template< class Tag, class Relation >
struct value_type_of
{
        typedef typename Relation::{side}_type type;
};

\endcode

See also member_at, get().
\ingroup relation_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Metafunction value_type_of
/*

    template< class Tag, class Relation >
    struct value_type_of
    {
        typedef -unspecified- type;
    };

*/

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    value_type_of,
    left_value_type,
    right_value_type
)

// Add support for info tags to value_type_of

template< class Tag, class SymmetricType >
struct value_type_of
<
    Tag, SymmetricType,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        ::boost::bimaps::relation::support::is_tag_of_member_at_info
        <
            Tag,
            SymmetricType
        >

    >::type
>
{
    typedef BOOST_DEDUCED_TYPENAME SymmetricType::info_type type;
};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SUPPORT_VALUE_TYPE_OF_HPP


/* value_type_of.hpp
bDvUHtnPvPK3zt88VZNWoE3h9LqRthuhC7IMw6SbKLevg/zSJ9rZHYWSBWEFPfIlrgs+n0EZxnLub/LZ832U1txqGsx4iFquFSIB7wcqvo8n03ZsMEoOuJThhDq9J62z9i8jgRHaYipOj4iOaavNzel9azK8WyB2DbvUhYnlMA4jiGICSMLpzwZBcNvE5qnXVHhSms2ry8jwNzoIclrus9Gu6g8CjeFElqCmZSKCoB3508Y5L2JcxBVCoo7rti4Vr/Ov169YK7fjUB6yMiySGiAU7Mf89cYgo3C4Nay1v3POEzUmDu999C/sZS6fDjBtB10bkkMZ7PhJPNk+BcaetGk0K92VnAkz0hjC1pL7snSj2gePzjzFdmOP0JNobefdSMVRudil1wDTbMPOGFPKRej+tM8l6LR04GF5zECH2mC05omUI/b+WEUzsBFAY+a++1A2A9SAevrr5TOmF9aNp7h1TGG7gMfJqOe2maQxJTL5QqWtVe07Q182tF72N++lAd6M5eOy/1qR3UMv76DzD1uoXJAvimGmwjJ5ra9phbvvkKuJOd5vodJafw==
*/