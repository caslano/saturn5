
#ifndef BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'front_impl' or the primary 'front' template

template< typename Tag >
struct front_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename begin<Sequence>::type iter_;
        typedef typename deref<iter_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,front_impl)

}}

#endif // BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED

/* front_impl.hpp
H1HuT+c3s5sL6MVyRaXLpaWz/SdwicAOqPC+1bBfS9X7YRv398n9XzT6aWrRvuAVO/D7ePuBf+gK709nV+fT5zLU5TymDe+MLJqHn/+EMbx6BTKBXg8ffvoK/I82FO/Dy5ewfYFF14bLPds6NApNhP8Ut1kzNCm8/RPwF1BLAwQKAAAACAAtZ0pSh6Z+aKEDAAALBwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMTNVVAUAAbZIJGCdVVFv2zYQftevuKlLmwCxacmOE6uyiyJu02xJEyTesqcNtHSyiEikQFK1/dLfvqMk2wk6YEABwxZP3919990dHVs0NuEGZ14sZKbo5xm3a6VTM/Nu0fJCyGfvy2Jx33zB1aeFF7MDJGatl/fGewOPqL+h7hmRohdrrIotAVJuOUiV5Jg8T/0tGn/WhGJBP4BwMIC73705txjBE6anZIHfakk/QQjBKBpNIoJc3S68NngEjnDPNAeW8Wf0LpW0KG3vBuXK5hGcjZ1JYmKFkhEkhTIH0GJboYuxsSy3ZbG3z4WplBGtSyYKlLzEqfsiJsP3kORcG7TTrJZy+x5U5ZBTYzWXK/Q+O2svR55GQBXSx3M1cbA5t2ByVRcpaWBhiZBiIYg7ppBpVQKX
*/