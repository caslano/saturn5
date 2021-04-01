
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
Lob8fI9ViGrrOBrr3KzvpHvw4sbdWKXjHIhBzB6Ub57QMlkyjO+utDY4/1e2ANX7hpE4mW+vWI8X2kmOpa1Hc0X7j27jD1ZL/FXhgais9zg1kQfhFL/jRdWMGSBw5BRb+gS5RAb9IY7cGmqdP+DFsmyjcYPyhfISZHtoiw+es4bkvvWhnamDcoejjD97CqBhiWxRQamUo/SIukKsm03TLe65NnSYQY4B1XwzSHkrP0pDo1I6i1H3S6gzvGLQq9L6B3hjirfTZ5WvYkntC87C4kwmXUapT+Pb64dmHhe65ks6V4A2vvo/Qw2+CEOq0Qiw+dSrLPraECkoRhhiSbpJhkXT78HJez0dnqOw2yCqldrc70T4sC8Ar3PPsQ5sZ2Gankrw7tGsnDGTTjL8tpM3AsWfAGvBa0x5iT+SbvEZ05ZkQ9RDx3960idZ7cxjt5MYaSxPjAYM+HqMiN1X6M9T2S7wlngqYuBFxXI/rYpoAxwXsMXR7DHZB+c2Z/rIHB0z/i/vClnbC/8PU3uGYI/r2GzoWvpU44G0jA9Re7qgo/KnFbvu47uMg9jKLA==
*/