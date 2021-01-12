
#ifndef BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>

namespace boost { namespace mpl {

template<>
struct at_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef typename if_< 
              has_key_impl<aux::set_tag>::apply<Set,T>
            , T
            , void_
            >::type type;            
    };
};

}}

#endif // BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
M3ZviMUzrze5C7jse8ZBJ4cZlPeRh8h7wXIv75t5BB4xC52Q1aVd5tM4kJ+uk5d33az7Cq4v9Pg1UemVcXmQT1OkMXZztYkLoi3KTiOGIM8rfHqjWTjn53llcD3CXA5iB3kuFk1vD7qr2qwyH1+fpfOG5voqM03k01fW23n7ZL/sS3z9zbwz085W3pf6NBYusKbD7JnoWPRHLw9s1xRnLUltNfdaQd6lll5IjdwBbalP2xCP
*/