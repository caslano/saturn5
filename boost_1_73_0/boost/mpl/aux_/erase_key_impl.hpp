
#ifndef BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

template< typename Tag >
struct erase_key_impl
{
    template< typename Sequence, typename Key > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, erase_key_impl)

}}

#endif // BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
lCIcIzRXttl4rV7zDkD/QaZsmV5+mUy0fRTF34uRp4jh1udp4/l/P2ayjvQD1mXLNxDl+dsQck4Ljv0bg7p9M0n6N6xmojfEls62jnGsg2mEJdI/wOIXEuSn3MHY1qN5xu0LHyjrUSBbU2s9cmYp6rdTJunvB50M8UIS/7PrEK1c5FsjyvGrBPNmwj3kFXT7mC232vdHHMurItMtJfTm7zUnyrRyXcpyuG4OVBalu5aW2w3d
*/