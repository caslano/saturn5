
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
KMUZvXOdmkF9PMM0W32Jt4J46vbYV2Qoyz9DrPn+0N7Cx9piDRgTXSMsUhXnz0fFlisenS/DF5HZn+UZbzL0qPnW21gXuHU3ClrYv6G7m+/fWx+P07+OmP7924aI/rXdFdO//mvN/j3X0r8BYf/lN/H794y01vTvrkB0/z55ibV/LzH7FzWf8Jufp3/5/gPRFtbFItKgzUZpW/JQtLkyVWv+9KcZzXzgXalW1eASZ0FxKm8sysKbQaQ7LIw4BxMqtMPCJylpgEubtxdnZ6lqp9NWlOAKH4W17rsHD/s2gMafktW8f5fmKlBjcWmIivc24oR7ApmCYWIgwKxMqfuHZAkCOZ6NNjkSnoMf9HAZP14FghszupAtUGfF6g1AJye/rdYbGMytbqCL2/iYqkxkzqhAU9GzDm52+Bkk3NIGuT1FXWwuhW8vcGaLk0BvstHDD+iUPueShyKwvRcbwfS8arMKI6Yvaokw4jB+Sl8gWn/AGfWeF1+/AO/ZUe/5Ue85Ue+F5ruWSY+h/dqDsfJfpM+Nyp8V9T406n141Lsr6j0j4h3s7soVcc6XgZ+P0CLu+Y0aFO8ko/yeGE8TH4no/OfIwcRiVkExvZUVJ8vbHNcTZm132EWRjyVjB4gUB0nuBrLiCJ9rzJxlNDInKwjSOKc0NDwGO8MxYPQJj45dbGom9DeKl0kvZ8XwclYsMqTDC9oEO5PacBHFQ7c187doqeJPavguiOIrvktiRH5YNRYL776FqO1w5nhC/DO1fr+sbHr8SWWlOC+i3tj4gQnisxPE5yeIz0kQTyidsH2Fy6wnnwnPI4JbxtANsvlSaNyC/huzLH7/5SaAPytB/NAE8cNb0P5590r44sSfsD4+/K4E9WfEj8f8tl8bZ347If+i2W9ddOxq0bnkFuvN7VOEVIxWnHciV5ylMzBG0Q4qhCCtsl20nnBrGASlj1F4efz7Do61uO8Qo5/x9prm7zOkB+Pfr9jpiV/fb+6JvV9x8erE+iL33JDA/t1dzcdf4okPb3Z8eBEfWNV8/P2rEsMfXN08fC8ubD7+6zubjDfG3d30+HVOUN+Zqr4m7T8TM2r1rDOI+EZ54+ICFvHQB3HFEJJeUvzuE/6FlhWYwq13liollXC/JqIrFuvolu/JouffdLvg/34TZd+wavE6mFd1VoXWw8Wc+N/ua88Bh69beFBoRQ081D1E/xPVlJ7vskMhH1xO4rNw2LwgLKRGMHMQQqncf2t/aATwix9D+eJ/W/rSO9hBDRkUDLH9FazWMmPV4rXw7khpWVd2AwWEU8kN0rUfAsCo+6h0KM+KL4EJ1UjKxw+fqopX06cQinSHQuKl1Cig/5XwRSjCVzuIQ6VDS1Iiu7MakLLC4LTlP4/CYBPjsxr8z7JIfc5l2qlEsfHsFMGvLAsGlgn2fSHxPp4doHPLSD39QtPW0WUpVi/dywiDtiWn0XbRJVKHO2i3o5ekSL3miaJIX3Z1+TKSb9FlBe/JnkNgSJaVGqVzQXJhBTG/Mgceaxoz97LDMUKbpBLXtrGN4qJFXSaVBy/kdvhbX8KOKn2m7jPCYieAgBRFXdWGtwP4lh66nLgkTuiWCWa3kVuDRdX0T1hAvFTupJYGA0ttZMK/fClZQJzGHxfPhmfD2ezNlHOQvcjy9WSUF/yYk2xHcqrqkPi/1Pi2f5INWWdCLruIOkHcQQ9N169C27uC3hY+X4HWuGyVPb2no5M8vxbSOJ/wfxJka/fCvo8qhfLNATyirB7pi8Xd/+oVKGof8X8L5qZMDL56aNzit9IX96OommS+pbN9QgeBDbZnxfub+7ZPyKRXROOez/YJKXh/JpkHGfGQCCxXG67l2HA=
*/