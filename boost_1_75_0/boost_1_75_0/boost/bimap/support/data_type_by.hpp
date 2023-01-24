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
QB2QRtwtedqD/v50xgrVnSD27YTBW0Al2h+DWYH7RMCeg4Rk/BFSQB+hD+AJSXC3R4DIxcijpoi0pBPZQ4ONyihTG6pCZxt0Qtr/6nqCG6D24NlAwOH7mwmorsgRKbwc0eiurObkaaqm1gNXg4suRLNX3IsO3zGcwQmNFiEs5ByLsKCJRfCagxch5O3/eBFuNstFGHu68SLkMQhmUVPqtPvgO7COJFf8T8z8tlPBM3/kv5n56cHVFNPoIF018oCytiZ9yWAQYXdvAO1JjxKPU2w6B48jllMglE51S4iLaSFaIS7mhTLWLa8nsD+0nt4PrFdZnv3/yMwPc+aPOfMGzvzuemnXQTp74P6j9ApIUnxZVhSqCshKZEcErqjFYxa2eYxRRiwWGANcIoLPa3mr0AlYGe8lOgP28aI7xSCepQ1aC0jDVpASKs3wyboi1T8hOkUwyPliZpxe8X9yBDRJE+TfK3c0CiW4pTHMte5yZCZGB5O2nKBJBBPTQjoR+EHzrysj0pShhTNGzsED94lij/d/A/Y4Hv493kl1ktuDs+E2b0fGIrI6+JLi24XelD3sIlyMd9JJKwbBycMmQzV7lh2a45gB3IEs3Ph4sVLm4t2v6XEXIpOYDffSiJOOKHYnnfA8rNIkl4+Ups6y1+m/ls5BZKJCFghO6WOZbBmyY5NBGumYBd0UpCJAedN8N0S4vIkQKZryeIeJH2ao
*/