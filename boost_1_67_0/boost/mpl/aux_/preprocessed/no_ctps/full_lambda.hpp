
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
+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
*/