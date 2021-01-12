
#ifndef BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/multiset/aux_/item.hpp>
#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/insert_fwd.hpp>

namespace boost { namespace mpl {

template<>
struct insert_impl< aux::multiset_tag >
{
    template< typename Set, typename Key, typename unused_ > struct apply
    {
        typedef ms_item<Key,Set> type;
    };
};

}}

#endif // BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
KtP+3BYl+jug18a8rC0RRF9F+dzHWPpb7Uw+Q7RsNLEAqTZGGgP/qI7URuKRHHLL5mVBm2CWxHUQcz0dxLEWJqBMxM7IQj9CPNQzzw26b4ibqQK3Dl6X0cX0B2bOxI0Za5CDSTQjOKtrL9xOtIYWOxqBmFPZ7Opx3peFqNHg9kkJL97Lr9ZmdA35lWJJynFjn72e8yJ3zK41rFb9NcUbGiOBr9ZV3oTE0Y31lfHmRpOlynOW
*/