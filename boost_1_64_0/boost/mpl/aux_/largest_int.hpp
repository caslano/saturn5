
#ifndef BOOST_MPL_AUX_LARGEST_INT_HPP_INCLUDED
#define BOOST_MPL_AUX_LARGEST_INT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/config.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct integral_rank;

template<> struct integral_rank<bool>           : int_<1> {};
template<> struct integral_rank<signed char>    : int_<2> {};
template<> struct integral_rank<char>           : int_<3> {};
template<> struct integral_rank<unsigned char>  : int_<4> {};
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
template<> struct integral_rank<wchar_t>        : int_<5> {};
#endif
template<> struct integral_rank<short>          : int_<6> {};
template<> struct integral_rank<unsigned short> : int_<7> {};
template<> struct integral_rank<int>            : int_<8> {};
template<> struct integral_rank<unsigned int>   : int_<9> {};
template<> struct integral_rank<long>           : int_<10> {};
template<> struct integral_rank<unsigned long>  : int_<11> {};

#if defined(BOOST_HAS_LONG_LONG)
template<> struct integral_rank<long_long_type> : int_<12> {};
template<> struct integral_rank<ulong_long_type>: int_<13> {};
#endif

template< typename T1, typename T2 > struct largest_int
#if !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
    : if_c< 
          ( integral_rank<T1>::value >= integral_rank<T2>::value )
        , T1
        , T2
        >
{
#else
{
    enum { rank1 = integral_rank<T1>::value };
    enum { rank2 = integral_rank<T2>::value };
    typedef typename if_c< (rank1 >= rank2),T1,T2 >::type type;
#endif
};

}}}

#endif // BOOST_MPL_AUX_LARGEST_INT_HPP_INCLUDED

/* largest_int.hpp
Id8dY/1ovueRqQ8m0dqp2edbbfeGhssad5VU372/16OZJvG77rqYyrkEd9NXOysS1Pd0v2R8mXc+aU30NVZno45YvmuFZWEpY8vrQVLin4Zt16PINSVq3Dh/Srt0R3Pg5ZZlr87nZdxbsNfm5taGpJmGyxYb2ZeZ/bwX6yz2fNvcrQrs3Gp12R801vNWwxe3WIu0DDbMtJF/TRpUs3RFkUGQ9sJxy9cxDVdeKRDZcv18bj0h6rJW0arR4hdufq8x/iCz+mep8NBrZyrPVs92HX/Wr3Wt2tP2Sc9aP5SaZMkWRx31Xjghdn8uW3b6uWZVKcUdBisjLN8p1OXNsbbYdrxm8vSfqvIdzUliqme2KLgW3t9lHvEqRHK3+o1pmw50BD6qPDhsndo82tGOUepKVVnnlhSEMkfOFylamEZ8/71B8bqSW3dFgor09DmX9kZt/534+0MkqWDj76KGheuIMatPd0ZNvie307qxbHzhwi/6AfPVdke1rqCmNDFePq1lZN//sLiB9m6NuILJQrGzR9pvaz9sHEL1PzlEIj4/5WKrwZ5BjZoGcZON2x85bPNWur91jYzxuwWfLqcneJ66+b3wXiD7me/ODaIP1d4OpSg4vVxZquxdGXzg3Crja9O1tCq/TiRlK9Eik689jnqUT8yaddk7Qyw4/eTcG967igkpO1mHOyZKHCCqr69t23+e5j5x0f7G7qYKkagM9vHM7BVzLr+I8TzStXaG+Jedjdt0PVqNrI+8S2AUZG8zvVJUbuo03WeBOi0lIfv3htU3jCVVUF3gLQpD1N5MFK25I9r6uCPFNDIgQSZO68GgINnjW68Z2BXuJdsQHycxPieV0F77im3eU6LRLH5JjPjwxWTtzSu+Tzl3dUSgZ0LahDsF3zNONy++e0dFM4Qq/8q+IfyppuLewvC872smeW9OMX5idnjvFa9tsRafpFY6jw339tbNOrv/TsMdszPJE04tvMGs8Zgx30D2Su74onPbX510/2ZzfnlWwEOZX/4xc64k2baerB96daqTf2Lzz3UfwiuiDXaunH5ptteWEIkcevo2qcWxOl/ND8WLGss8LRlkcOhUkEPdj46HU5QefWqXrCeYz7J7+HH0zM+VkmEi3z9mZk9TCt1x/2K3RdiZ06rN+cumDboeI+3mGrboxtbWCq1hs7x80x4633d61C7VlrVEmKFf4nhK1dLbVfHMvJv3tOVX3PIe9VPSRLtyvsn7+pCL5mMLFETvTVGIq3yfHUSse3DxwdnzyzWpaq7Ot+V/V8mxzEfWiL1ddH/pee/KBTvMW7qVL+3105vQeS28tK4hJCH583RK4YZ1+vFrjeVVFxetsV2U1hxi+uHRogfJJSuD888dGtk8N8VV/v2bV4yvtZ+nzL5l+HMzMVSMYCPXOH2f4sXM4nZt2azg+Mx5V1gmRSedoiWUY8wu+xWKH5n4waN7guPlFM9rNTTNPPEhZmlfhX3prRprTx5wc770ITDMM0VPfJIca/vogglVnd9Cfp8Q2SOeVKA2d+/J7N07Za2Ts51Ob8kVPWA7rj2T8H/zx+ZvP2tDIpO5nrXBcYnwcQboN7kH2Lq5uNvDWWqIPgEcE44q+YLho6GadgGolh6Q+tAjOUH70kDvsw8uiRkC8XF4g+OM4IxXDhyBxgOZRq7ISIJ0U9xtHHt44YJ3RAWYwO2HJLj92ME7uB8K3uOCtiqD2cMHl/+haYALoghAVQXgdldOPE5wtJ1tT8zgD0evpoLMhLCCAkBfHtWn5Kch9/+EomLojcfRKBa5dprfj2aAHwd3a/TBseJjkkMDEpKCIIr+aQFBiYkC6AmJAnAc2cSwIiLD2CjckyUjAOI=
*/