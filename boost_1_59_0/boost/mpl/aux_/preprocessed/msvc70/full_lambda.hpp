
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