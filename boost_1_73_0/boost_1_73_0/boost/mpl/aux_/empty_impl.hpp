
#ifndef BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'empty_impl' or the primary 'empty' template

template< typename Tag >
struct empty_impl
{
    template< typename Sequence > struct apply
        : is_same<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,empty_impl)

}}

#endif // BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
uqfoqnh9ywLdr7Aj6wj6MBTePm5+O1a+DNc8gUeIM1R822Y+PW0Le7xm6mN++z8sFcwU+FDz2//pPi0Nnn7oPq0Jnv7LfRryJFLRLj4V7btTpnc9YEMPWtD8dmwHIm85GFV6OIhUls0ua4E7Q0P7hRDqSyFoWHQTv07R3gcI1UNoAD3do8zA3wwtE1gltAQ2XNwxviDYTwV7W7D3BMOjA4wd7xkMF5Z4MWiGhLBJa6TQFRJaK7LNItsKf/tQ6A4=
*/