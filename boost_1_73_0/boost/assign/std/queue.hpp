// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_QUEUE_HPP
#define BOOST_ASSIGN_STD_QUEUE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <queue>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::queue<V,C> >, V >
    operator+=( std::queue<V,C>& c, V2 v )
    {
        return push( c )( v );
    }
    
    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::priority_queue<V,C> >, V >
    operator+=( std::priority_queue<V,C>& c, V2 v )
    {
        return push( c )( v );
    }

#else

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::queue<V, C> >, V >
    operator+=(std::queue<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::priority_queue<V, C> >, V >
    operator+=(std::priority_queue<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

#endif
}
}

#endif

/* queue.hpp
V/8WTuyxmzjxS4rd9YtGKrsa2HB3Yn12/yNsmNk/Ntz9EWzYfiZseGvUfjw0CdhwtmBDqQqgE7Bhs8KG2wxseLh2b1X1P40NHXYTG96o2N1F4dYPOAyPKzwY7gEOnCI4cNU1av76cHtc4cDHiQMF/31osrl8/ng29xsv9GVzsceRgAHXt8Ux4DMmo7volkP/Ourz3DkXv/9tNneR587P94v7Du/9KO5TiM5Egd+39MJLOWmC
*/