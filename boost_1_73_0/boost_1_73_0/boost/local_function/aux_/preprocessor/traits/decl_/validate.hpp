
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/validate_/this_count.hpp>
#include <boost/local_function/aux_/preprocessor/traits/decl_/validate_/return_count.hpp>

// PUBLIC //

// Validate params after they have been parsed.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE(decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_THIS_COUNT( \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_VALIDATE_RETURN_COUNT( \
        decl_traits \
    ))

#endif // #include guard


/* validate.hpp
DME8sq+LjRH3uYNWvw3vzs7ew1s4PTk9CWHAlUAJU4dqgeY+hPO0mvmc84eHrsVPIaADLrs11SwXFqzO3JobBBpLkaCymAK3kKJNjFjQi1DgcoRMSIR+fDUfjb+GsM5FknuSjS7B5rqUKeR8hWAwQbHacRTcONAZwYk8FdYRYemEVl3SRnBoltZzeHkurQa+4kLyBQlxB7lzhf0QRUlpJLmPUp3YKHncfjd3y/1O5mRiyTegCwdOQ2kxBB8ZwlKnIvM9JYQmi3Ihhc3DgxuSUmmkDViU0nMRTqDd2UaY1ukJfRgU5Fg431mtrJda53r5JJDy6Fmy0igSojxQUKopzSGU9FmZKrja+aNEndMqwS8ezcFvClqRGWj0pjCaNmDBrbAh3I5mF/H1DG57k0lvPJtD/AV647kn+zYaD+joBYkZwIfCoCVxA2JZSIFprfl6LQqaQiWyTBEaTmvJLLqy6OaNgBYyX1qqgjGIh9O6YExH8Xi6X73o3QzZyK8EgY9MNDElWq3QOOY0U+jW2vxoJTk30FmUWYYmBCt+InMgUd27vP3xb2Rm9PI/sSst0j0ukchVWbT8JK0FTVR0pyDq/GYUaNNBxblH0UvLX10mVKbdpqBjrAd0N32k/yqqsKekz+am4qf0wJtd5U1b
*/