// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/data_type_by.hpp
/// \brief Metafunction to access the data types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_DATA_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_DATA_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::data_type_by

\brief Metafunction to obtain the data type of one of the sides in a bimap

The tag parameter can be either a user defined tag or \c member_at::{side}.
This is the actual data type stored in the bimap.
\code

template< class Tag, class Bimap >
struct data_type_by
{
    typedef typename Bimap::{side}_data_type type;
};

\endcode

The following holds:

\code

BOOST_STATIC_ASSERT
(
    is_same< data_type_by< member_at::left, bimap<A,B> >::type, A >::value
)

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace support {

// Implementation of data type of metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    data_type_by,
    left_data_type,
    right_data_type
)

} // namespace support
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_DATA_TYPE_BY_HPP


/* data_type_by.hpp
8pibBd8goRWz9Ynw0Ejo6UCS5+w7P0vfJjYML/AtnRsaLW9gUiif3oDxKZHs/JR/vLDts6musyzapaHggYwtCbq9ew8G+F4DOm4Elw4fWG4Nza2PrYlr5OANISRN6qMHigLUshSbT50cAFMdDxyPPTeB+uRp49ASpeGZWcsXn0SunaH6AweXBJQbmwljUbCfNWhyGlFi7MhvkuUeB45n9d82nJ3439bXAyyypDnp3WT9itQzU4ETyBLaqP45e3ca+j4WLwjFk6m3KwA6d4Qj0VCkP1aTfR/vVFEWeswZSCdy1iW2BQfqFDEqW4uftyIHWN+gbmhTg6fn+UNi/brim607CDOM9Q4KsqmJFfcvY4pgssZ8hG6bG8PiidkFT+AYw7BqHADBeKDxdVI37Td4TKM6MwVfw4rNnDA5rPi5Epg/LPFPGzKX2HcBVa6kOgd714P7cYSFpZg8YmIupxVb7qcXfcbtXen8bma7gUAmkkeCUAxVABWAIYu0JNqexPDYLrF5DagLpmEr6FUMnaZ4zfUV/KTYxVDVexiwdRJ2P7uR/QSnfXwqkK09FA==
*/