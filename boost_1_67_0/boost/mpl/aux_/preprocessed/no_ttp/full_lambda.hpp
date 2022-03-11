
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