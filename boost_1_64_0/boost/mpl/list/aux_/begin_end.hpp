
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
pv0ApqrXN/4Qxjc/EkakIeWPnI8OYiGA99AOBmpgw2eyynpJUsxYefx4zafdprcssVUsShuVraEbJME4FjfPGO3MmWXr3wi1eEnVfdWngND/NesZVX0g5pJ9X/pvd2JrZaM9GJgJAcQ7VSyBP6VaA7GFZxLPI//oebzjuTch6LerMo7Oj/eeiVK5B6h2peUzjjTBEiUNaucP2sVm+9Bk/7DA0KEl4k1RyqyW7u9kAzCO/BSDnPe30vdptMV6GPPfyRovDaJMIHjDkGt7BepreLPXxI1rcEitU4jv3Wkfj2Rg9Nh7swTbdvSYs9m11VcERFy1S6snQ/5fMrC0PtsTmTJdDGZFknc+nBSMQbfyF8GUhZ5ig3hR2ZzhSNrvdU6UYsn6yZ01bkgQhnaKgSC9ZVPx2ID238+1vX37/XV6zHXilEYQ45uOLwTiGque96E9acpdFbaa0UvVMeOr8i7nyN+D8JHcnRPf0czNWT3MtT3HHt3ogZ0vDnqxMsEI+VRuiTw6DmOW47ufYjo+KoJA1BL0YzJi0rmFlRwvgF7nl+f4t+o8hLPRBwgu1A==
*/