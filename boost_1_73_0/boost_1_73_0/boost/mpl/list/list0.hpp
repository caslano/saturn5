
#ifndef BOOST_MPL_LIST_LIST0_HPP_INCLUDED
#define BOOST_MPL_LIST_LIST0_HPP_INCLUDED

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

#include <boost/mpl/long.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/list/aux_/push_front.hpp>
#include <boost/mpl/list/aux_/pop_front.hpp>
#include <boost/mpl/list/aux_/push_back.hpp>
#include <boost/mpl/list/aux_/front.hpp>
#include <boost/mpl/list/aux_/clear.hpp>
#include <boost/mpl/list/aux_/O1_size.hpp>
#include <boost/mpl/list/aux_/size.hpp>
#include <boost/mpl/list/aux_/empty.hpp>
#include <boost/mpl/list/aux_/begin_end.hpp>
#include <boost/mpl/list/aux_/item.hpp>

namespace boost { namespace mpl {

template< typename Dummy = na > struct list0;

template<> struct list0<na>
    : l_end
{
    typedef l_end type;
};

}}

#endif // BOOST_MPL_LIST_LIST0_HPP_INCLUDED

/* list0.hpp
c3Rlci90ZXN0cy9kYXRhL3Rlc3Q3VVQFAAG2SCRg7VRha9swEP0uyH84MvKlzFFcCqGOEyhp15SxJjRevyv2ORaxJSMpSf3ve7LTZtkY7AcMG9uy7t699+5Q7NC6VFicsViqXNNrh81Rm8zO2CJJVu0DHh8Slmq9k2hZgSJDA9m+qlnMz9Ex7wDYF1ijOaAJrMyQxQbrsqHtTDjRYfJwGML1aATL7+xeOIwg2eNXGN3Csz7QRjiC8Ca6uY0o5PFHwjq4CDzXwLYLnosdsrlWDpULkqZGv/3meOGqkn3bK9UEnmgEDVq6wR5tWmqLBOaCeSslglzrjTBTJSqcQKYrIdU0vB4PR3SFE6iFK6Z8cpFSSVsJlxZTV0j716Q+t7IsG96/TK6FcV12bdAS80+A30uSm51fMT/5R7bOS+nVdram7YICOkNmrHDON+RjCbGX1RkOR+kK6BroSVAMCJXBqZUGU2qhVFtK4l0WxKmuKorpcCPOB4vlOnlaRQMPuFq+JPyI/CiU42MINqC0QgjuodRb7mHteOjeHPH5xKHPE2WS8opG5g14jSByRyRcgW2DoRAWNogK+rbQrs/iQxtLALXRTqe6nDGaR/il/sdQ9dhCWxfBH1x77CdpDu62VD+CdG9KPnh9eFk/LZ97
*/