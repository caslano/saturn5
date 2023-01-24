
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

namespace aux {

template<>
struct apply_chooser<0>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply0<
              F
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

namespace aux {

template<>
struct apply_chooser<1>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply1<
              F, T1
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

namespace aux {

template<>
struct apply_chooser<2>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply2<
              F, T1, T2
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

namespace aux {

template<>
struct apply_chooser<3>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply3<
              F, T1, T2, T3
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

namespace aux {

template<>
struct apply_chooser<4>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply4<
              F, T1, T2, T3, T4
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

namespace aux {

template<>
struct apply_chooser<5>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply5<
              F, T1, T2, T3, T4, T5
            > type;
    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_apply_arg
{
    static bool const value  = true;
};

template<>
struct is_apply_arg<na>
{
    static bool const value  = false;
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    >
struct apply_count_args
{
    static int const value  = is_apply_arg<T1>::value + is_apply_arg<T2>::value + is_apply_arg<T3>::value + is_apply_arg<T4>::value + is_apply_arg<T5>::value;

};

}

template<
      typename F, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na
    >
struct apply
    : aux::apply_chooser<
          aux::apply_count_args< T1,T2,T3,T4,T5 >::value
        >::template result_< F,T1,T2,T3,T4,T5 >::type
{
};

}}


/* apply.hpp
acqxCSOu/RdNL15Tu5FPBPHqIPh+n8O2Pti91K0Ac1cpIaumjzVqNLVcjIiifVpVzFU63f2WV+ve/GzoG3fftbjlwbgBTJVinv2NXgGqOdCS2oWjFR2VCtpjZDGtgVNcZW80oCKBScFL1YUFsii9wGcVnDB2kHYpUFJoUXMWjCDpS9r0+Lll55nqKVRxEEKMIS0bz/RTlqVCovvai5HIyZA9cnEpEOQ6jj4E53u/yCYdwV0ueydLNe6mf06i3tlb9RfO7iIoDi0LA/CD4DwkECxYcHd3h+AEh+Aa3F0aCAT34NK4uxOkIWhwd3cJjVtDd4/VzGymZqpmdavu4u7/+s893xeO5lWc3Q8IafiZaXs1Z8M8BU+cFWObd+9UMa3h8Uo7lkZoXk+sPoHiJmwSEekZ9k92vBnEN7ZG+RglxqG2eil2oYPWZEq/jvYYto0MNRDb5R86D3KJpjKV2Sg/s61XXX83ir9Z2BU5raBQWHTN07G80KXQWZHZR68AvP2JFz7UPnseOD+HuKnnYcxkPV+JskxKh6d+X1HrfqDP7JZxVZ8FDzQcBcVsMRoenoO0q4YWK3cfGByrvLHbFhjd0ovp2Pcp6F4jHfPAFN7KpPX7JrpDF55cdWHKN2bd6ivszz51xkxrJvGdSmvPmiWdUm1dtM7Y6rt0sytCxT1FXwKw5orcWX6OdT8gNwWJ/Dwj6X73nYZhn5ndgy04
*/