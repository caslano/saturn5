
#ifndef BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED

// Copyright David Abrahams 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/max_element.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(min_element)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct min_element
    : max_element<
          Sequence
        , mpl::not_<Predicate>
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, min_element)

}}

#endif // BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED

/* min_element.hpp
MS9kG87jIF7CBM5nBhfwNl7GTbycr3Ah3+Qi7ubV/JzX8Btexx95L0dXdxxyER/mTq7hx1zLL/gY93EdD63heos1+ATr8kk24bM8hs+xA59nd77A8XyJ1/IV/o5beDu3ciu38RAX0q+zKt9gY77Do/gus97TCN95hnfzo9/TOLiI5XkIj2BxHsmS7MPSHMoyTGIlLmVl3sGqvJeHcxWrcTVr8nnW4TbW4y4eyS94FCuITzO2
*/