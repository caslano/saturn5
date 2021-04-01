
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
06RQzsgzB9cjdxn9YE96YM+ZTtd+dzVUfCgDLAvHIsiIp3jF5regeZBTRBcD5OAjdFwQSMwR2I+ksM7PKtJ4bhdFYMdUQZMfAMIPfvj9dl9bkkGyFLdWiLUtVbrwyNfdRJASPP3wNx3Z0gGcP6KW5VRQ/+Ze+ANwQJmzQdJr62lz9L0Ma9Lxv/3vCCDEri1OgDDns8u1ZicBNORdinhg5mHsN0/a2v5o5EV2eYPZPZ8r0lbUoVs1Ta6Znwv+AxeRhJlGLYN5ieorBqH6+6DL9hqzNJ5haOKaJqjP2Lg5iYpSd35RMJ/GQJWbRKDPeP+mWK7xkFztIXxMmDpIOmYsWgpW2CTcXern4zx5fzg42/ZzaPQ53MueGCX2A8memNwQEzOX4p3Qv17Kg/aPHP1Yy2okcFvxQB0dm7O9S0IwTf7Ewkhngx8mFFKlGxPRytjUBA06bzjZ1shBc5Jq3JDOz4rp5rKaorXZrCNlUG5jpZDpg9EbI7BSSvBATDyZzIY6EP9xZ0VZiJGTz8tdWzaFtyUIFcGybWyuMyP3b8WmTmReriJkDxi2Ej8vcQ==
*/