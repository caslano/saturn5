
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "full_lambda.hpp" header
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
    , typename Arity
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
struct lambda< arg<N>,Tag, int_< -1 > >
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
        , int_<1>
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
        , int_<1>
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
        , int_<2>
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
        , int_<2>
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
        , int_<3>
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
        , int_<3>
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
        , int_<4>
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
        , int_<4>
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
        , int_<5>
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
        , int_<5>
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
        , int_<6>
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
struct lambda< mpl::protect<T>,Tag, int_<1> >
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
        , int_<6>
        >
{
    typedef false_ is_le;
    typedef bind< F,T1,T2,T3,T4,T5 > result_;
    typedef result_ type;
};

template<
      typename F
    , typename Tag1
    , typename Tag2
    , typename Arity
    >
struct lambda<
          lambda< F,Tag1,Arity >
        , Tag2
        , int_<3>
        >
{
    typedef lambda< F,Tag2 > l1;
    typedef lambda< Tag1,Tag2 > l2;
    typedef typename l1::is_le is_le;
    typedef bind1< quote1<aux::template_arity>, typename l1::result_ > arity_;
    typedef lambda< typename if_< is_le,arity_,Arity >::type, Tag2 > l3;
    typedef aux::le_result3<is_le, Tag2, mpl::lambda, l1, l2, l3> le_result_;
    typedef typename le_result_::result_ result_;
    typedef typename le_result_::type type;
};

BOOST_MPL_AUX_NA_SPEC2(2, 3, lambda)

}}


/* full_lambda.hpp
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
*/