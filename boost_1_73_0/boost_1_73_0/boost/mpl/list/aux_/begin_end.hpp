
#ifndef BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/list/aux_/iterator.hpp>
#include <boost/mpl/list/aux_/tag.hpp>
#include <boost/mpl/list/aux_/item.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_iter<typename List::type> type;
    };
};

template<>
struct end_impl< aux::list_tag >
{
    template< typename > struct apply
    {
        typedef l_iter<l_end> type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
xL3Vq0b61vbwO6znr0/U1dQuFGkbG+vn44mQvu75dMjX0xOpbsTuqa0eWnU57FSdX0pW4k8dJsAEjrsHug30dceHEkOrk5VzImdXhoaTfQN9P4IDuUrX0MBwHxwb8Dy/MAvv0Sssfa8MN9G2kFMLOds8rqgW9ES1iCPq0VyhYDQS8mueoAOOdqC+GDgnIzjgWK45HUH3Mp876iXzOScvI8fd4QprUUcrqeHwwozwpQ6/z621+B2tHWQuMI6aS+A=
*/