// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/pair_type_by.hpp
/// \brief pair_type_by<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_PAIR_TYPE_BY_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_PAIR_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::relation::support::pair_type_by

\brief Metafunction to obtain the view type indexed by one of the sides.

\code

template< class Tag, class Relation >
struct pair_type_by
{
        typedef {signature-compatible with std::pair} type;
};

\endcode

See also member_at, pair_by().
\ingroup relation_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Implementation of pair type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    pair_type_by,
    left_pair,
    right_pair
)

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_TYPE_HPP


/* pair_type_by.hpp
lOIHWg8Zo10+TwnSNUGDwZsiOQf1u6PhbTS0gW55KgTCCKVGTRguWfwIwxsQeKUd/omTnhFcvgqH/3FzCt3oIWnhl1C6ca67bkYH2F/RBwW3Bs6Zwu5LPg7VbMlWw8kbGE4F7HeFE0NJRl9ucPWzOoWvFtgKU4DCAkuRUUo60oKRgparKe48JTSdjrVFVa3D8WJwOR6++jPKARlx4BCyBbUVPGKWx63lgfQc6NatoXibP0KwhfvF3144/NK4wYggblBwC8wqdIJygybttRWUoOp9WmyWeBUM4QjkSKbF5mBwgl/wZtUkjDzlh2uPVRpXuCUEucLKIK7wUo0rXLEJ0UKlcnQHcoVgpTsX0+yzNoWjumdEDrGdooE0cuwumouCbauxhVF4V0MI8Ao0m0IXuqIk3x/FHHyxrEJI8GfMnq4C6Byzz3Cr0dzcftFcXUTqbDFccMHBJ3hCunrMgpNf6SgQo/aD5g0VO3XXopIDzKBwQqt5+mgh8IBc2fp7AG2CqoFMXmUmGiTEu1gLbQ15jjipXBPq8mRanu5CNq3xmjNwLv+QtPmtXY6+kv+zWuhat7Qapu31VpjcqY00HyqTPam+EadzJxdr4IkaGYYT1aASs8Yu71VZ3o86CoFhb3yCiFy1gcg9qXdBNvYTHD245w7Ya0OxkeraUPGWc1HtYPEQKHn3x2HSI0tVqLz+Nm4Ln/99zOd//EzbwnfL
*/