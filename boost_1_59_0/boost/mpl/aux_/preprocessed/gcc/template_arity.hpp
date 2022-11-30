
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {
template< int N > struct arity_tag
{
    typedef char (&type)[N + 1];
};

template<
      int C1, int C2, int C3, int C4, int C5, int C6
    >
struct max_arity
{
    BOOST_STATIC_CONSTANT(int, value =
          ( C6 > 0 ? C6 : ( C5 > 0 ? C5 : ( C4 > 0 ? C4 : ( C3 > 0 ? C3 : ( C2 > 0 ? C2 : ( C1 > 0 ? C1 : -1 ) ) ) ) ) )
        );
};

arity_tag<0>::type arity_helper(...);

template<
      template< typename P1 > class F
    , typename T1
    >
typename arity_tag<1>::type
arity_helper(type_wrapper< F<T1> >, arity_tag<1>);

template<
      template< typename P1, typename P2 > class F
    , typename T1, typename T2
    >
typename arity_tag<2>::type
arity_helper(type_wrapper< F< T1,T2 > >, arity_tag<2>);

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename T1, typename T2, typename T3
    >
typename arity_tag<3>::type
arity_helper(type_wrapper< F< T1,T2,T3 > >, arity_tag<3>);

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename T1, typename T2, typename T3, typename T4
    >
typename arity_tag<4>::type
arity_helper(type_wrapper< F< T1,T2,T3,T4 > >, arity_tag<4>);

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename T1, typename T2, typename T3, typename T4, typename T5
    >
typename arity_tag<5>::type
arity_helper(type_wrapper< F< T1,T2,T3,T4,T5 > >, arity_tag<5>);

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5, typename P6
        >
      class F
    , typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6
    >
typename arity_tag<6>::type
arity_helper(type_wrapper< F< T1,T2,T3,T4,T5,T6 > >, arity_tag<6>);
template< typename F, int N >
struct template_arity_impl
{
    BOOST_STATIC_CONSTANT(int, value =
          sizeof(::boost::mpl::aux::arity_helper(type_wrapper<F>(), arity_tag<N>())) - 1
        );
};

template< typename F >
struct template_arity
{
    BOOST_STATIC_CONSTANT(int, value  = (
          max_arity< template_arity_impl< F,1 >::value, template_arity_impl< F,2 >::value, template_arity_impl< F,3 >::value, template_arity_impl< F,4 >::value, template_arity_impl< F,5 >::value, template_arity_impl< F,6 >::value >::value
        ));
    typedef mpl::int_<value> type;
};

}}}

/* template_arity.hpp
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
*/