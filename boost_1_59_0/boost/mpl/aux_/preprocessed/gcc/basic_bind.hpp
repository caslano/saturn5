
// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/basic_bind.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template<
      typename T, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg
{
    typedef T type;
};

template<
      int N, typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg< arg<N>, U1, U2, U3, U4, U5 >
{
    typedef typename apply_wrap5<mpl::arg<N>, U1, U2, U3, U4, U5>::type type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg< bind< F,T1,T2,T3,T4,T5 >, U1, U2, U3, U4, U5 >
{
    typedef bind< F,T1,T2,T3,T4,T5 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

template<
      typename F
    >
struct bind0
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;

     public:
        typedef typename apply_wrap0<
              f_
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind0<F>, U1, U2, U3, U4, U5
    >
{
    typedef bind0<F> f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(1, bind0)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(1, bind0)

template<
      typename F
    >
struct bind< F,na,na,na,na,na >
    : bind0<F>
{
};

template<
      typename F, typename T1
    >
struct bind1
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;

     public:
        typedef typename apply_wrap1<
              f_
            , typename t1::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename U1, typename U2, typename U3
    , typename U4, typename U5
    >
struct resolve_bind_arg<
      bind1< F,T1 >, U1, U2, U3, U4, U5
    >
{
    typedef bind1< F,T1 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(2, bind1)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(2, bind1)

template<
      typename F, typename T1
    >
struct bind< F,T1,na,na,na,na >
    : bind1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct bind2
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;

     public:
        typedef typename apply_wrap2<
              f_
            , typename t1::type, typename t2::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename U1, typename U2
    , typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind2< F,T1,T2 >, U1, U2, U3, U4, U5
    >
{
    typedef bind2< F,T1,T2 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(3, bind2)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(3, bind2)

template<
      typename F, typename T1, typename T2
    >
struct bind< F,T1,T2,na,na,na >
    : bind2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct bind3
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;

     public:
        typedef typename apply_wrap3<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename U1
    , typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind3< F,T1,T2,T3 >, U1, U2, U3, U4, U5
    >
{
    typedef bind3< F,T1,T2,T3 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(4, bind3)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(4, bind3)

template<
      typename F, typename T1, typename T2, typename T3
    >
struct bind< F,T1,T2,T3,na,na >
    : bind3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct bind4
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;

     public:
        typedef typename apply_wrap4<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename U1, typename U2, typename U3, typename U4, typename U5
    >
struct resolve_bind_arg<
      bind4< F,T1,T2,T3,T4 >, U1, U2, U3, U4, U5
    >
{
    typedef bind4< F,T1,T2,T3,T4 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(5, bind4)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(5, bind4)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct bind< F,T1,T2,T3,T4,na >
    : bind4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct bind5
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef typename aux::resolve_bind_arg< F,U1,U2,U3,U4,U5 >::type f_;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef aux::resolve_bind_arg< T4,U1,U2,U3,U4,U5 > t4;
        typedef aux::resolve_bind_arg< T5,U1,U2,U3,U4,U5 > t5;

     public:
        typedef typename apply_wrap5<
              f_
            , typename t1::type, typename t2::type, typename t3::type
            , typename t4::type, typename t5::type
            >::type type;

    };
};

namespace aux {

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename U1, typename U2, typename U3, typename U4
    , typename U5
    >
struct resolve_bind_arg<
      bind5< F,T1,T2,T3,T4,T5 >, U1, U2, U3, U4, U5
    >
{
    typedef bind5< F,T1,T2,T3,T4,T5 > f_;
    typedef typename apply_wrap5< f_,U1,U2,U3,U4,U5 >::type type;
};

} // namespace aux

BOOST_MPL_AUX_ARITY_SPEC(6, bind5)
BOOST_MPL_AUX_TEMPLATE_ARITY_SPEC(6, bind5)

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct bind
    : bind5< F,T1,T2,T3,T4,T5 >
{
};

/// if_/eval_if specializations
template< template< typename T1, typename T2, typename T3 > class F, typename Tag >
struct quote3;

template< typename T1, typename T2, typename T3 > struct if_;

template<
      typename Tag, typename T1, typename T2, typename T3
    >
struct bind3<
      quote3< if_,Tag >
    , T1, T2, T3
    >
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef mpl::arg<1> n1;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef typename if_<
              typename t1::type
            , t2, t3
            >::type f_;

     public:
        typedef typename f_::type type;
    };
};

template<
      template< typename T1, typename T2, typename T3 > class F, typename Tag
    >
struct quote3;

template< typename T1, typename T2, typename T3 > struct eval_if;

template<
      typename Tag, typename T1, typename T2, typename T3
    >
struct bind3<
      quote3< eval_if,Tag >
    , T1, T2, T3
    >
{
    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
     private:
        typedef mpl::arg<1> n1;
        typedef aux::resolve_bind_arg< T1,U1,U2,U3,U4,U5 > t1;
        typedef aux::resolve_bind_arg< T2,U1,U2,U3,U4,U5 > t2;
        typedef aux::resolve_bind_arg< T3,U1,U2,U3,U4,U5 > t3;
        typedef typename eval_if<
              typename t1::type
            , t2, t3
            >::type f_;

     public:
        typedef typename f_::type type;
    };
};

}}


/* basic_bind.hpp
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
*/