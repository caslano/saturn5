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
GHV3pgMZSsOFeDY6ojbRglSCOApW7xrPwMaFMJf25pn010oyn3XUCTu7HqvUhezFkvA7e4EEQvp5aTD+E/W7xJVfzRMZB259/hUK8dDFpJ4r8+q7/Re55MpxGh9A6WIpp8k/+FxGq/BFZWnPRtq+bJlmsFHi4zVHRnJmY7Eo/F/xRw/WbMhAeH+OaxG2Jc5QF/+ZHMSi29SZ6BvZ1bIbuVYaEFiIXZHw7fMABXW/cRvKWIIDND21O9OIs7bGQ8GtZ0msAT3JhK+QTrpY7kO6/R1r2rDD3DroPLz3Iae82hkby3YSaY/V5iuuul/BB9Ndp5IwOuc90qrtcpnYIb4XkvcKzhrnQGC0XbL4vbNuzsGD+nBvGd0ZbRARibv8VvVX83AFajHtWxey5xQ1WeSWNANp77koTnoPSAZecQw2zT86aPKpAaixnc3RiEtWi4YW2MO8zK1obCdy1lpTQaocuuNPh0w/QrWLTGTz6uRT3ub+f+kZu7l1YG4snOvkDng5MVKkCmYBk2v9f4bKj+B+rsPmQJ2sdg4t+xwIKuAxZkyPVps/HobMKxxtxw==
*/