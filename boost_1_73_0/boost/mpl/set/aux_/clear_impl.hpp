
#ifndef BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef set0<> type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
kpd2TWCjOKJn2fbJWT7n6uzb1i8Tgdc3NEVs2/o01ZfdhnxafQMtdyMeIT+WjS36+obqVjvtE3waC+rZf1LTEV5a+gTfl9meslLrq1QHjq1LkGeZf7062lgbxUT1ta1Wnqt9ulk7W5+V53WBrJF4YxX1IJsHcjbU0ixqtebP1mVNUGcEqCaaLCuIrJh4fSBvs93eWvwY41nPizNB3lG/3lrIl3jSkB3nbgx0ao43zIwXTxFd
*/