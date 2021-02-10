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
fZOCtFCk4vYD0mR2N5hmlmTS0r83WcXXueeeuXsOYwfx6fLUrtWW/NzhmAj9/qtewBFjJC0U1SGysGGfupqqN2vJdnhtX57bldoUZOR4W1yqaRr1ztFQgsnRQxj5V4oLxeQ44E/uqxrXiQIMh0BGXBgrrxHpzLKUVKJYeq1SuwEy0T9aPC7BciBcnUycpeIPhSlnnhdg0gmBQcNQGi36EikXjM+2rPs87jZNTvXn3bbvD4/re0jUIQ1lZvn3URfIpBfvstlVmyDleeYoZHG6QXu/5CdtvinYUvwBUEsDBAoAAAAIAC1nSlKqZtlKywAAACsBAAAlAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdGxzdjEuZFVUBQABtkgkYF2OsW7DMAxEd34Ff8BGnW7aii4dXKCo3e5CTEgCFDEl6ST9+9JOpi48grjHuymzWMABRm4poFW9DDDHpAG/SbRwU/gQNj5y9ds0jfCyLLQEeF+Nbr7cmX546OGhz/BJP2sRcmoeJ5iIuliVA2az8+bf9ABvVM8Bv5Q2l3NPyIJJKBoJvPpMLL97CHRdBzPVqnhcpaIxro5Fw0pRbePxcu+MQ3/Da6aGzXkr0UpLeC2WMaLQiW2PAyVxosc5+5cTxab/vuxt
*/