
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
8TIOxR/Qgr9jDFYnD2OwJY7FbhiLg3EcmnE8jsAJOBon4SycjJ/iFDyKU/ESTsPrOB2zs74zsDDOQk+cjc3wI9nerJs8m8i+KsfDPAR720yrfOxH2BrdsQ32Ry8cgW/hHGyP95D9Qp45ZNlyHdGIsFvKu08Byhv7Yjnsh67YH2vie1gP/bAJDsDWOAi7YjD2whAciKEYjGE4Es04EYfidIzG2TgMV+JI3IijMAnHYF6lvLET
*/