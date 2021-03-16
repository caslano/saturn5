
#ifndef BOOST_MPL_EMPTY_HPP_INCLUDED
#define BOOST_MPL_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/empty_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct empty
    : empty_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,empty,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, empty)

}}

#endif // BOOST_MPL_EMPTY_HPP_INCLUDED

/* empty.hpp
gE+AJ6KM+FewAtwJUpnxJF0v+BQ4AO4Cnwa/Bz4DPgO+Cn4ffBN8luIH0VJxPwWfB/NRi70AklHVXvAScB9dF/gS2Ar+APwv8BXwbRDPzJ2M8uc1sBx8nfIF/id4NngAXAT+CKR672BIyqPTHaMhoa0iXnNNZNWOkbVaWczKfLoSKqi5ySFmPY28mTTrnWsFiYysLeJGhBjyS/MiSfY9jZXRxZuKraBqcT83c3lXDC+bU/8m3dDotuieQ87S3eQ=
*/