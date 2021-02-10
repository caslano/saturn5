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
ZvNVuhgvZw9/jKkpG4GlZJXz2MDJHBjnxAs7v0FqW5SQhtw4D5oVAn6C0lhP2XRVoLhxSsVaakZiclQADJIGMIneSJ2pigsYOM+l6eV3ZyaS01FTaI6k9qgcqds7I3kn+hpB4Apd8rit3zLDSdgOPoTXcTr7fBvhNyxzzLIcnNRb1Gxgim5G4TmgceltczTWAvZWejyZKE6yhxNlbMGwKFqfZstVfz5brPrD0Qi7tERlCRw92Wn+5B/yK7kmarCXSoG3B2pljRkfU1GWJoS61rSslpsTdofnvM7/PR3TPgg6M1rTpenNMRuFBBKk/4ZbQ6jCYyUzps4GSFE4AqAGVJiHsqcOD52HbpjnhzNTyspSaN6ePj481Oz/92qJF4YCFj2UQv/t21/61ze/9q7wd93qhOmEumo0wdwhlVr6doeGKjdtMnfgawA9uTjh8Q4JH+N/ijYOegzxF0Nwi6HV3GBnTFt1/FFNpyx4pZAcjrQC/SAvpvbs4CBTgumqPDb2HLz+0IQBfGsqrxu8sUKkTKl2zT0iaI+XE7RR+h2kcRt9i/4CUEsDBAoAAAAIAC1nSlIvTQ4yrwsAACYkAAAgAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9ydHNwLmNVVAUAAbZIJGC9
*/