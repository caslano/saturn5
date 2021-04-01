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
AFVQr8dL2vYcd+pebUFnqe+iPn9OrKwEnx4G0e6P93hHWeluoO9GkkUy6HAh3uMVoEfGm1fG06BktU+qmbrws+2AhalX5Azq6Ht/x9ulzSL7ntxpzo8e+jV2eInqwz9grw/wj/5DVHQJlRcf9pLJuzEJom9Rl7JolrKr/ol8rHY5GL7jC/JtDYYWFp4F5NbP/TPyjSwR+X64FROMMdKF8lbrn9GdY2ucP6qETl1qKYhFcAGach5r//oFB+yHt873sSFnWb9NDZox1x5zF2MlVX5S5LztsDY5ilURqY9Nlf7WV6xBhfqtgTCc/11aSFkRmW+0WB4Up+Fy6Q90S98cMec7dy+Otl2mcnFWQzvqJSRveZIdsSxtijITONNCyHC/e6S+6jTPPJ+1N6OfGXAGlgAA5b29o+EqmZ1Gnu3USsDgiKdfWG7e3EnpbFr0N31JeqOjbijsT0WFauvDPUjBNmmE1BXlgNkjt3XpjLqm2qaczgFK2rQS12aBMXxarbDvL/UHT+rDdowHzXx9lgB6GyGTruqQ9u86zs54rIht0dnsu5s49pYZ2iU83A==
*/