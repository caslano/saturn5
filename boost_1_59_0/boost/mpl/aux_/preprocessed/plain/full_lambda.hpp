
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