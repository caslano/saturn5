
#ifndef BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<Vector,0>
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< BOOST_MPL_AUX_NTTP_DECL(long, n_) >
struct front_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED

/* front.hpp
4FBP1bWZMRSARkThDC6LQDRK9e6V3GXIWKWEeqTY+FrE9mKuZqlwVTD8wpQcNUkUxhas7c0YfeA4Mlj8Nesv9w8KittsimF5hrtG3p6JkrRYNGdUasrQJboXKTahxXR5FXw8lN8zM1Xm4/MnmBAeOGL2yIVNrNyQeTaNGtAVPYDeNZ+mdALd0raDWiYzVMvuhfGbRtrLR1oVZMyt61z3A5sQn1vL+jS4l2xN+DoCQeZE6GoolpzPqa8gH3PBM6dWB54V75Rhm04ZB1H9H+iYZ0ipqBp5ls/SKZjw+wvLsQlEMOn5p5gi1dIOE9sRb7N5tfAWNtvqZiU4bCOew7NoM7N4dVT5VfqEao96nbvEKhGnJXgeSj/rcrPoW+vzxG/Vw5FJAXEvyZTCeXapIUv3Rsy7kfpv5+ti9HbCorIPNLacY3ASni9GwPPTG7qJTksFmmd6Gdi56fpZO7m+83Aaae3GCvM+hhgNDwbwI1b3lW+6XrOQfAipXvW5rY+gQcAdWFB+jAlJii17PaFglunyDS5fB0gZzaf4nlRZxFqJLH0vCZzwymtGCFibtuGsP9W4PfHWmcTZW1Cz+GaCVTkH48t9osmmKdsUqmB6Fp+Ib4wxkNfQ2Ugbvehjmk6dBbTUos5As1M3nafqIMgPBJvgyRQqL7AxvLPLQ0YDxyLjhetypzC0Jl9WKC5vA1Ur3//gD3m/IA+1vKAdpZ5m
*/