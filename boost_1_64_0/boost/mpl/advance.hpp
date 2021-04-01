
#ifndef BOOST_MPL_ADVANCE_HPP_INCLUDED
#define BOOST_MPL_ADVANCE_HPP_INCLUDED

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

#include <boost/mpl/advance_fwd.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/negate.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/advance_forward.hpp>
#include <boost/mpl/aux_/advance_backward.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl {

// default implementation for forward/bidirectional iterators
template< typename Tag >
struct advance_impl
{
    template< typename Iterator, typename N > struct apply
    {
        typedef typename less< N,long_<0> >::type backward_;
        typedef typename if_< backward_, negate<N>, N >::type offset_;

        typedef typename if_<
              backward_
            , aux::advance_backward< BOOST_MPL_AUX_VALUE_WKND(offset_)::value >
            , aux::advance_forward< BOOST_MPL_AUX_VALUE_WKND(offset_)::value >
            >::type f_;

        typedef typename apply_wrap1<f_,Iterator>::type type;
    };
};


template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    , typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct advance
    : advance_impl< typename tag<Iterator>::type >
        ::template apply<Iterator,N>
{
};

template<
      typename Iterator
    , BOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct advance_c
    : advance_impl< typename tag<Iterator>::type >
        ::template apply<Iterator,long_<N> >
{
};

BOOST_MPL_AUX_NA_SPEC(2, advance)

}}

#endif // BOOST_MPL_ADVANCE_HPP_INCLUDED

/* advance.hpp
VpVsSPqgJNxkSBsHbAVzA7eQy8oS+w79gBYoux5in1sE9slbeeFQYDIaQWa8xQRuyIPoRUVyQDo+ySMxNFKLgLdA2Yt/0YMpZSlAgRqRvOs7RS7U0yj2yzwjUGKkn3QZjM27avvnP+JjaKwdRRC5uEuus2zUjY4iGjLn5E3ramOKToMVrEWDN81lhEKJ1SA2TctKqU01GC6Kix8dupZj/VTNnIpGkjS15A1lxiimMWDbDjYtfE3mDs03h/ZAHOpyffYNeFThBF9kUIVVmLSsJjoidCc+wrr1ZW1ElWFwplSboWvB0nFZucXI4S+q05E/X8Bi/uUb4TxoOsQnVdHL//bhrwIuMOf8UT6jOIp5hwb5oYMfGZ4w6RVIaIkb8hKHi33vqiFXW5Z8CF/bFz8oQ6qIG1QvRagSkgKP0sMo06yiCZxx45YoquxbI+mHamtAdsSeuL1rbMDdQoG0P9zz8eFph3win1bYIJ2dtGgafg9UHrs2lAPSUMFhlcWPURB/73c2ZDJY116lwiJzYvgN+y/TPB3c28iBS5MS+F2NK9ASVNaYBo/dpQQTkw==
*/