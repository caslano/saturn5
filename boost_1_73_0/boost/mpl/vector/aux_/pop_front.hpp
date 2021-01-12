
#ifndef BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

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
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
XKuIZGUdcWibNIvWLsvg5NHRUbqjlrroWzecuRXEAns8TTF1IXVxyfCchQ9Drs0J3dTFHTR/aEQh2HX+o5KWz7rBoU5PwXEAu/72uPWlmTV5Saf6NkVyIt3xZsnIV2pqg6RMeQs99ae0EYv6ZsjP3nbi/0On/MvKYd9VbKyDWNA3N3H/glgrnfbbhzJ1Bo7piVTSsXHNdeV5+FsT2ZS4Frojzuy6u1sOzydV131DxJMtJeuN
*/