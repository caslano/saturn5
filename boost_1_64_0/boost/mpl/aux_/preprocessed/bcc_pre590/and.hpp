
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "and.hpp" header
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
40m0Sf0asCKls+/glgSDneedQBXW4/dZl8mqmlFgnAuASSMIGlku7WbEjzuIhoQU5Lu1oU77EzNVvExwMiv0SJl9kM0LdS5steBhs9QNb+77jdoVWualZicZlZvKpjst+2UIuR+Km/VpgSNmYmwZGfJXI7fuZOhfJhlIDmdJr2pXdFWdojXtNiiyk3a944idef+IczQlYQckJ9TBHFixP4mn1XSMc+dW0v6lrGtF+i33AxBAMi9NIZOyZfPQ5IdPA2DYIl6gSlGc5G4Kpr5XnrUbVAtHrJfgbAjz1nY/w+D3zAlncj32DJmgs9oa80Zt9m9tdvKzr22y8dTQEqh4Zfz9R1TdMVABdhBkacUm0U6b1shhZ9YzH69n8+Qke7bTkDQMocWsCmzjbpjGgmuNeJewHoWaeTypu+rMcdK8sq62dpy/T5+NO08m8eM5reiCHxfjd6jsWHTRl2JZjawUIcC2W8/Z49QFA+24+1h6cMoDHGwt7W9GZX7ntKxRf94AXmeN58oVNEdYxpIimCHxCY9fYjJG8B3mXze1bOyNfXkDjI5xEKW0/Kc7yw==
*/