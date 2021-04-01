
#ifndef BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template< typename Tag >
struct contains_impl
{
    template< typename Sequence, typename T > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > >
    {
#else
    {
        typedef not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > > type;

        BOOST_STATIC_CONSTANT(bool, value = 
              (not_< is_same<
                  typename find<Sequence,T>::type
                , typename end<Sequence>::type
                > >::value)
            );
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,contains_impl)

}}

#endif // BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

/* contains_impl.hpp
Y4yM3yKIxpXseYCmFMu5YeDaLFdEd8lGZAMYK0o0IhsEZQRQwY3EHlQmjLz4XbIY48lSIYB78myu1+xoKK6X2TPnmjPWGnJ2ZNnAv5sxEvzaVF9QyWJ3Uu7UlzOWlPjq5JEQRDiUeH6DVjs0k9sPMa3ujNubTxiuJGaRvCPxThF6Kf9FmqyiF3LKvGu+hLM9ogVzuzsVKVnMvthd3JR5/9x4WAbMZ+I+BUMrFwQOp07rTJupAwwAPyDQuQtO9bEznk5KfIxtSifLwBGnZdfcNRcgzMzQTISLC63BiZVOlbRgUozBFXkf6WCGfHkzdguZykUm0kwzWxjTgZf9wPwUOCUq0dBtHjdRNfvF3mvZldveNMCNCNzwjkSi/8G2eUtJ1PzlTnYAyI1p1rNDXQb0mx73wRWDXWCDEucI8ut+jPjE7b5/AWYFxvO9qsytWZy1r7NMb+n0G7eShtRuKtXJ9AlyYivaAy9omwcrsiVoi+h6Gi9F75anqgq1VRqrf3bHHg1mSD5gtwyb/mxYoIeDccbDcqtNB6Wjo1I4mAWNVIYn9wbg2fIwpfwu0g==
*/