
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
5tnrt3WaAkDB3+7FgIKRNzfj36LJciEu2xDDPfzCCO/LJTJ9QP7v+adnF25jOI0sTLhDD2UDBxH8dEHWCxprH7wlRqAz/0LU/ZxIR9StBuc+u3+FyiYy3xwabUb/+K1zHhl3K2AaxNgt+eKKh2VmRH4+eRjH5EpQrGJ+6x7JIHMRYJXNPwq6Q1pPn0K9rnDAw4kZHgi8ZglMao2125Y3yjkihMqUH+H3lnylphYr8Gacod+QrpWXbQlSHgowFwOkXJ7K5HhSH3oLRvvtEoQoQMb0t3Qo+iqDnABVA/Kly92bOoGXrzCzmRM1dSx8LHxUh6mBlBiKtuHu/Z5t+NLv0mYGhWDMh75XhE8Nsrqa6YRVigH7Hw3aOl+y4L0rr+Leebd9r1FrYOS/m3+jvuYm/+/m/+P/mZ/pf5n/D8G/x9JAbx93Vx1bfx+ef7fanV1MhoGQpiDtNBlR1vFWG3NlbjpDjgsvxdgy2lRoQWar2Ue6scaSaZabWBP7duVLaYLz74YrWqdE0kwNZOX3GdgaKCgnslvNKC8/2eL/EH8pV9UsUMBoDt354uBs2DxIwK4luBJib3dxk0qdidPsgOyP3ZO3mCVoP5mb1e53CH9V1zeBwtEeEVIqmFCZsO9f2fAHW7lnkwu1QqX3L22aDKsFoLpPtRi9SGTf2nQDKeI+3OZmvimV+KSBzYrEHFrax23R7oXU8NYAvQZJD/nx
*/