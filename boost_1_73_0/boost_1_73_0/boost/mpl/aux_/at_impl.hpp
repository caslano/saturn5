
#ifndef BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'at_impl' or the primary 'at' template

template< typename Tag >
struct at_impl
{
    template< typename Sequence, typename N > struct apply
    {
        typedef typename advance<
              typename begin<Sequence>::type
            , N
            >::type iter_;

        typedef typename deref<iter_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, at_impl)

}}

#endif // BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
WGJB2+18i0x4IWPNm0/nLNMLRvUiDTv5nliNOsVcKyIHp2FtUodVgblMtJFlxWFLxKyUxZzJrSyR/9UYSCl6/ZBngBLZkniv0/VBKqHjVC0m/sol7VP/NbrtQu9c++SKh5Wd+CQ2ZrNer3fY0nS0WTCfVCUeJC88ZRTrtco0j4kVeaIH4qdJKjgJWVogWnK7BIctOfHtkgcnQ3/KB/1uHAz7p2MxHM9HPBic8DGPh+NAJEF3PohFNxgm85EIkuSUB6I3HIjBmI9GPTw3jMcRI9AqIvsiZLQtsYWcP4jdmGCmPb8mtTJZzYmS96EwMsEWVgIt464/rSVpXlzfzS5vwia1zs317YxRrhHD43X0XaxSIEYKkWasFi1iW0Xpvnob4RC6clVMvUIikebd7dn55S3L0jkVmSmNs5taZztFBiQ0BS1vtrOKWI9AsNfq+Skn6yMJsoFyJ/HESQNuWTcYyoYNh12HpdDO96p60QYrjHZaaEwLtx9UEbcbrOFdYLAQvlCj4f2ME9p+s8DguIRQFdb8+Pb27vL6p4b3RghZoPkle9nwGsR4F6JspN7fd9K/XCslSo0WPEKzLsb5rbEqt6B26x+6SWNKN8h1jFZamf5+gYRQ4ELEUYKjfxz41m68GS6cTqfzH1HwQ7E/
*/