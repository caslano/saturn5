
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
+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
*/