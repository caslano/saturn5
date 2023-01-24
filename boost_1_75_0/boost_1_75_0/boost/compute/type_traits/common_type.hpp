//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_COMMON_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_COMMON_TYPE_HPP

#include <boost/type_traits/common_type.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, size) \
    template<> \
    struct common_type<BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size), \
                       BOOST_COMPUTE_MAKE_SCALAR_TYPE(scalar)> \
    { \
        typedef BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size) type; \
    }; \
    template<> \
    struct common_type<BOOST_COMPUTE_MAKE_SCALAR_TYPE(scalar), \
                       BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size)> \
    { \
        typedef BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(scalar) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 2) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 4) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 8) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 16) \

BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(char)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(uchar)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(short)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(ushort)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(int)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(uint)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(long)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(ulong)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(float)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(double)

} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_COMMON_TYPE_HPP

/* common_type.hpp
k+x6clVCxfidW1WQZ7r8D8QzXUkX/Usa22rCSR9VNVWdyp4AzdtHfzq7iub1m1R5gsrP/lBej7vTWJWHCBFMZ4yAZ9bj1B/K3Z5yrgur+Xb0Mt1qrwovdRaHCHDWUViPk7wezXdPou8myt9Nqqj6S8FhC+nmY1TcMe1y/2cc9lkCfoalv2RVzD/9BPNPlUl+7wLvPTMXN+uMrlg3u+S9W6hyD793e8V77+nJyveOyns/pIrsn2cq3rucef/MBuL/1ylI+eirVRVVj9I77TVUSVAB3dkZfpU2x1doxdWfuN4yVfzNPFXWVKGtZ1QFv7lZF01be+ao1m2XqtbxSdWa2apaq7Yos7L4+1fTa6tD9P0bqPLXVPzoZreZ3qrQMkNc44+qe62sPeqk7Re0daFaZbdaqqrBxQuzCS84qoHWYQOtw4Z03XRD5xzVOD6uGjOfVY1V69W847XTc6dqjs7hOX6fPvVP1MDcbB1VSSpLqLDsCdF8zMieLbrcrd3P0pTfFI7do0vWT+3zbKugbyZ+siM4/1rmX3vzcYEOjs0qGpcO2mfbFtOea6f9dppKVrWp2mm07Vb6+Tx33d9JlaNUnqVC694dhZ2G0dgNdsMoNsDrPeF9YuqcPw+rc8P1r4f0bXaTM2q3hXN2PmStJHSctOuD60eFuL01Ia+9daFgewn5gacJG17FbeMy+kmHy9MMUWWl+3uwU86oyukd
*/