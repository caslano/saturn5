
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