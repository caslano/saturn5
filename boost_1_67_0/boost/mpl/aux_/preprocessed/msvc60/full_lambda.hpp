
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