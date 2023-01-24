
#ifndef BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
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

namespace boost { namespace mpl { namespace aux {

// hand-written version is more efficient than bind/lambda expression
template< typename Op >
struct fold_op
{
    template< typename T1, typename T2 > struct apply
    {
        typedef typename apply2<
              Op
            , T1
            , typename T2::type
            >::type type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

/* fold_op.hpp
O9ItxCb17EiKE6/NvTTF+ZcSujTE2hp10PavEZ45/PyjyeO/Jl4PqwdKCozgpeSL+GlpolqqxBKxRU5xJTvEzRTmeBJDWI9JVF1LJVqsA3FPnnGngl0Ym4YkxONQiCCtaossq8MG2MS9t8zIaSwOlMmrbmxOU+izApJ8AWRXql8gmnjFUaJhnuU0nrAIQWVzq7X9wwv95G45A1jYBYhon9vGaQarjkpNhtNPmCl5it913XS4NOCaZBri0hAmjkUlHtWFb0U26wUeEUIXaXQuGPZs5N8W6iFk9eziGJalpQpjGX82OFGK8p23nii1h6kI1A+QaxRxJtA3DBsR/vAvaSR3TypvCaY3b9+Y21EfpV8eypE/xMz3cDQGPNP+8UIxi66evUcLDjxH7taPfzyoCcXv2AdaPHqWkPXYZqVuJN+pqD1WqWd9aFSOohV8wm+5NDlCVI6Jt1oXe3bITnkKUKdJ68D/xwjsr6P8G8ECoUwgx1J2CrwRyxpiYZnluBCRFk6YHnVMSNGa/GRGynihs6JIDL9UZitjdCphqKLbaTjX5bBoPM+0R4liC+N7QvNjSh1I7FnuwNvwivnA+5m+B01trB69QuYZuKVCfmntOmpmuFNZSdLhfj8mcaH4BVITk0o5H82HIF5rsRirJUG4lCnFWTI9c1t01FQcg+hnlqie1R0RTPpYZe/apCRROLVoULzzTvHsKZHEIFGo
*/