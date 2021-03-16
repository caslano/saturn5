
#ifndef BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED

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

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct pop_back_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, pop_back_impl)

}}

#endif // BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED

/* pop_back_impl.hpp
HojH44PJgOV9+BQ1hlga6U/EjL5VwYB/Qai/7O+x/o9CegdWJQcTqyLhgP8UqF3FKvtWBWJDoXA8aAwF3O9QAzgKfxHwL/9i/1JkE2YiMNAfX2WE+kOBEXswrS6ebMHo0cg6FH2195Te+eTVs2TFssWLl/UsXz6fvXqgcNmy+fN7Tzmld6ksWX/oxp1BcfQZJ47ev876dBlf9Mlv+JKf9qpvy9ivQ9vZt6PxdfFJQvgB97j9bQn8VCEg2vtsXMY=
*/