
#ifndef BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
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
#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<Vector,0>
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< BOOST_MPL_AUX_NTTP_DECL(long, n_) >
struct front_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED

/* front.hpp
l/hcvFOMh4K2EMYFpzxsKWBPJJEesgHyAsQ10V/UqTz7sfOkQJgytUxu2/j5AUk3Azuo2APozUIz7XxuTab23RCYU8p28PiD9kEmwsvBKqpVF+MFVBg5FrLO3B9RmVlRzTC2ca94YMsix/6E3ee2iTvjx8Ha0geP9tdnFeys635ST+vr6sa7/dKO+4Nffm2YW8KHvY5r3657k5DWJzqtzfNFfZ4vu/4DrY9/3Cync+RNeu1F4b2g9xbSe/W/9Z5FbxuL3h1bXnqk5rRHWcff5DM77a3NWY/2yQt4T+bwIe8M7ZiM2ulPk29QSwMECgAAAAgALWdKUiGmOYy2AgAANAQAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4OTBVVAUAAbZIJGBtVGtvokAU/U7S/zCxMdnNFkHwURs0sRatDVWLbzebZoBxnQoMOzNo7a/fC1ptshsIl5l755xzzwxYkgjpY0FaikXjNYOwJYc944FoKaPhyFTG7bGTP1B7OnlEw+xp5BNq31XcbqdcNytZrOrHWKtXGlms14xbxdIucJZ2ZFCulWs0JnxHuCpoQBSLkyQ8QIHIJ/0oaCkXsnu77drAZI+c5VHDD0QOTx9Br6sHi2c6pE+JF682Xi/cLkx3h41Z
*/