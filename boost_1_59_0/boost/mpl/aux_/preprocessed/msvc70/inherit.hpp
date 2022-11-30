
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