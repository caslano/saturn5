
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "full_lambda.hpp" header
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