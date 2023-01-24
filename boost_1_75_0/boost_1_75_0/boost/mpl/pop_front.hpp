
#ifndef BOOST_MPL_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_POP_FRONT_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/pop_front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct pop_front
    : pop_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,pop_front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, pop_front)

}}

#endif // BOOST_MPL_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
9Bv2tKKUpThs04twlNZPOtyZ8mMtinHeIpE7IWLvupE9az+JsQ3ORV1bYPkbhSBMlxbcRokpCABW8/e9YDgvkYMicLpLG1fTJmP6YwrZvpo4cqu+Va6tRHVet5WxYhwI/5PGflFGunOqdlGHDMMnv+scie6gUI3IymuEHqpOo0jN7b+AlFlRQGrfPYZ7ZK46Ao8Ie1MUmWfuN0Vvuz9AmWltpOzKgEPF2Uf1rD9xWkPOZUv5szNdsQyNr1hUcZM9F+Nk0BZQZTezAreKRVtMo8iaBfFo2t5v3F9kcwrcgMyXJcUVnRXgpleSv4u3CcfDYimoWkzMveyNW9vmpC4W8IomWl+9sNxJlc/gn7KcubdfMouZT+2G/yKtdpwoRutGv065rPuz+h/TvEnhLJVh4Sx1I+qt8G3x11xJfwNGSD7umfAdU+EsTz7WmcGdUuHsu/N8PQP4SHo+QelDKzkHQ81PELny6Vk0l4lgySzbi0HTmPzuvm5852mH+bmJC6NJ/HVjal2Tv8gqYJSURwMgCr7PepEqnJPL/C08wPSoBnuevo9YAQOZoC3V4XaW41oMeFs+aYBfOzFcWTxRvgaspFJ2h8ERtb6YjakY1G1p5FLCNT9XVGAypkpX1UEPxE/3+vxPdPWznfd6Wa+x6ee+9Bv254+dJbVjpaSPDZUYe+dLhxzH9+myIJfHX9jG737Hxi8+T+dTzDizGwWL
*/