
#ifndef BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
aSrphsoMg8GBBWWPiBPLHdIMoFtrlQxLillehtPs3ooFVQXlNLa3oKKC4GcQPC/FRMSCgSiZiECtrz7MvuQHKb7Lm0KWJYPl/hj0ozml+T3NFiAV0nkuLymu9pBZB7lhKZf7fQ0h5V5O6dm9KCbB9n+fw62Kqr3llsoAr/89Wa+S3KGngmWQsXjBCuPKSy0nCj3IJj0ovIyk0REfF3pMdApV82ZBMlgwRqUhsm/BlLlVFZOZfLuJrA1Luil3XXM=
*/