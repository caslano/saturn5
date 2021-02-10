
#ifndef BOOST_MPL_FIND_IF_HPP_INCLUDED
#define BOOST_MPL_FIND_IF_HPP_INCLUDED

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

#include <boost/mpl/aux_/find_if_pred.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/iter_fold_if.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(find_if)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct find_if
{
    typedef typename iter_fold_if<
          Sequence
        , void
        , mpl::arg<1> // ignore
        , protect< aux::find_if_pred<Predicate> >
        >::type result_;

    typedef typename second<result_>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,find_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2,find_if)

}}

#endif // BOOST_MPL_FIND_IF_HPP_INCLUDED

/* find_if.hpp
/2HjIuP1WIybUDA1bFH38MhtAspNSt58jLALDM3EXZrTzWj9fmhm7fDirOV6jYPDJpw9gtuuctSEauZZ1aXtDx14BWS/3xUYb63oafO3Ld6jbhP6vOuWXzYpNOHaHMA2xeNtTj4HsBalufCpyBXPlX3J8zs19OEzIbkY44PEn1PbUNz7byg+VKoQeTbbQPKX8vv1IE8hFJPbLI1bMy636Q+EeJsU5fmb4KyBGIYIPCrt43O+PF13HuSot3ul8P41rRvb0rrxkrRu7JrWjX9N68Zr0xoBDp2d09rTjW3ewrCznWaplq46W2wGKDDgTCEoNsEwvET55TioUrlNNEPMSzfNxWSQszH25MpYidxQoNkEptnGLP9QjUvcbU4cEDnXCJVigG6PWZ60iT0yeSZ9Sve7vTC6uPb3TWO/7t1EhnqO47hgX4IdA1KZYk/Xs3X1R4HdhT0dJh+m02l9JaR7YFDXQVcxvZ0x0fp7s/F3EUP0Mx3oe0JRCiVikbUJ3kRgafuiqtbIRtwa+YFhtU/uEM4HjFVG9392bsKL3lWNnMQxL3D6I/1YI7UHwN5bAgd0aX0wSDMO+qBae2vR2YOxSHBacfxvI62uuJIxK3h18hUf4Bz1cW1xrnrnuuQ0EbGketKe39LqQzXOUDAa
*/