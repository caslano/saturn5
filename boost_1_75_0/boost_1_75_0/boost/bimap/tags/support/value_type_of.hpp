// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/value_type_of.hpp
/// \brief Consistent way to access the value type of a tagged or untagged type.

#ifndef BOOST_BIMAP_TAGS_SUPPORT_VALUE_TYPE_OF_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_VALUE_TYPE_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::value_type_of
\brief Metafunction to work with tagged and untagged type uniformly

\code
template< class Type >
struct value_type_of
{
    typedef {UntaggedType} type;
};
\endcode

If the type is tagged this metafunction returns Type::value_type, and if it is not
tagged it return the same type. This allows to work consistenly with tagged and
untagged types.

See also tagged, tag_of.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// value_type_of metafunction

template< class Type >
struct value_type_of
{
    typedef Type type;
};

template< class Type, class Tag >
struct value_type_of< tagged< Type, Tag > >
{
    typedef Type type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_VALUE_TYPE_OF_HPP



/* value_type_of.hpp
9cR6q4rL1V7ZCtr8BSYBY+kj9uw09My7KUrlDaJUOs9Y/ngY9qPeZOhoPXYU1/VzPEIqrGeUHid+KxK9u8HNeWEJ0468bugJ3w9Z4ZT+9RC1w9vLrFor/iiNYJfSB+qWXzrEbKPOjCT+usHnljUx+Ow+Afu94kPdhRCDMMsN8PcYsnZ7oGu9YsiKY2M9rJReJhxQ1oxM2LHsf0EmhHCDqjzog+CUY8uaO/KScgYtVEGbXwKB5Nm5BXhYtysl/7Q5xebYCaewr5tN2inaY+t0p2gwEu04jlycmXQf6GhPdfnjz+PIBTf1I2dZCqz9jK1wiqgP7QRQQpN09AOEgiD2pA0DhrZ8Orn8ow8ayeVvfNCMEuPZD/4XlBjgHUVVYKT67o1Nr30DPLGog+pGrTberKH0IXiziiTdZq398FQgsB6ML5Rhk+k495Ep9PwkGw5vN2XT222ceiM/X8lW3ZC1mQyhnhYMpCPnOdl0ObyAC07j9+gpaoHvH2X/b5zlDLf8Nz/TtLrfhaxKItcdz3XFccEYft84WS0w41G+o851vcTP5yfz4fThKVSmiD/kTab3rzg9S6trINc1Vku6iLs+nEtfx8/neFou5/dL+PmUNupDWTCUSVfQUMZzc2O5YAa/H31ULfBBFt/R5258w89d/LyIi3SZIv3SxATFFK9xzjhM5NgSea10XhWFbuA+c/lOosIlXhAwjLAWQi4o
*/