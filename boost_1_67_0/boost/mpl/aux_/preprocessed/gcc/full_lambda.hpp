
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/full_lambda.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template<
      bool C1 = false, bool C2 = false, bool C3 = false, bool C4 = false
    , bool C5 = false
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< false,false,false,false,false >
    : false_
{
};

} // namespace aux

template<
      typename T
    , typename Tag
    , typename Arity
    >
struct lambda
{
    typedef false_ is_le;
    typedef T result_;
    typedef T type;
};

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};

template< int N, typename Tag >
struct lambda< arg<N>,Tag, int_< -1 > >
{
    typedef true_ is_le;
    typedef mpl::arg<N> result_; // qualified for the sake of MIPSpro 7.41
    typedef mpl::protect<result_> type;
};

template<
      typename F
    , typename Tag
    >
struct lambda<
          bind0<F>
        , Tag
        , int_<1>
        >
{
    typedef false_ is_le;
    typedef bind0<
          F
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1 > class F
    , typename L1
    >
struct le_result1
{
    typedef F<
          typename L1::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1 > class F
    , typename L1
    >
struct le_result1< true_,Tag,F,L1 >
{
    typedef bind1<
          quote1< F,Tag >
        , typename L1::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template< typename P1 > class F
    , typename T1
    , typename Tag
    >
struct lambda<
          F<T1>
        , Tag
        , int_<1>
        >
{
    typedef lambda< T1,Tag > l1;
    typedef typename l1::is_le is_le1;
    typedef typename aux::lambda_or<
          is_le1::value
        >::type is_le;

    typedef aux::le_result1<
          is_le, Tag, F, l1
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1
    , typename Tag
    >
struct lambda<
          bind1< F,T1 >
        , Tag
        , int_<2>
        >
{
    typedef false_ is_le;
    typedef bind1<
          F
        , T1
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1, typename P2 > class F
    , typename L1, typename L2
    >
struct le_result2
{
    typedef F<
          typename L1::type, typename L2::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1, typename P2 > class F
    , typename L1, typename L2
    >
struct le_result2< true_,Tag,F,L1,L2 >
{
    typedef bind2<
          quote2< F,Tag >
        , typename L1::result_, typename L2::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template< typename P1, typename P2 > class F
    , typename T1, typename T2
    , typename Tag
    >
struct lambda<
          F< T1,T2 >
        , Tag
        , int_<2>
        >
{
    typedef lambda< T1,Tag > l1;
    typedef lambda< T2,Tag > l2;
    
    typedef typename l1::is_le is_le1;
    typedef typename l2::is_le is_le2;
    

    typedef typename aux::lambda_or<
          is_le1::value, is_le2::value
        >::type is_le;

    typedef aux::le_result2<
          is_le, Tag, F, l1, l2
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1, typename T2
    , typename Tag
    >
struct lambda<
          bind2< F,T1,T2 >
        , Tag
        , int_<3>
        >
{
    typedef false_ is_le;
    typedef bind2<
          F
        , T1, T2
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1, typename P2, typename P3 > class F
    , typename L1, typename L2, typename L3
    >
struct le_result3
{
    typedef F<
          typename L1::type, typename L2::type, typename L3::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1, typename P2, typename P3 > class F
    , typename L1, typename L2, typename L3
    >
struct le_result3< true_,Tag,F,L1,L2,L3 >
{
    typedef bind3<
          quote3< F,Tag >
        , typename L1::result_, typename L2::result_, typename L3::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename T1, typename T2, typename T3
    , typename Tag
    >
struct lambda<
          F< T1,T2,T3 >
        , Tag
        , int_<3>
        >
{
    typedef lambda< T1,Tag > l1;
    typedef lambda< T2,Tag > l2;
    typedef lambda< T3,Tag > l3;
    
    typedef typename l1::is_le is_le1;
    typedef typename l2::is_le is_le2;
    typedef typename l3::is_le is_le3;
    

    typedef typename aux::lambda_or<
          is_le1::value, is_le2::value, is_le3::value
        >::type is_le;

    typedef aux::le_result3<
          is_le, Tag, F, l1, l2, l3
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1, typename T2, typename T3
    , typename Tag
    >
struct lambda<
          bind3< F,T1,T2,T3 >
        , Tag
        , int_<4>
        >
{
    typedef false_ is_le;
    typedef bind3<
          F
        , T1, T2, T3
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename L1, typename L2, typename L3, typename L4
    >
struct le_result4
{
    typedef F<
          typename L1::type, typename L2::type, typename L3::type
        , typename L4::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename L1, typename L2, typename L3, typename L4
    >
struct le_result4< true_,Tag,F,L1,L2,L3,L4 >
{
    typedef bind4<
          quote4< F,Tag >
        , typename L1::result_, typename L2::result_, typename L3::result_
        , typename L4::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename T1, typename T2, typename T3, typename T4
    , typename Tag
    >
struct lambda<
          F< T1,T2,T3,T4 >
        , Tag
        , int_<4>
        >
{
    typedef lambda< T1,Tag > l1;
    typedef lambda< T2,Tag > l2;
    typedef lambda< T3,Tag > l3;
    typedef lambda< T4,Tag > l4;
    
    typedef typename l1::is_le is_le1;
    typedef typename l2::is_le is_le2;
    typedef typename l3::is_le is_le3;
    typedef typename l4::is_le is_le4;
    

    typedef typename aux::lambda_or<
          is_le1::value, is_le2::value, is_le3::value, is_le4::value
        >::type is_le;

    typedef aux::le_result4<
          is_le, Tag, F, l1, l2, l3, l4
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename Tag
    >
struct lambda<
          bind4< F,T1,T2,T3,T4 >
        , Tag
        , int_<5>
        >
{
    typedef false_ is_le;
    typedef bind4<
          F
        , T1, T2, T3, T4
        > result_;

    typedef result_ type;
};

namespace aux {

template<
      typename IsLE, typename Tag
    , template< typename P1, typename P2, typename P3, typename P4, typename P5 > class F
    , typename L1, typename L2, typename L3, typename L4, typename L5
    >
struct le_result5
{
    typedef F<
          typename L1::type, typename L2::type, typename L3::type
        , typename L4::type, typename L5::type
        > result_;

    typedef result_ type;
};

template<
      typename Tag
    , template< typename P1, typename P2, typename P3, typename P4, typename P5 > class F
    , typename L1, typename L2, typename L3, typename L4, typename L5
    >
struct le_result5< true_,Tag,F,L1,L2,L3,L4,L5 >
{
    typedef bind5<
          quote5< F,Tag >
        , typename L1::result_, typename L2::result_, typename L3::result_
        , typename L4::result_, typename L5::result_
        > result_;

    typedef mpl::protect<result_> type;
};

} // namespace aux

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename T1, typename T2, typename T3, typename T4, typename T5
    , typename Tag
    >
struct lambda<
          F< T1,T2,T3,T4,T5 >
        , Tag
        , int_<5>
        >
{
    typedef lambda< T1,Tag > l1;
    typedef lambda< T2,Tag > l2;
    typedef lambda< T3,Tag > l3;
    typedef lambda< T4,Tag > l4;
    typedef lambda< T5,Tag > l5;
    
    typedef typename l1::is_le is_le1;
    typedef typename l2::is_le is_le2;
    typedef typename l3::is_le is_le3;
    typedef typename l4::is_le is_le4;
    typedef typename l5::is_le is_le5;
    

    typedef typename aux::lambda_or<
          is_le1::value, is_le2::value, is_le3::value, is_le4::value
        , is_le5::value
        >::type is_le;

    typedef aux::le_result5<
          is_le, Tag, F, l1, l2, l3, l4, l5
        > le_result_;

    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    , typename Tag
    >
struct lambda<
          bind5< F,T1,T2,T3,T4,T5 >
        , Tag
        , int_<6>
        >
{
    typedef false_ is_le;
    typedef bind5<
          F
        , T1, T2, T3, T4, T5
        > result_;

    typedef result_ type;
};

/// special case for 'protect'
template< typename T, typename Tag >
struct lambda< mpl::protect<T>,Tag, int_<1> >
{
    typedef false_ is_le;
    typedef mpl::protect<T> result_;
    typedef result_ type;
};

/// specializations for the main 'bind' form

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    , typename Tag
    >
struct lambda<
          bind< F,T1,T2,T3,T4,T5 >
        , Tag
        , int_<6>
        >
{
    typedef false_ is_le;
    typedef bind< F,T1,T2,T3,T4,T5 > result_;
    typedef result_ type;
};

template<
      typename F
    , typename Tag1
    , typename Tag2
    , typename Arity
    >
struct lambda<
          lambda< F,Tag1,Arity >
        , Tag2
        , int_<3>
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;
    typedef typename l1::is_le is_le;
    typedef bind1< quote1<aux::template_arity>, typename l1::result_ > arity_;
    typedef lambda< typename if_< is_le,arity_,Arity >::type, Tag2 > l3;
    typedef aux::le_result3<is_le, Tag2, mpl::lambda, l1, l2, l3> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

BOOST_MPL_AUX_NA_SPEC2(2, 3, lambda)

}}


/* full_lambda.hpp
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
*/