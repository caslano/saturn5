// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/map_type_by.hpp
/// \brief Metafunction to access the map view types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::map_type_by

\brief Metafunction to obtain the map view type of a bimap indexed by one of the sides.

The tag parameter can be either a user defined tag or \c member_at::{side}.
The returned type is signature-compatible with std::pair.

\code

template< class Tag, class Bimap >
struct map_type_by
{
    typedef typename Bimap::{side}_map_type type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace support {

// Implementation of map type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    map_type_by,
    left_map,
    right_map
)



} // namespace support
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP


/* map_type_by.hpp
+11+epW4z90wjD2loGg9t/NJis6nEEUQ5whvFNSqW/J+e4oYpAoerqRa7+GobBvWl6CnCOsp0TexUTyRIrGtT5tt+V/FR9urNo4mAsdWG2NOicZdLMhDOUhBpNCDm9x7MsqLOMWhzz99IkDpouRwLX7LOobaNS1n1FWvRsfLKPDcNDv2wkBE2YSmTw6PPvzpPX592zzmHDjG5qu8Q+ERRxvlyW8f/y5S7pMhrxZgszwRp16n1+u9b8qLlcTDQf1Hw5nYY03TbXsVKHduKiacLHLncA6v57wyxxYZr3JbsdGFjJL4n8LL4EHcpXgc+AhNdltzlmWL9GO3ex9ks+Vdx4vn3VPX+3m5OD/XMO92KV8XYlDGBlsLpwLKzZQA4erPnaMe3WLfJ4Ju12+jfE2OszcT3s8Iy3xOp5KQjt4MO4auQv6nMDxqwZs3UP77oSVjsgqHzFscIb1Pq9zFvCqU62G9m8nt7UEtpJ/Pq+BRXVxp/yu0MkU+1c4F49S9R48A+pFLxk9l8H1iv5bLC/Xq3SV+aFE8BU7SwO+uEumsLdSr0FbyE7UbtuTLA5FUEitCJNx5s5oJm/RiIou9ONwhwBdTdxlmK0Eftze+q6X6L+58EQqi4w4BA/Lwr0edw+/+0ul1jrqsTpfNO+SY
*/