
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
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
*/