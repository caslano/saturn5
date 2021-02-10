
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
q0lwvtvtzvBdrcscz6jF11pzUgPNLtQ+mc0X4YMvTpqM/XkQAun8oKDXvQetO7+wypIa2iuiEkuqaXIbK6TKwApJRs+k2vaY3LZYoiBdVkfN4vfTED4V9d3WJV5lcLhvDptpYwX8BxdD7xC4gFN+6jC/2d2ltAuMbKYLAY+IpXudZ1tsIpf8qEIaG+sNrXS4B4da8g/N/Pgj/gVQSwMECgAAAAgALWdKUvkYiIBsAQAAigMAAB0ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q1NVVUBQABtkgkYL2TX2+CMBTF35vwHe6LL2auhY2HkYbEbEbNnBhle+9KFWJtCa0Sv/2K4J9kb8u2FwrNPed3T3uhVhjLmRExooVaa7dsxbHWVWZiNEnTxekB41GK1lpKXUvNmS20QhRfCynutJUo5dGtGbOs1WP/3ocHEkDyCqY2XGoj0KwziSAMCSEBemFWRJDuxR2QJ5jrAwTEJ+A/RiGJCIHxW4qetVKCt7LWxnFb0IkX3AADp7kF/tD/U2fHDhJ0FJ4Lvv2HaH8YpYtAcXdbiHJZCGXdlhHVQVQxyq0tXcH5E6hiO9GmhnYOoBJZUTkI1IXNwRRqIwUYyUwOhYKS2dzJcKsDyvVux1TWOkcY9ybJKp0u
*/