///////////////////////////////////////////////////////////////////////////////
/// \file as_lvalue.hpp
/// Contains definition the as_lvalue() functions.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007
#define BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007

#include <boost/proto/proto_fwd.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        BOOST_FORCEINLINE
        T &as_lvalue(T &t)
        {
            return t;
        }

        template<typename T>
        BOOST_FORCEINLINE
        T const &as_lvalue(T const &t)
        {
            return t;
        }
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* as_lvalue.hpp
t6jP+5KB6bXiyju57B5qMbYk5h3umqNvb2hnDhMGyvrQer5WqbZkN1C+7iOz4WjZUfkunLa79txQz+vopnH07kO2+Gp0IPIgyeIqY3/ZOLV47PLwi4B77sUFEv3uAbPHyF+e7KxHwLtvqS28XIY3Jwse1XlYwOinLZ5FbiWZFZvgrL3/o8v74UT/V4wPPw7R/xLnGy3yGm/sGQ3qHgf67pQqIFiDvDOF3r9ZSe/VXUtUX29dXzRexyoTn9HMHts=
*/