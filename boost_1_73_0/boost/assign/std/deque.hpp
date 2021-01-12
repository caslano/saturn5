// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_DEQUE_HPP
#define BOOST_ASSIGN_STD_DEQUE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <deque>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::deque<V,A> >, V > 
    operator+=( std::deque<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }

#else

    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< std::deque<V, A> >, V >
    operator+=(std::deque<V, A>& c, V2&& v)
    {
        return push_back(c)(boost::forward<V2>(v));
    }

#endif

}
}

#endif

/* deque.hpp
P9arub/8Y/Hj8N740dM/fpz7WgJ+7OqLH7/0TBw/Pq/wo5qJt7xDFPlfQJBz/zMIUtXSc+cX+sWRv3/1IziSuJHo68spMfQlqFJhsY0Ki932SAIW2ypYbN+zCVhsoGCxyldNLPZDhcWGpCgs9oMELBYdICP5hBrJ9bhpyuUjjaf3wmKX/AMs9tYB86u3Kyy23sRi98WxmJ6Axb6dYyKRvXEsRn71E6GyT6WYqOwehcruU5Ve
*/