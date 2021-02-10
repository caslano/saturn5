
#ifndef BOOST_MPL_SWITCH_HPP_INCLUDED
#define BOOST_MPL_SWITCH_HPP_INCLUDED

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

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template< 
      typename BOOST_MPL_AUX_NA_PARAM(Body)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct switch_
{
    typedef typename find_if<
          Body
        , apply1< lambda< first<_1> >, T >
        >::type iter_;
        
    typedef typename deref<iter_>::type pair_;
    typedef typename lambda< typename second<pair_>::type >::type f_;
    typedef typename apply1<f_,T>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,switch_,(Body,T))
};

BOOST_MPL_AUX_NA_SPEC(2, switch_)

}}

#endif // BOOST_MPL_SWITCH_HPP_INCLUDED

/* switch.hpp
zPMWk8PUwOuBd+13NvIq6GtdgcSilibFAkrUrIJ3Iewr3hsMOoJAzETb5rwYaSJKZ4t0nd2uopnFX6UPmXXQcriz119pfnzjLnhLI+yAYMJJ+9DVI8q63MGwC3lp+gddIdhthCpX8ITIwVWV0C6Jt0OtgdhIoQUTTUJsawP3fiwOWQilI/hDoUO+GnO8y2fDbTzvZENnj9cP69v03iGXjOHGHJ/SU4c4b4Qa06NuMzhdmE/m/278m+9yaFdyatSEhwHS4+/mJ1BLAwQKAAAACAAtZ0pSQ/xkx5ICAACfBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE5MzNVVAUAAbZIJGC9VE1vm0AQva/k/zBylEsVwmecmGCrllvFUZ3aCiS1eki0WYawis1SWH/QX98BHLtV7uWyzOybmTdvBgKNpRa8xCELZJYoOt6w2qoiLodsEkVzNn64n87m0fPoR/gc3t48eiwwj5DAbKPYCYRYbLAwShkjCwrMlxVdx1xzyJRIUbwNuhWW3TataZ/b4FoOzL6xL1yjD9Eaz8Dqw3e1AceyLbA93+v7lgU3dxFrk/tQ0zXKxjAT/oZsrDKNmTaiKsf6eqfNVK+WB/8Us1ed+mCxqRJcS5X5YNp917Usy2HE
*/