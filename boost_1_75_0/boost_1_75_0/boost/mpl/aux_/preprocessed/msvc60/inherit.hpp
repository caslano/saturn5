
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
YqNZg6BbBOhR7aEP9FTNSO8Onr9ujOMP3JDPjEuVD6uJ2VXCIAQx2ZCTNnHaDBNfemisqmshanT4fdKvlWEeIblxsrV4xvHY+75rDIeea1lGXTVwunzN/seYLBD7Q9dk2Xbd+Iq0Ej2Ze6DQt8odl3IjQWs/+3nyZVf+2mNYZOZxrFMnhNPCSmay+X3TZL2glQALHTk3R0V1Ike8QS1BK6s8kqrl2DaCunYpR6umfdT31PFIv6I0wTQemu8Fnyx/Z8llvQ1HjhG/X7J2oVvHqTGf8MC1YUAPA9lLknuc43BmeGEI24N0hh9iPNfaMYaVSPnkBxCiQSkBbCcYMZmTcb6Bp2X3MRlLxtcucURic021m+z9hyo2Q1S9Qhl3OmhS7bV4x6setbZ++lvuc2RXbTnqkuUYG7Li2vTqz+L1RcnHn3npp3a9Bzsf772GJRJ3oWa6X9oFu223v/gCnrZ2hV9fvwUV9OZCL4XfNK52q49XCV189LN+BZm6L4xn88xTPpaP8T8/MKpiUSOHo+AOoFLuY9Gandz9qo2bNj+wxTplRvhCgPs7LFZp2LO9sA0lNMd4PTQnxzhIUhIhap8UXKQ//+BUu5xiGSPBuL30uSSDZ+bnd7QCL87URk/erCXZ8wbUCNao1koW9KUvTEDJVQer3eVSF4YUKibnLvxlFn9lxad8HezMMPBuBqG5EKWz14ksJmlVoxPa5pHl
*/