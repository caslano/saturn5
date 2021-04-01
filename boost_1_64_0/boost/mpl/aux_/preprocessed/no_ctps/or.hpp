
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< bool C_ > struct or_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : true_
    {
    };
};

template<> struct or_impl<false>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : or_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,false_ >
    {
    };
};

template<>
struct or_impl<false>
    ::result_< false_,false_,false_,false_ >
        : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        >::template result_< T2,T3,T4,T5 >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
UrMw6cXgEFRVVacans71T6mYJ/zOoHeCe/CWbp+oBrPyhrtfpBU+2f1qZXXYxktKYxSyFSwGs2sKv+VtpYkWDS74xTcz+GM3/nwPqS0V55FEU2mNyzoW46XVxAQJVw9EVRZjdTP0RJaB6dHX7F89HvVrAPwPkDrfGP44Pv0TQFIJt0+WyIMAtfk2g7lpxHZC0QUj7UbkTGn0UgA5GmRuzmp25N4SH0n8H+v1wt1wBcJzDwm21Uqc3/hFRg27RwH/fcvisUvxJWK9vE+FnRfTIh1jzCMeHh20aXRvBHpDtLJJwvHVWW7EqCa6lAMHkuiNBqISarftxB5PMCWFwfwj0TOBtsMcBl1CVH4QO5XqfcotHprlyfKrxP6yGNXi5HOfoK/UF4TJEqmT7TPttpUSRcalroUfeoK34jezcXGw4haoQdL095GSHaS2UWgfVumQxlUwy+fxUUzJaTgnYhgAAobArkQlhxuIsfdiagYvVwpSyrywujyaAuXNMvboGGQocSMYh9OwvAZ4yaxg+PbNFGQKzUu1kRObq/xvPyZuylxUiXhBjwqEqOalpw==
*/