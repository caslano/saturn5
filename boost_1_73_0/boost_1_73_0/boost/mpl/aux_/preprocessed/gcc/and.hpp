
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
SYc6y3bs4ePYkLpEgk9d4dD2aGNWE3XOt245CC1bb9CptmsQgquLITgpqkHpXjaqhMIOHRlA/aM0eg4fSSAK07ZSlzGLorF5o0Qj5VqNfofzeYDoAGH+ivPFJsnybbpahIlpss/58vHZG7sr+vC6Zdj/C62qBiglSZAVoQWqES4vDLV08I2oYeZqQzMm+oD1EmitsYUpvdenpVf8lwt+R/Hpn/4AUEsDBAoAAAAIAC1nSlJGBgaOLwIAAPgFAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzA5VVQFAAG2SCRg3VRfa9swEH8X5DscHXkpTeWk3UOMllG6ri1kTYjdvmvyORZxrCCpSfPtd5KdptugMNjLBka2pNPd74/OwqPzSjqcMKGb0tBrhfudsYWbsLs8n8chiyPc3uSsNHVtdrVR0mvTMMGP4YK3GdgHyNBu0Q6cLpAJi5t6T9uF9LJNyofnQ7hIhpBX2gE9EnaobWHA44uHNTonlwhu51RtHPbYF+kxhfwZzyAZw4PZwigZJjC8TC/HaZLA7be8x9qiKQRKAxcnvJQrOj7t4KZQeb9xKef9u1mW38/TfqQ3ny1yHuDxi2ScJMno3L/4z8qY2mmPn/boeuzaNA2qNkuHqsci/rYU
*/