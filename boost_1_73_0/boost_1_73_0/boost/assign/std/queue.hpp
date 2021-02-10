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
tkgkYE2Q0UrFMAyG7/sUeQA7FAVhdyKIB86FoF4fujVnK3TNSNPNvb3pdgQv2+T78idnSkMLEvPy0Nybd4xzC98Z4ev8WX+AGAZGJ8jmg0mop5jbWjUv3qNv4bl5fFLyVVsG4m13GWuteSPuMUNfOIIQlEMKC3IOlOAmj1UN64gJekoJewlpqP0OGCeSA8rIyjXGnBJQ9H+SDHS9DRiDPmap5tVl8NSXCZOg310x0goXSnG77D4dfme6ItDh6JagOSoUkkbIIYuC4HHG5GsYVcp45IihY8dbs5/IWl3VTu4HwtVsVNShnI7LKBpfC2Eq0/+lG/MLUEsDBAoAAAAIAC1nSlIJldzZ8wAAAG8BAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdGxzdjEuMS5kVVQFAAG2SCRgTZDNSsUwEIX3eYp5ABO8KAjdiSAKdyGo60uazG0DaaZMkta+vZP2Ci7n53znzJwpDR2UmJeTOak3jHMH3xnh6/zZOkAMA6MtyOqDqZCjmLs2Vc/eo+/gyTw8mnv1IisD8bazlNZavRI7zOAqRygE9YDCgpwDJbjBY0PDOmICRymhKyENbd8C40TlEGVk0Rml3hNQ9H+QDHS9GYxBirk08mozeHJ1wlTQ
*/