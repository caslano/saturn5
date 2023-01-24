// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_SLIST_HPP
#define BOOST_ASSIGN_STD_SLIST_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_SLIST

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/move/utility.hpp>
#ifdef BOOST_SLIST_HEADER
# include BOOST_SLIST_HEADER
#else
# include <slist>
#endif

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< BOOST_STD_EXTENSION_NAMESPACE::slist<V,A> >, V >
    operator+=( BOOST_STD_EXTENSION_NAMESPACE::slist<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }
#else
    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< BOOST_STD_EXTENSION_NAMESPACE::slist<V,A> >, V >
    operator+=( BOOST_STD_EXTENSION_NAMESPACE::slist<V,A>& c, V2&& v )
    {
        return push_back( c )( boost::forward<V2>(v) );
    }

#endif
}
}

#endif // BOOST_HAS_SLIST

#endif 

/* slist.hpp
Mq+ftlpps+C0U+lPuk9pMATqym0P0GvFO/Riq5ez0Yv+V/TqasOCV5GZ1SfPelQnzqlsaReMBV3WkngfbSzyfqjouqS2I4+DPuSx9a3OgY0wdo6vPO8Z2GBwcrz9pSk2ShEisTQDUGIZoBRT+JKxXv5/KfH+O6jZnNQhpiyJ219hQWxgYMP5QyISjPLnB5w4/vD2Z2/mlvbNu6okjy23vX46c/ftlQMNW1f9KYm6xLf3mnxsQ2DzJwXxma1afrVy7/CWAxc28/j5dbWr3wyedGrtoMajL3x56fHeR8KKozFNLm9cr+cFx88tt3pl0qCoh2Vm33jNz05KPz+ka8WhTcaOl0rnDOrktqt3269Wbu5T/+ey3m9mJte8PqR+5C9+pMPzM191f338aNemdPjOGiVvhJBTSTV9g6v8ILbW0xk97eRSyX18TOuoMcG13JjtLS+06XHzTN3uD5voNzM9qT+aLl18ulNq9Yj8EWtbPGp6StSkxVuGxqwss/ir459Mj9K+yyzS1eXsO6jpgh7pSIpbqVfSEkJuxAW/PsKef9RB3rZwslST0wRSwr1IoWEo5eTqZh8YdPB+m7N1lNen6dZnq0+Zc21erJpBD1il7cmtS8q+38nP2dWnohcVQQ2mulONqAZ/AbdimWNiQ6JqzP2tWslXta55RczpcGMFCXeAW3PSjDRJb5TeYIL5n4Pb+7eTENoWKtnAFvkR
*/