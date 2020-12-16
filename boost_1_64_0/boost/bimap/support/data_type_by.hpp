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
+F04Fb4PN8O/wFvhh/C2sP26/WaVb2zJz55IL83PRK2HLWA/mK7tbGs4A7aBq2BbuAaOgZ+BmXAr7AR3ws5wj7q/BbvBA7AHfB321nUi+2j9O0Pr3UCYC8+C7JNwA+BwOBKOgKPgSHgRHAMvge3h5TALLoEd4FI4GK6AQ7S+9oPrYE94LxwFH4HnwS/D0fBpmKrreY/Revam0W8jOEfzrSNC2ZWto45P6arlsRscA/PgWDhex1ucofWrH6yGZ8IVenw9HAA/BQfperJnwU1wsK6/OwTWw6HwaxruZTgcvgZHwD/AkfAYPAfmuLoc2AWOhoMcHU8Bx8ELoTcHnH7z6HtqYSNzwJltTfOX10R/BU30V3ocf/tkTriTM95iX/6pG3MRH28RH2/x/zTe4hDjKI4iGTuZBw4Zj5Qha5EtyB7kEHIUydjF+pm74uMu4lt8i2/xLb7Ft/j2T/bOPT6K4g7ge3lAQgKEEAIJAcJLEIKEh4iAGkERkEJ4qKlWk0ASEgnJmQeioAakihU1tajUUosVBVurqLTFVjH10cZWLSq1WLXFRysqraiI2FLb7/7ud7N7uduQINr+cZvPL9+b3ZnZee/uzPxmokf0iB7R4///+Erm/7Mk0bGa/z/b7P8nYx9y5CHdlTcNsDumZJzStTpTYEG/Lmb9JVkfyVnPT+wfb8YucR+ynt/jYvZZwT3oZmJnDuFI7uqMX54bsj9a+9b6C6zbFL5m03qdE9+IDFTegt2d4fEzC9UtuKxQ93zSvcI0rho3dXucmetzUMwXWxfpvNS4FF2fCm/MXA3jbqSZW/gfMRdbF/Bf51EYdzrly8yj+EzsLrLmyFxDnY+kaR5pnrBvjcyVtc7A59D9y5w5PwPFzinMhOpj5g2myLnTKAu9ZW7sOuzFkYbzZA7r8cnxCcmxI5Pj4z3mxor9HOzPl/3v8pJjU8L3v2trnn7HlafpIXoPTtpm6lwenevhpF2LdRXXUUml7qhuRC6yAf8b17QsBxSB4pLCktKy4vrKusIyag1WPcv9D8X9QFM28M/oQ7DfHkeZv7iuHHNgjtYDcr2jKRM/E3OaUwcyj67M22to3St+0c+cErrmYEMHXb+Hi31gP3gHbvd4xN0rzhpHdTfEzKHseJ1tTvRpnPktPmgcg/azjS6CJfaTfM787JpSaPb47C7XY3x2nfBL2EurihdUslgc+VtrmbS8WuzlqNlnNYs5w+pLSVsfx33j6b+3y2FcdnKnjknJSdPYhLJvvNViPUSJ50ZnbUWTt73Fv3cDc9XUzzjCU2D72WNlJ6edCp1L/V4GY7PIn5H3ugXu8U7Gkec32fPU3rhO56lVleh829B81rlqupdjIJ3Ja9Oez9S1+K7Wcn4Fsgn3/m+F5TUTnJw81jwwOii3iP0LZV3J+dpur+5A/PH/fJlPPtdqOfcvOI/9g3bOMf79t8zcvJD5ocm63t5spLvyYsKafb0TF3kqaVmdHVwX0JWH48TueFN2cRvyXKrCbNaZ1by8J/WIz56QuTSzg2sGtpgjmK1dml3VURdks93muMOvTx1tz7StNvHQcKobfErVeYDhzxfHjjxLOoQ9S/S5Yey1eS3BOSZ+zjqJhCGsHe4FuW+kdtiUz62J4WvvbhnA+bA0qSpeUuqZHthv33q7ThxC28ZpncLXdLwXu01h4fHXL2AF5sLFpZe1kk+4a986je5wucv+TtWDSMPPXjAR1gzgvCtcujSs5PduKRPuMJowqZu+Zl76P8T8iXW2PZMdcdpt0txpt9Vdb6Mj9r6Y37GmE87XEK1zYW1H/Frb3iuMeyZZjyH2e8RM0jmfOF2QSZ43bGdH4B40xj0Sw+qdtqU=
*/