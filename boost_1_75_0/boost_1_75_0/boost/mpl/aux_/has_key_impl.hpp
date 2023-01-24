
#ifndef BOOST_MPL_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
// Copyright David Abrahams 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy 

template< typename Tag > struct has_key_impl
{
    template< typename AssociativeSequence, typename Key > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,has_key_impl)

}}

#endif // BOOST_MPL_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
BBirC3Sm5+hRzjPl2bfJN+yniff47khDW3gOALkvlBDXIL3LZpxJw3y0q5RPRwmWIWLYYJTCn6paH31yqVCaf/NJ4Syt0GDZ2WIMjClhgkEkcNFlP+DaGMFpA7ORRUlEiBeyzE4IqCWXcDOnjAM898A9Bz4jYDQjnX0jaQdxwRKM7FC0VnpnNJBPSwzOatJBpqTq2VJZFuEQXa0cpaRtNg6YrVyuxIFh0h058L7Eq3faQ2VDhPhGEKIJXTgmrf4YUaMZcuUV4aS2z1N541BaPDCGdHbKAPdhYTBzBSJZQs54TFY+fQhhpoNxh12iq9HDJMNYEZaRDHANlfccEGrRTeX28BGecDu+DLwjmdOlHhBsoiUywfIGxJHaiPf+PjLBwgecBlmXTEzVJz8iGZ6whilNlAkkbCJmirQS44sK/2FrYKAVQZdLLvdHamP6FzghkgFBQJYUPWM6Utt/Pv8LPCCrQjTDAK1HhdprUEvB8iPCK0HHeJSiUUFq5Bx6HXVqTB4m0o1v6Dc6J/h3ZxqPsCY20xAtGDUoCiMaWn0q2pLnBY1ZLJ53Pk269zT+rvrT9rdXYHPgtwAxw49IuNcyTXcB1OhH7h86yNJkxm5D+ccJiFy4ltCsKIqz3o6e0dxAXEKWfyIHhL7zhkp2WQWMkeiuoHkKG9533/TTXh/8IbXE2P97hGEmQyc2Cvf55hEhh+4BcW2yEb5P+sEZ
*/