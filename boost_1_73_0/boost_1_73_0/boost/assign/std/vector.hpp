// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_VECTOR_HPP
#define BOOST_ASSIGN_STD_VECTOR_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <vector>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::vector<V,A> >, V > 
    operator+=( std::vector<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::vector<V, A> >, V >
    operator+=( std::vector<V, A>& c, V2&& v )
    {
        return push_back( c )( std::forward<V2>(v) );
    }

#endif
}
}

#endif

/* vector.hpp
13blWuyNGNIVSLoyy1+/q10bvRFDuoLA5SFdgcXDRmtXgTdiSFcw6bo09sir2nXRGzGkK4R07Zq/t6F2/eGNGNIVSrraPYmvql2uPoghXTWUS7yyDwyQT3SIV20fxJCumqRr5tS429rVygcxpKsWma/kuPxS7errgxjSVZt0PZjwZV3tyvBBDOmqQ7pOjxq+S7tyfRBDusJI15NqGT9r1wc+iCFddf9P11EfxJCueqRrU+9M1FXigxjSFQ6uMOk=
*/