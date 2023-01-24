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
rfddSpb7+P24noHW49dx1MDwRg1IxTJFaRqmhzCEZRi+I16yhH7/knw59n/k2ooSb+t975KurdqEt323u8u/2Z2McarycZ85uVEuY5yKY2SdvJzHODlR9zvtG/VJ0K8T3PN6vQ3dWmav840tPkxBkjGq3sQLrZduWt2o/rOei+lrDN1kw4XvgsZVvlBv67gvXvJnIwIubPu0Ypsfe+28s93H+XXNmPUZE/84VmXLT/s9Bz+dkji9x4UHUyremt4oKK7j2Ymj0vqpmUNOthdG5e/xjcqcVzC5c7247zdWL9KlYo9SD/X9pafPn+R8kGz/zju2UvGkE+e3Z/AlJixc6u31+6xO015GLvrucdmuDb8qsaSCmba9RsmxZZkxFR5fnHiu8mZt2TaPNheC1t7/6um3F1++kNusvvVoY4e2Ty43WFj/k8Qev9y+svZhv8quvhHs7s1tDl+L2NygZ7P+4h97bi0s3WDGZ/U6kYPOCE2n5WOcKqBHypKS6MsK1Vx9iJe7J+LXzc3DxYVUsDYWcy3t6le+bbHHn9Tanj354Cdf6ue+jt65PKK/PYAVijs5vXV1dXH2SCGVrNdVXf1J6RS/45/kHzuzpXS001GxHlu69M6wBV6VSJS1QyXXNqQVaZnePL3ZhCbxycmJSv36PZIS6vV7N4r1egzoVz/xsz7W1vqJSQPiBvdIHlQfg4xARBgiArsSqS5L12UQ
*/