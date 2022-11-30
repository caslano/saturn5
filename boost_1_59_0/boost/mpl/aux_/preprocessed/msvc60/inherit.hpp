
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C1, bool C2 >
struct inherit2_impl
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1, T2
    {
        typedef Derived type_;
    };
};

template<>
struct inherit2_impl< false,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T1
    {
        typedef T1 type_;
    };
};

template<>
struct inherit2_impl< true,false >
{
    template< typename Derived, typename T1, typename T2 > struct result_
        : T2
    {
        typedef T2 type_;
    };
};

template<>
struct inherit2_impl< true,true >
{
    template< typename Derived, typename T1, typename T2 > struct result_
    {
        typedef T1 type_;
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : aux::inherit2_impl<
          is_empty_base<T1>::value
        , is_empty_base<T2>::value
        >::template result_< inherit2< T1,T2 >,T1, T2 >
{
    typedef typename inherit2::type_ type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
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
*/