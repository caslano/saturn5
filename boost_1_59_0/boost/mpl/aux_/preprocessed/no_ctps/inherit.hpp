
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