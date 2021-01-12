
#ifndef BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED

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
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct pop_front_impl
{
    template< typename Sequence > struct apply
    // conservatively placed, but maybe should go outside surrounding
    // braces.
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) 
    {
        typedef int type;
    }
#endif
    ;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, pop_front_impl)

}}

#endif // BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED

/* pop_front_impl.hpp
9tDPXTr07XPNuX3P7u1Yqh9Nnzz9w8VXNH3yx1VNz5h99JJ+KcpM1vT5D9+ctGVxzdKdU647/LM+I3Q+WoXp5+z+5Z1DStY58t2akybc36VwO9cOWfOPKTPpvvY3zdy8/2HH77hv9ZRrtIkbRNPnVl39XNneX504sv6pm4YtHeuix6pNf2l+txY9buzwWtdrF8x8pnG3c7Uhs+avdf4Zp53zwH3zr9t5V52OaWVr68PJmn7i
*/