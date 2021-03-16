
#ifndef BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

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
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename Range::start type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

/* front.hpp
Y47SuEw9DC5KoyE7me0hzmlamHGQmBQCHthM9qiBTRc7rJQMy22nD7jktRu2hEYUkFQg9BUFzZxudFY8eTibKd3edgt5605kpgmlvhdnmh3uDFeDoA+hLB43WORIXYDUP6mBM9nd1nOInbbT1zok0y506xCelMlMP+cnBT5PBr5c8MUirGzQTwO9cpokfhdRBxvKIKmAD2XNNPSjmWxZ8XayBRtlOvWntFI4GkvhTgl5wFr1Jfx9CUxl+L6kiUY=
*/