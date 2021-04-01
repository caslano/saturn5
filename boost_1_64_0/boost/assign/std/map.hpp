// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_MAP_HPP
#define BOOST_ASSIGN_STD_MAP_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <map>

namespace boost
{
namespace assign
{

    template< class K, class V, class C, class A, class P >
    inline list_inserter< assign_detail::call_insert< std::map<K,V,C,A> >, P >
    operator+=( std::map<K,V,C,A>& m, const P& p )
    {
        return insert( m )( p );
    }
    
    template< class K, class V, class C, class A, class P >
    inline list_inserter< assign_detail::call_insert< std::multimap<K,V,C,A> >, P >
    operator+=( std::multimap<K,V,C,A>& m, const P& p )
    {
        return insert( m )( p );
    }

}
}

#endif

/* map.hpp
2HuT99D+1caMuu/PKIceQp4tVwsnurLCwzmMzZz+uEmTapkAD6HWhNCJ8zQGTbzi+XM8dc+qgvZm/uUmEPZ8nipMuSc1p9m+L3Yq5W+Iceec8ID0phTga5sThX0YjdawEB6QrU9Qv/mcFZ/B5l39wUPXjH25pM51FVbYX4sTGITgjwr+gC8mW/l1JfcFrUIWVYD3b4z/uA0XnoDd1RzxftxhQdWiJ1aJjt5K7VTChrdCcm/QWsWxQ7ICimRes3ek6zdFhhTlzq794X3CbQNU7QaG8UlM19r6xD57nqc0T0vGBJhzusQUUd/6UhzjhOsvfjLdfvROCANx9tfzIVWCUHBVpAnMRPZMYp+nYdHDmjHy/BPEkuHQpwfHHwqOLu+vRTZjNgSPlobK91Joqe+DTl2gfUj9+rBBN+BxUk5wfFuj375hcQcJapZQUw4Kc7/jSykPix+o6cmHoMv+UbQKTtTz478Wz7HjmxDcy3Xpb60ujdrO+VgHgtEyCv69Y4AZEUtwQ4lX3CoiW8mYMOr+7wymSx0j828ue/MEu1ITEiICthrsDBE3iiAdCQ==
*/