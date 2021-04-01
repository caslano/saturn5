// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_LIST_HPP
#define BOOST_ASSIGN_STD_LIST_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <list>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::list<V,A> >, V >
    operator+=( std::list<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::list<V, A> >, V >
    operator+=(std::list<V, A>& c, V2&& v)
    {
        return push_back(c)(boost::forward<V2>(v));
    }

#endif

}
}

#endif

/* list.hpp
O4HEBJlsY+BxdwuPKWEqIfc9+XxIYhPbfCnsvn44I8nmsxD2XA10jdKdxJWHrD7gZ4poKamf56G3lq5AK0ZZ3jW7jxaVC+wdLyt+gXjoMuneZxj34CIVk8GfoLYWfQlwbCoQ4TjvJFw4xpjKNzl6XPx5bd47DTsgE+yxDSIXDCTqkW1zoNgMv4Bnz3BbTNyetLtg0uCK3KIuCxajI1M03tuq0hXzNf1v8bNaNdWl+rVX7oZCXXAQHY5FUA7b4NhUa5MIaSK8+HbeXs6PE5lovIZ7riNLRvAf9gQl5/+QXB0r2efEScw64FsR7swqqkWsiSMjr4SRhLeu7V54TVxaT+Yu0iqQ91+TCgscpajK7bNYiXhWuOur4G5+osIGXaytSIK/YsAe9f5TcZMedez0DJ/hZLlCVOaMaUKawnqBSn3OG97VAtYZT0TxWE8BtcebsE3QrFfOg/o80XnpA/NgFtyeLAQpQnpDSy8LNBS3GIyp2gQSt7DQkm4vj1yjArfOpu3KNrFUiNuObohNE7u8zf2PFR1KUuVRZpK/T0YlTZCJFHer2ewLULhdYw==
*/