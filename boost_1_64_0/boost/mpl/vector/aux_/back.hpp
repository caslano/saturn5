
#ifndef BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<
              Vector
            , prior<typename Vector::size>::type::value
            >
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long n_ >
struct back_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED

/* back.hpp
co+Lv3qxFA241JomQ5+kjQVlIr96shikiU4fFKESdrNq4eShcT+Ix1vxEW0/H5ETO6FlYWCU6RdGdrU6GX3ryQcKbUK3RHU83ChnZsgViLPP7GGrQF70uX5dXyh2wOGZDKvPmo2BLN9249Rp/WxI7TBpWbmS4WsgVXgJEi+1WrzhBkpqxV80m6QUUK0yZEmWLWn7mqB4eXBW+gEogtajc/65cdvn3PoBccGkGWVQrW9Bzx+i1Ja1fWeBNJdKDxkf/NbzCXC/B0pYh8aGY0gOLe1uCaRyQMMrbxw1HUQUQQYpkLdNI3AWli2Ywq6RElmNHh4Mvws2n6DJi757h7cho/LbLEnBZ62+HHwZMacC4R6WRuKwrq+lxQhu/xnkmttAoFL1L8Z5f4K60YnzyNaSRqlWnrw7aOQ1Vq42MMblV5Qkn7geKt60pi4g4STRSQiOv8hc4x4GGMeqIcn5CzzFrfORpcG889ViWZOVKJXWsJtSNuhXFl+ULHgCbSWsNaGcaLMGeFJvYvvkUkRUoL+A/eGe/Bqw4TDvEcMSjvceqCOh7gu4kT/mLXim5A==
*/