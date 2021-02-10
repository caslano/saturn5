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
PY7BDoIwEETv/Yq5eaIJamLCzXjx4En4gUoX2oi0dpcQ/t6CCdedN2/2Eca+ggwcDfMcklV3GmKF5lFjP12tJVvhoo+lPqubEepDWrYazCROFUWhapK9gS4kTEyYvTiIo823ojSKb434MOJD4oIFR2p958lucFZl60rKEknjSd/JJ+IsMYItzN4EM3DAi8AkWqnGeYYNxONBkB94/4fX0VKftPoBUEsDBAoAAAAIAC1nSlIPo6xVrwAAAPMAAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdGxzdXNlci5kVVQFAAG2SCRgJY29CgIxEIT7fYrprC7gDwiHCGJjcZX6AsGsJngmZ3YP8e1NYrezM/PNkOKjh44yC2c65CJ20b54Tycepx7X4YJqoT7p4By7HluzWpoNHa3yI+Vv68PO6qnrOrqwtkpt4J5yFfgE9VDPDVijHDXcrIYU8WL1yUEmvoV7YNfCBVWoNanfiQ3O/J5DZikQq2jmZEU+KTvYURKCQFgN0dWX0yWWuFAU//kfr8NLszb0A1BLAwQKAAAACAAtZ0pSM1uGbPIAAABvAQAAJwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Rsc3YxLjAuZFVUBQAB
*/