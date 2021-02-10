
#ifndef BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/numeric_cast.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast1st_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >
    {
#else
    {
    typedef typename apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >::type type;
#endif
    };
};

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast2nd_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >
    {
#else
    {
        typedef typename apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >::type type;
#endif
    };
};

}}}

#endif // BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED

/* numeric_cast_utils.hpp
SaAJFmDlCKXTK7NVn3EBU3ydAXDkYZ5AOERzRkMXTTHnEkg0ynCwwFomE7OhakcaymU01CbEWXpKWTJFSokBF1DLtxnldCzSjUZPzR9lUkqZhoKEIm0tpqSABPkmVE9Mgl+R7WHGiTj1OU1/+pQ/SWtJ5yYJXeEVUPaXlDIcDtMmWIH3vg3MFSLDD72PPWMEB5PTfRni6HE/paQUy/M5gr+QxoTJLwDZJXsQtjXYJW4to20Cl1B98I1NiOODsd1B1vXHICMr6LasQdvqm2bZNKNbwzyLnmquWTG/Hve1tjnE5+WGuXHl5C0a369qTs09vUsKF34QbKEm4mPNTXaDmx5lbLGRRDvMiJMnRf6x5EnAYzTCTpL9G8CzqwrqEZtCcd4toUQVDhHzXU88UEPZv9QQtBDYDV0wC+U79kMiS5tHXKEAqn+HeZWVqKt+iINgcQiRjuE/GPFsXAwSN7jLnKcqh/69yoHeZz/8COqh31EP/e/VY7ew/4cKot9REP27FGTHmfGSKqInKlKlMwZZ/5iKPFZPuXv19DBl+otT9i+KaQtluUR/qv54C2GPyW7+ibK744J8gvTmEyWxPWJfv4mNyA+/n3hFO4A3snK9iQXoTSwZr1Lml9oOrdXxwDtUDnw5XXxqYEcNWM7G
*/