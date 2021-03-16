//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP
#define BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

#include <boost/assert.hpp>

#if defined(BOOST_DISABLE_ASSERTS) || defined(NDEBUG)
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    function
#else
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    BOOST_ASSERT(function == CL_SUCCESS)
#endif

#endif // BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

/* assert_cl_success.hpp
VdjEkQJXZcFHx9KcKlPY16Pt+Tqhv21jFDZW/AQff3M/Fx/96uqntyjsJz8ROCt7Pot2fATMOy6BK7Pgo/BmnVthSf3Vc6vxS/sby4E5rQqc1XgLQ77FVQrbWSNwBRZ8JWjvIq/C1vgFrsSCj8bblwGF3RBK91tOe4bgC4F5OyJwVuMtDLv/XyyWx0y3H28HYZhzfqawcEzgPBZ8UbTjh1kKC7QK3BUWfDdB8HCbwhZ1CdytFnz0W/SHbldY80I=
*/