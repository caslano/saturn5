// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/value_type_by.hpp
/// \brief Metafunction to access the value types (std::pair compatibles) of a bimap

#ifndef BOOST_BIMAP_SUPPORT_VALUE_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_VALUE_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::value_type_by

\brief Metafunction to obtain the value type of a bimap indexed by one of the sides.

The tag parameter can be either a user defined tag or \c member_at::{side}.
The returned type is signature-compatible with std::pair.

\code

template< class Tag, class Bimap >
struct value_type_by
{
    typedef typename Bimap::{side}_value_type type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace support {

// Implementation of value type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    value_type_by,
    left_value_type,
    right_value_type
)



} // namespace support
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_VALUE_TYPE_BY_HPP


/* value_type_by.hpp
BSJSD62i3L09BI1Vj+fp7i1ArRSpixx8s8gneUM3Cb9ApBLvUZ8G4OwWR0E0rlrm+8S9w158osRK9RR9TpTvwsN4SkBeUQ9569dVu49cd6uo1UoL0RcfERwQvHb76EuhKgPv44HoDRbJdUr9Ykhv0TlvzL6817U+BWBlF2Z+P4W8a+vgdMtiQWcPylzlTQUQ9jVd1nrqtT0L3INJTD/w/qRx92ojIpZDS3dnEQsanNQcjWyfAtXjrFEwNsWqGTiZAFl7JbFOIidZA5qFUHBwZvxCC3f//C4pUo0woi/gvQoy1xAeAxdLxHfn0hCOf1s5LVJrA88zqp7XN+98rGzMXkmBLgd3j5mLPUkUccSW/63YUNjyBY32LVGHr31aKBjLcXKShopc/lmk41+PH38skxELD1HqCLYR/Mk7EDQdOsIN/BBkVDJ+rgpnxce1Se2ijGzmVg2w8aCOd5jeT1jN/jFLcAapkpl6B+JL42BywOjrqpfiFSCvwDcQoXRO8IkrMIp8LA2cxJH9gZsoB4IjCKEfH+PEJ/HxvF+0NPyLVliRY6cmAm+c9cqztQ==
*/