// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_STACK_HPP
#define BOOST_ASSIGN_STD_STACK_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <stack>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V,C> >, V >
    operator+=( std::stack<V,C>& c, V2 v )
    {
       return push( c )( v );
    }

#else

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V, C> >, V >
    operator+=(std::stack<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

#endif
}
}

#endif

/* stack.hpp
KArGQYdxLTB/2dLi2sboxRabqEtXAjB1gA27u3U+QpwJn4pHw350v2gW6xLY1SoiNPjL4yiglig4ym7khp3z4Yljz8iPNvjt0u3GXLhHDhzjlpKEn6QOCNKZu+XjqW+OkrL8JAU6gRd2Z4ObEzLvoMIizgcco7fCzVnuF4Da25Rm8sq3zLojbnsnFUT9zq7zQf3Fs3rMGUSj05PM1XsxS30gB/TCJHPf0ItOaK5zY3NifSwMuBUgJrI4vWkX2LPMddViLBQPV2V5PxG88sEso2bcZ9Qdg8czXrO2KxEZ01QvB2KSPofJnW7meqN0qfdHqJJIRIZUpjxBaT8ngphdZOg6BOhyWdK18/7SJnklto1YK9wSUIdwC497PD2MPeorIYkQ38QXY2HBSExTZqwCls7CDuvobaSPLIyEioBnTofN+KYM5OSPyK9iDwSQ73AZRy/PZl72O/Xs6jrJ+HypmCgfsgR9JkucxyeSAkkeybBFJ9/Gwiw++ioda8XD/CUmYbDuUcRMo/KotDLaXsnDEzR3/rImu6eGTafzmEBzScfHOPRVPgac8vF+Kw==
*/