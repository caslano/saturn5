
#ifndef BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

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
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename mpl::next<List>::type type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
Y+NKnmOaw6hJLCHd55ZpHSRyR/3hWGNIv0sEwRtqCYOJ0p3x6Jlq5NJidps7T5a3HHlghg3dwllDCYj735Sh0O4QyBYP4y54uctBtWEqwGCn8oPTnhV6iTTOjKS7DdKRrKE4pRNlzG7L0PyURJEkx1dVUsWrLSpkpP5HikCVHavBXczSY5HXniczrJWUOzHPS0uq3eXFTIYn00T1ahR8XW4RurpyXlW1cylIFQLRlZF4E3lN+T4PLQXkRyhTRRI=
*/