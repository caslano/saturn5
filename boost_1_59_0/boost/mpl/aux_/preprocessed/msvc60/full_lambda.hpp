
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
struct lambda< arg<N>, Tag >
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
struct lambda< mpl::protect<T>, Tag >
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
       
        >
{
    typedef false_ is_le;
    typedef bind< F,T1,T2,T3,T4,T5 > result_;
    typedef result_ type;
};

/// workaround for MWCW 8.3+/EDG < 303, leads to ambiguity on Digital Mars

template<
      typename F, typename Tag1, typename Tag2
    >
struct lambda<
          lambda< F,Tag1 >
        , Tag2
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;
    typedef typename l1::is_le is_le;
    typedef aux::le_result2<is_le, Tag2, mpl::lambda, l1, l2> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

BOOST_MPL_AUX_NA_SPEC(2, lambda)

}}


/* full_lambda.hpp
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
*/