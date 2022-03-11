
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