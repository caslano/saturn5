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
THSkiZw0EeSdkntIFybzhNowpyLTi4TPGEyWgMIf9ONM6Bv4nDNMDq4ZzpOExOMg8MMIgiHCoMgg6HIZKxYNMEhAa+FWc+rf0Ma6hdwxXbfMxP1ONRMhLJG1nKaen0AjutaVIXPqURwYxm6JBjBSAL0wg0BqIDqbIhOIMZIuDQ6kvWE++A6Vmklq0ABVEQSJHrmeeXJFfJOpAGb9DfT5+C3c3ws1eQsTG08AIXASQWrLSQa0
*/