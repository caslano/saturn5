
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

BOOST_MPL_AUX_NA_SPEC(2, lambda)

}}


/* full_lambda.hpp
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
*/