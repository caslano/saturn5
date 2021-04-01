
#ifndef BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Bruno Dutra 2015
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::set_tag >
{
    template<
          typename Sequence
        , typename /*Pos*/
        , typename Range
        >
    struct apply
        : fold<Range, Sequence, insert<_1, _2> >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
teW2xbgH05NmeBI71sAqhgGd0nBBJZBKXNzCQjBMU3w1pAImShoJvMiS/6NXGbONP4F4LLeOzXaWnacsBgY4gY09xLDJm2z5ish4v7tFQYox3YClAUmkkBwPegDDZPEqcIoZ6EsTUX25iqGSBHEUJpSo4DTlRYom/6P/+p/2j4UtSR7A5H46G7kql4gBxSLPH9rjF5m0jVaQDlD797bAFBZT5XDSEBas/rchDaLvO7shWVk6cFdzRDliKyamGygfq9GjkT2LFX6+dHENHt9ZqjSyljq6roTO5G41dcIqXS2Ja0yfzNTARmf0293aYPPNcLhYO2uH/RECeUS90LKX05+F7S2nDFWojGwHV6rvxrLMkHlYzYSr51xyCx+xwpAhx4vmKTtR9//HbHempVM9U7kTj4h3jIP5GXeQwB7G9ljKZVjDU7ddCwdOyZAVRCIgciWJV6XPRjltZDRM8fQa5VsZ3oOSlC4xTG4+gDTc+AxiiJ4PLMSg1/rHRdG3Fbc14ANdfQCS3qqexeSlXbOS+vVAK20Whs1wksIMAYkGNVV2eYJ9VhBmOVJ2KQ==
*/