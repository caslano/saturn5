
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