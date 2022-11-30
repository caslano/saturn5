
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