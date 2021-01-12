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
iIfWI5TrXAnspcRDl6iccpCTFznh4WvejtL097EDY5yZ8cGB0hG86tORKoabJ9jktM55luBYls+rUh8Vz/dcqcM0ehjQ3YkJrdxm9rK0SGl+hY8qa3rXOapqPpx/wyMIMmbxkpWh0gn6rnMSsmi2KjWHyKxrKllwuf6Lc2IF/4AfFPJaDH2yeKjGvCJikIz2YuIRS1QhdeuUk7DEYqrlALT4JFv7kIXP9+C3XJ8YTz0uBoIs
*/