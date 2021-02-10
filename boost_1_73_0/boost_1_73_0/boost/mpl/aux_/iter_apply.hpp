
#ifndef BOOST_MPL_ITER_APPLY_HPP_INCLUDED
#define BOOST_MPL_ITER_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename F
    , typename Iterator
    >
struct iter_apply1
    : apply1< F,typename deref<Iterator>::type >
{
};

template<
      typename F
    , typename Iterator1
    , typename Iterator2
    >
struct iter_apply2
    : apply2<
          F
        , typename deref<Iterator1>::type
        , typename deref<Iterator2>::type
        >
{
};

}}}

#endif // BOOST_MPL_ITER_APPLY_HPP_INCLUDED

/* iter_apply.hpp
Gv8iZc9ppAwv+lAWWVV/MBnuKLLcmcFHsJB93Ag8nVpCcWi2Qix6w+TbAYp3YFvGBNwhFEnobIZPxAhV7ogrZfYjWxwc7Tg369wW82ujfwX16UP8AFBLAwQKAAAACAAtZ0pSuxIaMpsDAAD3BgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMjBVVAUAAbZIJGCdVVFv2zYQftevuKlLmwCxaSmOE7uyiyJuU29JEyTesqcNtHSyiEikSlK1/bLfvqMsWQk2YEABQxKPx+++++6OjiwaG3ODMy8SMlX0esbdRunEzLxbtDwX8tn7slze1w+4/rT0Ita5RGx/ynvjvYFH1N9R94xI0Is0lvmOHBJuOUgVZxg/T/0dGn9WQ7GgH0A4GMDdr96cW5zAEyanZIFfKkmvIIRgOBmOJ+Ryfbv09uATcIR7pl6wlD+jd6WkRWl7NyjXNpvA+ciZJMZWKDmBOFemc1ruSnQYW8syW+QH+1yYUhmxP5KKHCUvcOoe4SAcvIc449qgnaaVlLv3oErnOTVWc7lG77Oz9jLkyQQoQ/p5LicONuMWTKaqPCENLKwQEswFcccEUq0K4BJqYTUaVemYhGNOMadso2At7VUuHM29tHG9IJe9DDMvs7akA+0y
*/