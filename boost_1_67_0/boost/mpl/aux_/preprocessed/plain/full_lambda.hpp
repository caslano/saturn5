
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