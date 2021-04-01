
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
ex6muv5VAwpkUdzBI7S1FIOc/zFc6v15etvgFSx1bosk08Mn+UUIm+vMRERxDOFWFLbSnD3N1tl0NwgS0xfiWECyxSuU0X9dkk4mFDKd2me8k2vqHqijJeYbtpRq9yWnJfEaNArsoGTsOGtKAE9dWjytzGtfxAEZlhlLTktoME4OAiRqZNwd0mrcQ+opfhEIbOIl/Aq5/tIPbuTB/YVPCzasBAFdrMVOOOHdFI8Xb4/ALm1s/gwwBBWKjatcGylm5lG7sLdFSApKQ/Sytnnzoq9vmkuqrgGeDBASv3ALik2ECatSsOikCzzHs+UW8iUXKOZ4tC+UWgRZKBLsZh4hoDhot4lmbLd2XRM0vWBI45aKkR2WwzK4MrFZtZUdXuH+JsUuNgmPWP2l8sL6ECk9Av4hKR6BskoZteqgi8FGftriBt7mnOOQkYWjdrcp+J4g/5zNMMW/NPFuzKeXzfiHa/SFyUTnadBU7Ar921txVJlbbGqd2UcHosbQwKEnbiuvWfXg1U7NBB53GGL7+wvQqYtIhJeDk/3i9YGGfldYFYZBr6dpDRjPB2dsXA==
*/