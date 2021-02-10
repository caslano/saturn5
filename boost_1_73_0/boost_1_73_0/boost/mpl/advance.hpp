
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
Usn7DKrdAQAACAMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTA1VVQFAAG2SCRgbZJNb9swDIbvAvwfiBS7FHVlp0m3CEKALcvarWkTJF6vg2LTsVFH8iw6nf/9ZDsfwLCLLVLkw5ekJKGlWFmcMpnr1LjfGzbvpkrslD1G0ar7wMM8Yvu6oJzNfq4Xy1X0az3fLBevcyb5JV7yHsFkhWXROEeiSPUcHt6GMAwCWD557KsiFBDVeAPBBF7Mwd2EAYQjMZoIF/PwHHlsg9UBKwGtQt92Bk/VG3psoZzn2SR5mmNy5IR38KPWbQXHGYowOHPmkdoJGAzDYDj2k/ijfzcZ3Q9Hk08Dj32OYyzJXyu9Qytg27hiHpsZTajJX6DeUSbgvnNpjCk3WkBcGIuXqKgpsVX5h3hG+8Jj32qtGz9D5bQ1aJsW6TE/NcZ3I+pHIvlxROyKXcGsyFuSzRNkMu4MF9L3PGUZUekSTqYkY4opK/JtOA7G7qK3QWq1x37Y0O0K3nPK4J+F3Tj5qHRdgsXfNeoYYfXFJfM+G2Rs9nulk76s4HxnzK7AW+cWH1r2armOeFsZzqY7LTfR95XTcs52x2MfXYevWOVpA23zoFLCCijDbrWQKQtbRA0DmxkaMHno
*/